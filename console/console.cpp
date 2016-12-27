// console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int EditDistance(const string& first, const string& second)
{
	const string& shorter = (first.length() <= second.length()) ? first : second;
	const string& longer = (first.length() <= second.length()) ? second : first;

	if (shorter.empty()) return longer.length();

	vector<int> prev_i(shorter.length(), 0);
	for (int k = 0; k < prev_i.size(); k++) prev_i[k] = k + 1;

	for (int i = 0; i < longer.length(); i++)
	{
		vector<int> prev_j(shorter.length(), 0);
		prev_j[0] = (shorter[0] == longer[i]) ? i : min(1 + i, 1 + prev_i[0]);

		for (int j = 1; j < shorter.length(); j++)
		{
			int cand = 1 + prev_i[j]; // delete char in longer
			cand = min(cand, 1 + prev_j[j - 1]); // delete char in shorter

			if (shorter[j] == longer[i]) cand = min(cand, prev_i[j - 1]);
			else cand = min(cand, 1 + prev_i[j - 1]);

			prev_j[j] = cand;
		}
		prev_i = prev_j;
	}
	return prev_i.back();
}

int main()
{
	int tests;
	cin >> tests;
	vector<int> results;
	for (int i = 0; i < tests; i++)
	{
		string first, second;
		cin >> first;
		cin >> second;
		results.push_back(EditDistance(first, second));
	}
	
	for (auto r : results)
		cout << r << endl;

	char q;
	cin >> q;
	return 0;
}

