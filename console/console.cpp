// console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class CStonesCollector
{
	vector<long> m_cache;

public:
	CStonesCollector(vector<long> first_row)
		: m_cache(first_row)
	{
	}

	long GetCurrentMax()
	{
		if (m_cache.empty()) return 0;

		return *max_element(m_cache.begin(), m_cache.end());
	}

	void AddRow(const vector<long> row)
	{
		if (m_cache.empty()) return;

		if (m_cache.size() == 1)
		{
			m_cache[0] += row[0];
			return;
		}

		vector<long> cache(m_cache.size(), 0);
		cache[0] = row[0] + max(m_cache[0], m_cache[1]);
		cache[m_cache.size() - 1] = row.back() + max(m_cache[m_cache.size() - 1], m_cache[m_cache.size() - 2]);

		for (size_t i = 1; i < m_cache.size() - 1; i++)
			cache[i] = row[i] + max(m_cache[i - 1], max(m_cache[i], m_cache[i + 1]));

		m_cache.swap(cache);
	}
};

int main()
{
	size_t tests;
	cin >> tests;
	vector<long> results;
	while (results.size() < tests)
	{
		int h, w;
		cin >> h >> w;
		if (h == 0)
		{
			results.push_back(0);
			continue;
		}

		// first row
		vector<long> frow(w, 0);
		for (int i = 0; i < w; i++) cin >> frow[i];

		CStonesCollector sc(frow);

		for (int j = 1; j < h; j++)
		{
			vector<long> row(w, 0);
			for (int i = 0; i < w; i++) cin >> row[i];
			sc.AddRow(row);
		}

		results.push_back(sc.GetCurrentMax());
	}

	for (size_t r = 0; r < results.size(); r++)
		cout << results[r] << endl;

	return 0;
}

