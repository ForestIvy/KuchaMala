// http://www.spoj.com/problems/CSTREET/

#include "stdafx.h"

#include <vector>
#include <string>
#include <functional>
#include <unordered_set>
#include <iostream>

using namespace std;

#if 0
struct Edge
{
	unsigned v1 = 0;
	unsigned v2 = 0;
	long cost = 0;

	Edge(unsigned v1_, unsigned v2_, long cost_) : v1(v1_), v2(v2_), cost(cost_) {}
};

long GetMSTCost(const unordered_set<unsigned>& vertices, const vector<Edge>& edges)
{
	unordered_set<unsigned> v_seen;
	v_seen.insert(edges.front().v1);

	long mst_cost = 0;
	while (v_seen.size() < vertices.size())
	{
		long min_e = 0;
		bool first = true;
		Edge found{ 0,0,0 };
		for (auto& e : edges)
		{
			if (v_seen.count(e.v1) == 1 && v_seen.count(e.v2) == 0 ||
				v_seen.count(e.v2) == 1 && v_seen.count(e.v1) == 0)
			{
				if (first || e.cost < min_e)
				{
					min_e = e.cost;
					found = e;
				}
				first = false;
			}
		}		v_seen.insert(found.v1);
		v_seen.insert(found.v2);
		mst_cost += min_e;
	}

	return mst_cost;
}

int main()
{
	int tests;
	cin >> tests;

	vector<long> costs;
	costs.reserve(tests);
	while (costs.size() < tests)
	{
		int price;
		cin >> price;

		int v_count;
		cin >> v_count;
		int e_count;
		cin >> e_count;

		vector<Edge> edges;
		edges.reserve(e_count);
		unordered_set<unsigned> vertices;

		while (edges.size() < e_count)
		{
			unsigned v1, v2;
			long cost;
			cin >> v1;
			cin >> v2;
			cin >> cost;

			edges.push_back(Edge{ v1, v2, cost });
			vertices.insert(v1);
			vertices.insert(v2);
		}
		long mst = GetMSTCost(vertices, edges);
		costs.push_back(mst*price);
	}

	for (auto c : costs)
		cout << c << endl;

	char quit;
	cin >> quit;
	return 0;
}
#endif
