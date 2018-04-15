//For now, completed
#include<iostream>
#include<stdio.h>
#include <stdlib.h> 
#include<queue>

using namespace std;

//Stores the datapoints
vector<vector<double>> datapoints;

double distance(vector<double> &p1, vector<double> &p2)
{
	int d = p1.size();
	double ans = 0.0;
	for(int i = 0; i < d; i++)
		ans = ans + (p1[i]-p2[i])*(p1[i]-p2[i]);
	return ans;
}

bool lexi_compare(vector<double> &p1, vector<double> &p2)	//return true if p1 lexicographically smaller than p2
{
	int d = p1.size();
	for(int i = 0; i < d; i++)
	{
		if(p1[i] != p2[i])
			return p1[i] < p2[i];
	}
}

void sequentialScan(int d)	//for the dimension
{
	double average_time = 0.0;
	clock_t begin = clock();
	string filename = "queryset/queryset_"+to_string(d)+".txt";
	freopen(filename.c_str(), "r", stdin);
	string pathname = "seqscan_20NN/"+to_string(d);
	string makedir = "mkdir "+pathname;
	system(makedir.c_str());
	for(int i = 0; i < 100; i++)	//Average time for 100 queries, in given dimension
	{	
		vector<double> point;
		point.resize(d);
		for(int j = 0; j < d; j++)
			cin>>point[j];
		priority_queue<pair<double, int>> Q;
		int N = datapoints.size();
		for(int j = 0; j < N; j++)
		{
			double dist_val = distance(point, datapoints[j]);
			if(Q.size() < 20)
			{
				Q.push(make_pair(dist_val, j));
			}
			else
			{
				if(Q.top().first > dist_val)
				{
					Q.pop();
					Q.push(make_pair(dist_val, j));
				}
				else
				if(Q.top().first == dist_val)
				{
					if(lexi_compare(datapoints[j], datapoints[Q.top().second]))
					{
						Q.pop();
						Q.push(make_pair(dist_val, j));
					}
				}
			}
		}
		filename = pathname+"/"+to_string(i+1)+".txt";
		freopen(filename.c_str(), "w", stdout);
		vector<vector<double>> ans;
		vector<double> distances;
		ans.resize(20);
		distances.resize(20);
		int k=0;
		while(!Q.empty())
		{
			ans[k] = datapoints[Q.top().second];
			distances[k] = Q.top().first;
			Q.pop();
			k++;
		}
		while(k > 0)
		{
			for(int t = 0; t < ans[k-1].size(); t++)
				cout<<ans[k-1][t]<<" ";
			cout<<endl;
			k--;
		}
		fclose(stdout);
	}
	fclose(stdin);
	filename = pathname+"/"+"average_time.txt";
	freopen(filename.c_str(), "w", stdout);
	clock_t end = clock();
	average_time = double(end-begin)/CLOCKS_PER_SEC;
	average_time/=100;
	cout<<"Average time to find 20NN using sequential scan for dimension "<<d<<" is "<<average_time<<endl;
	fclose(stdout);
	freopen("seqscan_time.txt", "a", stdout);
	cout<<average_time<<endl;
	fclose(stdout);
}


int main()
{
	system("mkdir seqscan_20NN");
	freopen("seqscan_time.txt", "w", stdout);
	fclose(stdout);
	int d[] = {2, 3, 5, 10, 15, 20};
	for(int r = 0 ; r <= 5; r++)
	{
		string filename = "dataset/dataset_"+to_string(d[r])+".txt";
		freopen(filename.c_str(), "r", stdin);
		int N, D;
		double data;
		cin>>D>>N;
		//First, take in the tuples
		datapoints.resize(N);
		for(int i = 0; i < N; i++)
		{
			datapoints[i].resize(D);
			for(int j = 0; j < D; j++)
			{
				cin>>data;
				datapoints[i][j] = data;
			}
		}
		fclose(stdin);
		//Now start finding kNN
		sequentialScan(D);
	}
	return 0;
}