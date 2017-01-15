// console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>

using namespace std;

class BugColony
{
	int max_id;
	vector<vector<int>> relations;

public:
	BugColony(int id) : max_id(id), relations(max_id + 1, vector<int>()) {}

	bool AddRelationship(int one, int another)
	{
		if (max_id < max(one, another)) throw 0;
		relations[one].push_back(another);
		relations[another].push_back(one);
	}
	bool IsConforming()
	{
		if (relations.size() <= 2) return true;

		vector<int> seen(max_id + 1, -1);
		stack<int> in_progress;

		auto start_at = seen.begin() + 1;
		while (start_at != seen.end())
		{
			*start_at = 0;
			in_progress.push(start_at - seen.begin());
			while (!in_progress.empty())
			{
				int cur = in_progress.top();
				bool shouldPop = true;
				for (int i = 0; i < relations[cur].size(); i++)
				{
					int next = relations[cur][i];
					if (seen[next] == -1)
					{
						seen[next] = in_progress.size();
						in_progress.push(next);
						shouldPop = false;
						break;
					}
					else
					{
						int dist = in_progress.size() - seen[next];
						if (dist % 2 != 0) return false;
					}
				}
				if (shouldPop)
					in_progress.pop();
			}
			start_at = find_if(start_at, seen.end(), [](int n) { return n == -1;});
		}
		return true;
	}
};

bool IsConforming(int max_id, vector<pair<int, int>> rels)
{
	BugColony bc(max_id);
	for (auto& rel : rels) bc.AddRelationship(rel.first, rel.second);

	return bc.IsConforming();
}

int main()
{
	int cases;
	cin >> cases;
	vector<bool> results;

	while (results.size() < cases)
	{
		int id;
		long rel_count;
		cin >> id >> rel_count;
		BugColony bc{ id };
		for (int i = 0; i < rel_count; i++)
		{
			int f, s;
			cin >> f >> s;
			bc.AddRelationship(f, s);
		}
		results.push_back(bc.IsConforming());
	}

	for (int i = 0; i < cases; i++)
	{
		cout << "Scenario #" << to_string(i + 1) << ":" << endl;
		cout << (results[i] ? "No suspicious bugs found!" : "Suspicious bugs found!") << endl;
	}
	char q;
	cin >> q;
	return 0;
}

