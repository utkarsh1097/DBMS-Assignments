#include<iostream>
#include<stdio.h>
#include<stdlib.h> 
#include<queue>
#include<algorithm>

using namespace std;

#define MAX(a,b) (((a)>(b))?(a):(b))

double **datapoints, **mbr_min, **mbr_max;	//Stores the datapoints, all the min mbr, all the max mbr
int **indexes;	//Store indexes of all datapoints
int sort_dim, counter;	//Dimension on which sort has to be done
int comp_d;

bool comparator(int a, int b)
{
	if(datapoints[a][sort_dim] != datapoints[b][sort_dim])
		return datapoints[a][sort_dim] < datapoints[b][sort_dim];
	else
	{
		int k = (sort_dim+1)%comp_d;
		while(true)
		{
			if(datapoints[a][k] != datapoints[b][k])
				return datapoints[a][k] < datapoints[b][k];
			k = (k+1)%comp_d;
		}
	}
}

class Node
{
	private:
		double *point, *mbr_min, *mbr_max;
		Node *left, *right;
	public:
		Node()
		{
			left = NULL;
			right = NULL;
		}

		Node(double *in_point, double *in_mbr_min, double *in_mbr_max)
		{
			left = NULL;
			right = NULL;
			point = in_point;
			mbr_max = in_mbr_max;
			mbr_min = in_mbr_min;
		}

		void assignL(Node* child)
		{
			left = child;
		}

		void assignR(Node* child)
		{
			right = child;
		}

		Node *getLChild()
		{
			return left;
		}

		Node *getRChild()
		{
			return right;
		}

		double *getPoint()
		{
			return point;
		}

		double *getMinMBR()
		{
			return mbr_min;
		}

		double *getMaxMBR()
		{
			return mbr_max;
		}

};

Node *buildTree(int level, int dim, int L, int R, int mbr_min_idx, int mbr_max_idx)
{
	if(R < L)	//Leaf node condition
		return NULL;
	int split_on_dim = level%dim;		//Dimension to split on. First index of "indexes"
	int mid = (L+R)/2;		//median. if even nos choose lower one, else middle one is chosen. second index of "indexes"
	
	int point_idx = indexes[split_on_dim][mid];	//Stores the index of current point

	for(int d = 0; d < dim; ++d)
	{
		if(dim != split_on_dim)
		{
			//What we do here is that we will sort the index[d] array in such a way that the sorting and ordering of the left child and right child in all dimensions is maintained always
			int temp[R-L+1];	//will help in "sorting" the vector of indexes so that at each level we get the correct lists sorted on each dimension
			for(int i = L; i<=R; ++i)
				temp[i-L] = (indexes[d][i]);
			int i = L, j = mid+1, k = L;
			indexes[d][mid] = point_idx;	//for the sake of conserving this value in sorted lists of other dimensions
			while(i < mid && j <= R)
			{
				if(temp[k-L] != point_idx)
				{
					if(datapoints[temp[k-L]][split_on_dim] <= datapoints[point_idx][split_on_dim])
					{
						indexes[d][i] = temp[k-L];
						++i;
					}
					else
					{
						indexes[d][j] = temp[k-L];
						++j;
					}
				}
				++k;
			}
			while(i < mid)
			{
				if(temp[k-L] != point_idx)
				{
					indexes[d][i] = temp[k-L];
					++i;
				}
				++k;
			}
			while(j <= R)
			{
				if(temp[k-L] != point_idx)
				{
					indexes[d][j] = temp[k-L];
					++j;
				}
				++k;
			}
		}
	}

	Node *curnode = new Node(datapoints[point_idx], mbr_min[mbr_min_idx], mbr_max[mbr_max_idx]);	

	++counter;
	for(int d = 0; d < dim; ++d)
	{
		mbr_min[counter][d] = mbr_min[mbr_min_idx][d];
		mbr_max[counter][d] = mbr_max[mbr_max_idx][d];
	}

	mbr_min[counter][split_on_dim] = datapoints[point_idx][split_on_dim];
	mbr_max[counter][split_on_dim] = datapoints[point_idx][split_on_dim];

	int new_mbr_min_idx = counter, new_mbr_max_idx = counter;

	//The commented code below is to obtain the KD-Tree with in-order traversal
	/*for(int i = 0; i < dim; ++i)
		cout<<datapoints[point_idx][i]<<" ";
	cout<<endl;*/
	curnode->assignL(buildTree(level+1, dim, L, mid-1, mbr_min_idx, new_mbr_max_idx));
	curnode->assignR(buildTree(level+1, dim, mid+1, R, new_mbr_min_idx, mbr_max_idx));

	return curnode;
}

double distance(int &d, double *p1, double *p2)
{
	double ans = 0.0;
	for(int i = 0; i < d; ++i)
		ans = ans + (p1[i]-p2[i])*(p1[i]-p2[i]);
	return ans;
}

bool lexi_compare(int &d, double *p1, double *p2)	//return true if p1 lexicographically smaller than p2
{
	for(int i = 0; i < d; ++i)
	{
		if(p1[i] != p2[i])
			return p1[i] < p2[i];
	}
}

double mbr_distance(int &d, double *mbr_min, double *mbr_max, double query_point[])
{
	double ans = 0.0, delta;
	for(int i = 0; i < d; ++i)
	{
		
		delta = MAX((mbr_min[i]-query_point[i]), MAX(0, (query_point[i]-mbr_max[i])));
		ans = ans + delta*delta;
	}
	return ans;
}


//BestFirstSearch works better for D <= 12, whereas NormalSearch works better for D > 12
void bestFirstSearch(int &K, int &dim, double query_point[], priority_queue<pair<double, Node *>> &candidates, priority_queue<pair<double, Node *>> &answer)
{
	// TODO: Implement best first search and find the times for 100NN queries. This will complete this file's part.
	while(true)
	{
		if(candidates.size() == 0)
			return;
		pair<double, Node *> P = candidates.top(), Q;
		candidates.pop();
		if(answer.size() == K)
		{
			Q = answer.top();
			if(Q.first < -P.first)
				return;
		}
		Node *curnode = P.second;
		double *curpoint = curnode->getPoint();
		double cur_distance = distance(dim, curpoint, query_point);
		if(answer.size() == K)
		{
			if(cur_distance < Q.first)
			{
				answer.pop();
				answer.push(make_pair(cur_distance, curnode));
			}
			else
			if(cur_distance == Q.first)
			{
				if(lexi_compare(dim, curpoint, Q.second->getPoint()))
				{
					answer.pop();
					answer.push(make_pair(cur_distance, curnode));
				}
			}
		}
		else
		{	
			answer.push(make_pair(cur_distance, curnode));
		}
		Q = answer.top();
		Node *LChild = curnode->getLChild(), *RChild = curnode->getRChild();
		double lchild_distance, rchild_distance;
		if(LChild != NULL)
		{
			lchild_distance = mbr_distance(dim, LChild->getMinMBR(), LChild->getMaxMBR(), query_point);
			if(answer.size() == K)
			{
				if(lchild_distance <= Q.first)
					candidates.push(make_pair(-lchild_distance, LChild));		
			}
			else
			{
				candidates.push(make_pair(-lchild_distance, LChild));			
			}
		}
		if(RChild != NULL)
		{
			rchild_distance = mbr_distance(dim, RChild->getMinMBR(), RChild->getMaxMBR(), query_point);
			if(answer.size() == K)
			{
				if(rchild_distance <= Q.first)
					candidates.push(make_pair(-rchild_distance, RChild));			
			}
			else
			{
				candidates.push(make_pair(-rchild_distance, RChild));			
			}
		}
	}
}

void Search(int &K, int &dim, double query_point[], queue<Node *> &candidates, priority_queue<pair<double, Node *>> &answer)
{
	// TODO: Implement normal search and find the times for K-NN queries. 
	while(true)
	{
		if(candidates.size() == 0)
			return;
		Node *curnode = candidates.front();
		candidates.pop();
		pair<double, Node *> Q;
		Q = answer.top();
		double *curpoint = curnode->getPoint();
		double cur_distance = distance(dim, curpoint, query_point);
		if(answer.size() == K)
		{
			if(cur_distance < Q.first)
			{
				answer.pop();
				answer.push(make_pair(cur_distance, curnode));
			}
			else
			if(cur_distance == Q.first)
			{
				if(lexi_compare(dim, curpoint, Q.second->getPoint()))
				{
					answer.pop();
					answer.push(make_pair(cur_distance, curnode));
				}
			}
		}
		else
		{	
			answer.push(make_pair(cur_distance, curnode));
		}
		if(curnode->getLChild() != NULL)
			candidates.push(curnode->getLChild());
		if(curnode->getRChild() != NULL)
			candidates.push(curnode->getRChild());
		
	}
}

int main(int argc, char* argv[])
{
	FILE *input, *output;
	input = fopen(argv[1], "r");
	int N, D;
	double data;
	fscanf(input, "%d %d", &D, &N);	//N is number of data points
	comp_d = D;
	//First, take in the tuples
	datapoints = new double* [N];
	mbr_min = new double* [N+1];	//Should be N+1, but just testing
	mbr_max = new double* [N+1];	////Should be N+1, but just testing
	indexes = new int* [D];
	for(int i = 0; i < N; ++i)
	{
		datapoints[i] = new double [D];
		mbr_min[i] = new double [D];
		mbr_max[i] = new double [D];
		for(int j = 0; j < D; ++j)
		{
			fscanf(input, "%lf", &data);
			datapoints[i][j] = data;
		}
	}
	fclose(input);
	mbr_min[N] = new double [D];
	mbr_max[N] = new double [D];
	//Now we will have to sort the tuples. Sorting is maintained by instead sorting an integer array of indexes. The comparator function looks into the datapoints instead.
	//Sorting needs to be maintained wrt each dimension.
	for(int i = 0; i < D; ++i)
	{
		indexes[i] = new int [N];
		for(int j = 0; j < N; ++j)
			indexes[i][j] = j;
		sort_dim = i;
		sort(indexes[i], indexes[i]+N, comparator);
	}
	//Initialize mbr_min[0] and mbr_max[0] 
	for(int i = 0; i < D; i++)
	{
		mbr_min[0][i] = 0.0;
		mbr_max[0][i] = 1.0;
	}
	counter = 0;
	Node *head = buildTree(0, D, 0, N-1, 0, 0);	//Build the KD Tree
	cout<<0<<endl;	//KD-Tree construction completed
	string filename;	//Query filename
	int K;	//K-NN Query
	cin>>filename>>K;
	input = fopen(filename.c_str(), "r");
	fscanf(input, "%d %d", &D, &N);	//This time, N is number of query points
	output = fopen("results.txt", "w");
	if(D <= 12)		//Best First Search
	{
		for(int i = 0; i < N; ++i)
		{
			priority_queue<pair<double, Node *>> candidates, answer;		//Candidates is min heap, answer is max heap
			candidates.push(make_pair(-0.0, head));	//Initially the root MBR is present
			
			double query_point[D];

			for(int i = 0; i < D; ++i)
			{
				fscanf(input, "%lf", &query_point[i]);
			}
			//Now start finding kNN
			bestFirstSearch(K, D, query_point, candidates, answer);
			double *ans[K];
			int k = 0;

			while(!answer.empty())
			{
				ans[k] = answer.top().second->getPoint();
				++k;
				answer.pop();
			}

			for(int i = k-1; i>=0; --i)
			{
				for(int j = 0; j < D; ++j)
					fprintf(output, "%.6lf ", ans[i][j]);
				fprintf(output, "\n");
			}
		}
	}
	else	//Normal Search
	{
		for(int i = 0; i < N; ++i)
		{
			priority_queue<pair<double, Node *>> answer;		//Candidates is min heap, answer is max heap
			
			queue<Node *> candidates;
			candidates.push(head);	//Initially the root MBR is present
			
			double query_point[D];

			for(int i = 0; i < D; ++i)
			{
				fscanf(input, "%lf", &query_point[i]);
			}
			//Now start finding kNN
			Search(K, D, query_point, candidates, answer);

			double *ans[K];
			int k = 0;

			while(!answer.empty())
			{
				ans[k] = answer.top().second->getPoint();
				++k;
				answer.pop();
			}

			for(int i = k-1; i>=0; --i)
			{
				for(int j = 0; j < D; ++j)
					fprintf(output, "%.6lf ", ans[i][j]);
				fprintf(output, "\n");
			}
		}
	}
	fclose(output);
	fclose(input);
	cout<<"1"<<endl;	//OVER
	return 0;
}