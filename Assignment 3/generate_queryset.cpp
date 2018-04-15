#include<bits/stdc++.h>

using namespace std;

int main()
{
	cout<<setprecision(20)<<fixed;		//Probabilistically good
	system("mkdir queryset");
	default_random_engine generator;
	uniform_real_distribution<double> distribution(0.0,1.0);
	int d[] = {2, 3, 5, 10, 15, 20};
	for(int i = 0; i <= 5; i++)
	{
		string filename = "queryset/queryset_"+to_string(d[i])+".txt";
		freopen(filename.c_str(), "w", stdout);
		for(int k = 0; k < 100; k++)
		{
			for(int j = 0; j < d[i]; j++)
			{
				cout<<distribution(generator)<<" ";
			}
			cout<<"\n";
		}
		fclose(stdout);
	}
	return 0;
}