#include<bits/stdc++.h>

using namespace std;

int main()
{
	freopen("cases.txt", "w", stdout); 
	for(int i = 1 ; i <= 500000; i++)
	{
		cout<<"INSERT INTO registers (student_id, course_id) VALUES ('"<<i<<"', '"<<i<<"');"<<endl;
	}
	return 0;
}