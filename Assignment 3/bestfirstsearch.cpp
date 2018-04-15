#include<iostream>
#include<stdio.h>
#include<stdlib.h> 
#include<queue>
#include<algorithm>

using namespace std;

vector<vector<double>> datapoints, mbr_min, mbr_max;	//Stores the datapoints, all the min mbr, all the max mbr
vector<vector<int>> indexes;	//Store indexes of all datapoints
int sort_dim, counter;	//Dimension on which sort has to be done

bool comparator(int a, int b)
{
	int d = datapoints[a].size();
	if(datapoints[a][sort_dim] != datapoints[b][sort_dim])
		return datapoints[a][sort_dim] < datapoints[b][sort_dim];
	else
	{
		int k = (sort_dim+1)%d;
		while(true)
		{
			if(datapoints[a][k] != datapoints[b][k])
				return datapoints[a][k] < datapoints[b][k];
			else
				++k;
		}
	}
}

class Node
{
	private:
		int ID, point_idx, mbr_min_idx, mbr_max_idx;
		Node *left, *right;
	public:
		Node()
		{
			left = NULL;
			right = NULL;
		}

		Node(int in_id, int in_point, int in_mbr_min, int in_mbr_max)
		{
			ID = in_id;
			left = NULL;
			right = NULL;
			point_idx = in_point;
			mbr_max_idx = in_mbr_max;
			mbr_min_idx = in_mbr_min;
		}

		void assignL(Node* child)
		{
			left = child;
		}

		void assignR(Node* child)
		{
			right = child;
		}

		int getID()
		{
			return ID;
		}

		Node *getLChild()
		{
			return left;
		}

		Node *getRChild()
		{
			return right;
		}

		int getPointIdx()
		{
			return point_idx;
		}

		int getMinMBRIdx()
		{
			return mbr_min_idx;
		}

		int getMaxMBRIdx()
		{
			return mbr_max_idx;
		}

};

Node *buildTree(int level, int dim, int L, int R, int mbr_min_idx, int mbr_max_idx, Node *pointers[])
{
	if(R < L)	//Leaf node condition
		return NULL;
	int split_on_dim = level%dim;		//Dimension to split on. First index of "indexes"
	int mid = (L+R)/2;		//median. if even nos choose lower one, else middle one is chosen. second index of "indexes"
	
	int point_idx = indexes[split_on_dim][mid];	//Stores the index of current point

	vector<int> temp;	//will help in "sorting" the vector of indexes so that at each level we get the correct lists sorted on each dimension

	for(int d = 0; d < dim; ++d)
	{
		if(dim != split_on_dim)
		{
			//What we do here is that we will sort the index[d] array in such a way that the sorting and ordering of the left child and right child in all dimensions is maintained always
			temp.clear();
			for(int i = L; i<=R; ++i)
				temp.push_back(indexes[d][i]);
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

	Node *curnode = new Node(counter, point_idx, mbr_min_idx, mbr_max_idx);	
	pointers[counter] = curnode;

	vector<double> new_mbr_min, new_mbr_max;
	new_mbr_min = mbr_min[mbr_min_idx];
	new_mbr_max = mbr_max[mbr_max_idx];
	new_mbr_max[split_on_dim] = datapoints[point_idx][split_on_dim];
	new_mbr_min[split_on_dim] = datapoints[point_idx][split_on_dim];

	++counter;

	int new_mbr_min_idx = counter, new_mbr_max_idx = counter;

	mbr_min[counter] = new_mbr_min;
	mbr_max[counter] = new_mbr_max;

	//The commented code below is to obtain the KD-Tree with in-order traversal
	/*for(int i = 0; i < dim; ++i)
		cout<<datapoints[point_idx][i]<<" ";
	cout<<endl;*/
	curnode->assignL(buildTree(level+1, dim, L, mid-1, mbr_min_idx, new_mbr_max_idx, pointers));
	curnode->assignR(buildTree(level+1, dim, mid+1, R, new_mbr_min_idx, mbr_max_idx, pointers));

	return curnode;
}

double distance(vector<double> &p1, vector<double> &p2)
{
	int d = p1.size();
	double ans = 0.0;
	for(int i = 0; i < d; ++i)
		ans = ans + (p1[i]-p2[i])*(p1[i]-p2[i]);
	return ans;
}

bool lexi_compare(vector<double> &p1, vector<double> &p2)	//return true if p1 lexicographically smaller than p2
{
	int d = p1.size();
	for(int i = 0; i < d; ++i)
	{
		if(p1[i] != p2[i])
			return p1[i] < p2[i];
	}
}

double mbr_distance(int mbr_min_idx, int mbr_max_idx, vector<double> &query_point)
{
	double ans = 0.0;
	int d = query_point.size();
	for(int i = 0; i < d; ++i)
	{
		if(query_point[i] < mbr_min[mbr_min_idx][i])
			ans = ans+ (mbr_min[mbr_min_idx][i]-query_point[i])*(mbr_min[mbr_min_idx][i]-query_point[i]);
		else
		if(query_point[i] > mbr_max[mbr_max_idx][i])
			ans = ans+ (query_point[i]-mbr_max[mbr_max_idx][i])*(query_point[i]-mbr_max[mbr_max_idx][i]);
	}
	return ans;
}

void bestFirstSearch(Node *pointers[], vector<double> &query_point, priority_queue<pair<double, int>> &candidates, priority_queue<pair<double, int>> &answer)
{
	// TODO: Implement best first search and find the times for 20NN queries. This will complete this file's part.
	while(true)
	{
		counter++;
		if(candidates.size() == 0)
			return;
		pair<double, int> P = candidates.top(), Q;
		candidates.pop();
		if(answer.size() >= 20)
		{
			Q = answer.top();
			if(Q.first < -P.first)
				return;
		}
		Node *curnode = pointers[P.second];
		int curpoint_idx = curnode->getPointIdx();
		double cur_distance = distance(datapoints[curpoint_idx], query_point);
		
		if(answer.size() >= 20)
		{
			if(cur_distance < Q.first)
			{
				answer.pop();
				answer.push(make_pair(cur_distance, curnode->getID()));
			}
			else
			if(cur_distance == Q.first)
			{
				if(lexi_compare(datapoints[curpoint_idx], datapoints[pointers[Q.second]->getPointIdx()]))
				{
					answer.pop();
					answer.push(make_pair(cur_distance, curnode->getID()));
				}
			}
		}
		else
		{	
			answer.push(make_pair(cur_distance, curnode->getID()));
		}
		Q = answer.top();
		Node *LChild = curnode->getLChild(), *RChild = curnode->getRChild();
		double lchild_distance, rchild_distance;
		if(LChild != NULL)
		{
			lchild_distance = mbr_distance(LChild->getMinMBRIdx(), LChild->getMaxMBRIdx(), query_point);
			if(answer.size() >= 20)
			{
				if(lchild_distance <= Q.first)
					candidates.push(make_pair(-lchild_distance, LChild->getID()));		
			}
			else
			{
				candidates.push(make_pair(-lchild_distance, LChild->getID()));			
			}
		}
		if(RChild != NULL)
		{
			rchild_distance = mbr_distance(RChild->getMinMBRIdx(), RChild->getMaxMBRIdx(), query_point);
			if(answer.size() >= 20)
			{
				if(rchild_distance <= Q.first)
					candidates.push(make_pair(-rchild_distance, RChild->getID()));			
			}
			else
			{
				candidates.push(make_pair(-rchild_distance, RChild->getID()));			
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
		//First, take in the tuples
		datapoints.resize(N);
		mbr_min.resize(N+1);	//Should be N+1, but just testing
		mbr_max.resize(N+1);	////Should be N+1, but just testing
		indexes.resize(D);
		for(int i = 0; i < N; ++i)
		{
			datapoints[i].resize(D);
			for(int j = 0; j < D; ++j)
			{
				cin>>data;
				datapoints[i][j] = data;
			}
		}
		fclose(stdin);

		//Now we will have to sort the tuples. Sorting is maintained by instead sorting an integer array of indexes. The comparator function looks into the datapoints instead.
		//Sorting needs to be maintained wrt each dimension.
		for(int i = 0; i < D; ++i)
		{
			indexes[i].resize(N);
			for(int j = 0; j < N; ++j)
				indexes[i][j] = j;
			sort_dim = i;
			sort(indexes[i].begin(), indexes[i].end(), comparator);
		} 

		vector<double> new_mbr_min(D, 0.0), new_mbr_max(D, 1.0);
		mbr_min[0] = new_mbr_min;
		mbr_max[0] = new_mbr_max;
		Node *pointers[N];

		counter = 0;
		Node *head = buildTree(0, D, 0, N-1, 0, 0, pointers);	//Build the KD Tree
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

			priority_queue<pair<double, int>> candidates, answer;		//Candidates is min heap, answer is max heap
			candidates.push(make_pair(-0.0, 0));	//Initially the root MBR is present
			
			vector<double> query_point;
			query_point.resize(D);
			for(int i = 0; i < D; ++i)
			{
				cin>>query_point[i];
			}
			//Now start finding kNN
			bestFirstSearch(pointers, query_point, candidates, answer);

			filename = pathname+"/"+to_string(i+1)+".txt";
			freopen(filename.c_str(), "w", stdout);
			vector<int> ans;
			ans.resize(20);
			int k = 0;

			while(!answer.empty())
			{
				ans[k] = pointers[answer.top().second]->getPointIdx();
				++k;
				answer.pop();
			}

			for(int i = k-1; i>=0; --i)
			{
				for(int j = 0; j < D; ++j)
					cout<<datapoints[ans[i]][j]<<" ";
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