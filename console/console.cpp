// console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int MakePalinCost(const string& s)
{
	if (s.length() < 2) return 0;

	vector<int> costs_prev(s.length(), 0);
	vector<int> costs(s.length() - 1, 0);
	for (int i = 0; i < costs.size(); i++) costs[i] = (s[i] == s[i + 1]) ? 0 : 1;

	vector<int> cur;
	while (costs.size() > 1)
	{
		cur.resize(costs.size() - 1);
		for (int i = 0; i < cur.size(); i++)
		{
			if (s[i] == s[i + s.length() - cur.size()]) cur[i] = costs_prev[i + 1];
			else cur[i] = 1 + min(costs[i], costs[i + 1]);
		}
		costs_prev.swap(costs);
		costs.swap(cur);
	}
	return costs.front();
}

int main()
{
	long c;
	cin >> c;
	vector<int> results;
	while (results.size() < c)
	{
		string s;
		cin >> s;
		results.push_back(MakePalinCost(s));
	}
	
	for (auto r : results) cout << r << endl;

	char q;
	cin >> q;
	return 0;
}

