// console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <iostream>

using namespace std;

int main()
{
	long tests = 0;
	cin >> tests;

	vector<long long> inversions;
	inversions.reserve(tests);
	for (long i = 0; i < tests; i++)
	{
		long n = 0;
		cin >> n;
		vector<long> v;
		v.reserve(n);
		for (long j = 0; j < n; j++)
		{
			long a;
			cin >> a;
			v.push_back(a);
		}
		//inversions.push_back(CountInversions(v, 0, v.size() - 1));
	}

	cout << endl;
	for (auto i : inversions)
		cout << i << endl;

	char quit;
	std::cin >> quit;
	return 0;
}
