// console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Item
{
	int size = 0;
	int value = 0;
	Item(int s, int v) : size(s), value(v) {}
};

Item Fill(int capacity, const vector<Item>& items)
{
	vector<int> values_prev(capacity + 1, 0);

	for (int i = 0; i < items.size(); i++)
	{
		vector<int> values(capacity + 1, 0);
		for (int cur_cap = 1; cur_cap <= capacity; cur_cap++)
		{
			if (items[i].size > cur_cap)
			{
				values[cur_cap] = values_prev[cur_cap];
			}
			else
			{
				int v_take = items[i].value + values_prev[cur_cap - items[i].size];
				int v_skip = values_prev[cur_cap];
				values[cur_cap] = max(v_take, v_skip);
			}
		}
		values_prev = values;
	}

	auto it = find_if_not(values_prev.rbegin(), values_prev.rend(), [&](int v) { return v == values_prev.back();});
	return Item(values_prev.rend() - it, values_prev.back());
}

int main()
{
	int capacity, citems;
	cin >> capacity >> citems;
	vector<Item> results;
	while (capacity != 0 || citems != 0)
	{
		vector<Item> items;
		items.reserve(citems);
		for (int i = 0; i < citems; i++)
		{
			int s, v;
			cin >> s >> v;
			items.push_back(Item(s, v));
		}
		results.push_back(Fill(capacity, items));

		cin >> capacity >> citems;
	}

	for (auto r : results)
		cout << r.size << " " << r.value << endl;

	char q;
	cin >> q;
	return 0;
}

