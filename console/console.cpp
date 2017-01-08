// console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

constexpr int no_white = numeric_limits<int>::max() - 1;
vector<int> GetDistances(const string& pixels)
{
	vector<int> dists(pixels.size(), no_white);
	int white = pixels.size();
	for (int i = 0; i < pixels.size(); i++)
	{
		if (pixels[i] == '1')
		{
			dists[i] = 0;
			// backtrack
			for (int j = i - 1; j >= 0; j--)
			{
				if (dists[j] > i - j) dists[j] = i - j;
				else break;
			}
			white = i;
		}
		else
		{
			if (white < pixels.size())
				dists[i] = i - white;
		}
	}
	return dists;
}

string GetDistances(const vector<string>& pixels)
{
	const int rows = pixels.size();
	const int cols = pixels.front().length();

	vector<vector<int>> dists;
	dists.reserve(rows);
	for (const auto& row : pixels)
		dists.push_back(GetDistances(row));

	// go column by column
	for (int col = 0; col < cols; col++)
	{
		for (int row = 1; row < rows; row++)
		{
			if (dists[row][col] > dists[row - 1][col] + 1)
				dists[row][col] = dists[row - 1][col] + 1;
			else
			{
				for (int j = row - 1; j >= 0; j--)
				{
					if (dists[j][col] > dists[row][col] + (row - j)) dists[j][col] = dists[row][col] + (row - j);
					else break;
				}
			}
		}
	}

	string result("");
	for (auto& row : dists)
	{
		for (auto& d : row)
		{
			result.append(to_string(d) + " ");
		}
		result.resize(result.size() - 1);
		result.append("\n");
	}
	return result;
}

int main()
{
	long tests;
	cin >> tests;
	vector<string> results;

	while (results.size() < tests)
	{
		int rows; 
		int cols;
		cin >> rows >> cols;

		vector<string> bitmap;
		bitmap.reserve(rows);
		for (int i = 0; i < rows; i++)
		{
			string row;
			cin >> row;
			bitmap.push_back(row);
		}
		results.push_back(GetDistances(bitmap));
	}
	
	for (auto r : results) cout << r;

	char q;
	cin >> q;
	return 0;
}

