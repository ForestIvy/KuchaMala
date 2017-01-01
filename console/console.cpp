// console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct CoinCollector
{
	long long prev1 = 0;
	long long prev2 = 0;

	void Inspect(long coin)
	{
		auto cur = max(coin + prev2, prev1);
		prev2 = prev1;
		prev1 = cur;
	}
};


int main()
{
	int tests;
	cin >> tests;
	vector<long long> results;

	while (results.size() < tests)
	{
		int ncoins;
		cin >> ncoins;

		CoinCollector cc;
		for (int i = 0; i < ncoins; i++)
		{
			long coin;
			cin >> coin;
			cc.Inspect(coin);
		}
		results.push_back(cc.prev1);
	}
	
	for (int i = 0; i < results.size(); i++)
		cout << "Case " << i + 1 << ": " << results[i] << endl;
	
	char q;
	cin >> q;
	return 0;
}

