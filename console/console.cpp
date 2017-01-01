// console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

long SellTreats_DP(const vector<int>& treats)
{
	if (treats.empty()) return 0;

	vector<long> profit(treats.size());
	transform(treats.begin(), treats.end(), profit.begin(), [&](int t) { return treats.size() * t;});

	for (int day = treats.size() - 1; day > 0; day--)
	{
		for (int j = 0; j < day; j++)
		{
			profit[j] = max(day*treats[j] + profit[j + 1], day*treats[j + treats.size() - day] + profit[j]);
		}
		profit.resize(day);
	}
	return profit[0];
}

int main()
{
	int c;
	cin >> c;

	vector<int> treats;
	treats.reserve(c);
	for (int i = 0; i < c; i++)
	{
		int t;
		cin >> t;
		treats.push_back(t);
	}
	
	cout << SellTreats_DP(treats) << endl;
	
	char q;
	cin >> q;
	return 0;
}

