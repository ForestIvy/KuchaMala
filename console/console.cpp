// console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <stack>

using namespace std;

class CTree
{
	unordered_map<int /*vertex*/, unordered_set<int> /*incident vertices*/> m_vs;
	int m_root = -1;

public:
	CTree()	{}
	void AddEdge(int v1, int v2)
	{
		m_root = v1;
		m_vs[v1].insert(v2);
		m_vs[v2].insert(v1);
	}

	pair<int /*vertex*/, int /*distance*/> FindFurthestFrom(int start)
	{
		unordered_set<int> seen;
		seen.insert(start);
		stack<int> in_progress;
		in_progress.push(start);

		int cand = start;
		int max_dist = 0;

		int dist = 0;
		while (!in_progress.empty())
		{
			int cur = in_progress.top();
			bool f_pop = true;
			for (auto v : m_vs[cur])
			{
				if (seen.count(v) == 0)
				{
					dist++;
					in_progress.push(v);
					seen.insert(v);
					f_pop = false;
					break;
				}
			}

			if (f_pop)
			{
				if (dist > max_dist)
				{
					max_dist = dist;
					cand = cur;
				}
				dist--;
				in_progress.pop();
			}
		}

		return make_pair(cand, max_dist);
	}

	int LongestPath()
	{
		auto furthest_from_root = FindFurthestFrom(m_root);
		return FindFurthestFrom(furthest_from_root.first).second;
	}
};

int main()
{
	int e_count = 0;
	cin >> e_count;
	e_count--;

	CTree t;
	for (int i = 0; i < e_count; i++)
	{
		int v1, v2;
		cin >> v1;
		cin >> v2;

		t.AddEdge(v1, v2);
	}
	cout << t.LongestPath() << endl;

	char q;
	cin >> q;
	return 0;
}

