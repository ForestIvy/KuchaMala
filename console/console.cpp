// console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <iostream>

using namespace std;

class CAggrCow
{
	vector<int> m_v;
public:
	CAggrCow(vector<int> v)
		: m_v(move(v))
	{
		if (m_v.size() < 2) throw;
		sort(m_v.begin(), m_v.end());
	}

	int MinInterval()
	{
		int minInterval = MaxInterval();
		for (auto i = 1; i < m_v.size(); i++)
		{
			auto cand = m_v[i] - m_v[i - 1];
			if (cand < minInterval)
				minInterval = cand;
		}
		return minInterval;
	}

	int MaxInterval()
	{
		return m_v.back() - m_v.front();
	}

	int CowsAsCloseAs(int dist)
	{
		int cows = 1;
		int cur_dist = 0;
		for (auto i = 1; i < m_v.size(); i++)
		{
			cur_dist += m_v[i] - m_v[i - 1];
			if (cur_dist >= dist)
			{
				cows++;
				cur_dist = 0;
			}
		}
		return cows;
	}

	int SpacingFor(int cows)
	{
		int low = MinInterval();
		int high = MaxInterval();

		while (low < high)
		{
			int mid = low + (high + 1 - low) / 2;
			int at_mid = CowsAsCloseAs(mid);

			if (at_mid >= cows) low = mid;
			else
			{
				if (high == mid)
					return CowsAsCloseAs(high) < cows ? low : high;

				high = mid;
			}
		}
		return high;
	}
};

int main()
{
	int tests;
	std::cin >> tests;

	vector<int> results;
	for (int cur_test = 0; cur_test < tests; cur_test++)
	{
		int N, C;
		std::cin >> N;
		std::cin >> C;

		vector<int> points;
		points.reserve(N);
		for (int p = 0; p < N; p++)
		{
			int point;
			std::cin >> point;
			points.push_back(point);
		}
		CAggrCow ac(points);
		results.push_back(ac.SpacingFor(C));
	}

	for (auto i : results)
		cout << i << endl;

	char quit;
	std::cin >> quit;
	return 0;
}
