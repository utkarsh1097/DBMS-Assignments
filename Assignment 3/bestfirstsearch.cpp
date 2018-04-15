#include<iostream>
#include<stdio.h>
#include<stdlib.h> 
#include<queue>
#include<algorithm>

using namespace std;

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
			else
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
	// double new_mbr_min[dim], new_mbr_max[dim];
	for(int d = 0; d < dim; d++)
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

double distance(int d, double *p1, double *p2)
{
	double ans = 0.0;
	for(int i = 0; i < d; ++i)
		ans = ans + (p1[i]-p2[i])*(p1[i]-p2[i]);
	return ans;
}

bool lexi_compare(int d, double *p1, double *p2)	//return true if p1 lexicographically smaller than p2
{
	for(int i = 0; i < d; ++i)
	{
		if(p1[i] != p2[i])
			return p1[i] < p2[i];
	}
}

double mbr_distance(int d, double *mbr_min, double *mbr_max, double query_point[])
{
	double ans = 0.0;
	for(int i = 0; i < d; ++i)
	{
		if(query_point[i] < mbr_min[i])
			ans = ans+ (mbr_min[i]-query_point[i])*(mbr_min[i]-query_point[i]);
		else
		if(query_point[i] > mbr_max[i])
			ans = ans+ (query_point[i]-mbr_max[i])*(query_point[i]-mbr_max[i]);
	}
	return ans;
}

void bestFirstSearch(int dim, double query_point[], priority_queue<pair<double, Node *>> &candidates, priority_queue<pair<double, Node *>> &answer)
{
	// TODO: Implement best first search and find the times for 20NN queries. This will complete this file's part.
	while(true)
	{
		counter++;
		if(candidates.size() == 0)
			return;
		pair<double, Node *> P = candidates.top(), Q;
		candidates.pop();
		if(answer.size() >= 20)
		{
			Q = answer.top();
			if(Q.first < -P.first)
				return;
		}
		Node *curnode = P.second;
		double *curpoint = curnode->getPoint();
		double cur_distance = distance(dim, curpoint, query_point);
		if(answer.size() >= 20)
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
			if(answer.size() >= 20)
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
			if(answer.size() >= 20)
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

int main()
{
	system("mkdir bestfirstsearch_20NN");
	freopen("bestfirstsearch_time.txt", "w", stdout);
	fclose(stdout);
	int d[] = {2, 3, 5, 10, 15, 20};
	for(int r = 0; r <= 5; r++)
	{
		string filename = "dataset/dataset_"+to_string(d[r])+".txt";
		freopen(filename.c_str(), "r", stdin);
		int N, D;
		double data;
		cin>>D>>N;
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
				cin>>data;
				datapoints[i][j] = data;
			}
		}
		mbr_min[N] = new double [D];
		mbr_max[N] = new double [D];
		fclose(stdin);

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

		for(int i = 0; i < D; i++)
		{
			mbr_min[0][i] = 0.0;
			mbr_max[0][i] = 1.0;
		}
		
		counter = 0;
		Node *head = buildTree(0, D, 0, N-1, 0, 0);	//Build the KD Tree
		// cout<<0<<endl;	//KD-Tree construction completed

		double average_time = 0.0;
		clock_t begin = clock();
		filename = "queryset/queryset_"+to_string(D)+".txt";
		freopen(filename.c_str(), "r", stdin);
		string pathname = "bestfirstsearch_20NN/"+to_string(D);
		string makedir = "mkdir "+pathname;
		system(makedir.c_str());
		for(int i = 0; i < 100; ++i)
		{

			priority_queue<pair<double, Node *>> candidates, answer;		//Candidates is min heap, answer is max heap
			candidates.push(make_pair(-0.0, head));	//Initially the root MBR is present
			
			double query_point[D];

			for(int i = 0; i < D; ++i)
			{
				cin>>query_point[i];
			}
			//Now start finding kNN
			bestFirstSearch(D, query_point, candidates, answer);

			filename = pathname+"/"+to_string(i+1)+".txt";
			freopen(filename.c_str(), "w", stdout);
			
			double *ans[20];
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
					cout<<ans[i][j]<<" ";
				cout<<endl;
			}
			fclose(stdout);
		}
		fclose(stdin);

		clock_t end = clock();
		filename = pathname+"/"+"average_time.txt";
		freopen(filename.c_str(), "w", stdout);
		average_time = double(end-begin)/CLOCKS_PER_SEC;
		average_time = average_time/100;
		cout<<"Average time to find 20NN using best first search for dimension "<<D<<" is "<<average_time<<endl;
		fclose(stdout);
		freopen("bestfirstsearch_time.txt", "a", stdout);
		cout<<average_time<<endl;
		fclose(stdout);
	}

	return 0;
}
