#include<bits/stdc++.h>

using namespace std;

int main()
{
	cout<<setprecision(20)<<fixed;		//Probabilistically good
	system("mkdir dataset");
	default_random_engine generator;
	uniform_real_distribution<double> distribution(0.0,1.0);
	for(int d = 1; d <= 20; d++)
	{
		string filename = "dataset/dataset_"+to_string(d)+".txt";
		freopen(filename.c_str(), "w", stdout);
		cout<<d<<" 100000\n";
		for(int i = 0; i < 100000; i++)
		{
			for(int j = 0; j < d; j++)
			{
				cout<<distribution(generator)<<" ";
			}
			cout<<"\n";
		}
		fclose(stdout);
	}
	return 0;
}