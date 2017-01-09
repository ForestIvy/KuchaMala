// console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <deque>

using namespace std;

template<typename T>
class queue_with_max
{
	queue<T> values;
	deque<T> cur_max;

public:
	queue_with_max() {}
	queue_with_max(const vector<T>& values)
	{
		for (auto i : values) push(i);
	}

	void push(T value)
	{
		values.push(value);
		while (!cur_max.empty() && cur_max.back() < value) cur_max.pop_back();
		cur_max.push_back(value);
	}

	void pop()
	{
		int v = values.front();
		values.pop();
		if (v == cur_max.front()) cur_max.pop_front();
	}

	T get_max()
	{
		return cur_max.front();
	}
};

string GetMaxInRange_Queue(const vector<long>& v, size_t k)
{
	string maxInSub("");

	queue_with_max<long> q;
	for (size_t i = 0; i < k - 1; i++) q.push(v[i]);

	for (size_t i = k - 1; i < v.size(); i++)
	{
		q.push(v[i]);
		maxInSub.append(to_string(q.get_max()) + " ");
		q.pop();
	}
	if (!maxInSub.empty()) maxInSub.resize(maxInSub.size() - 1);
	return maxInSub;
}
int main()
{
	size_t n;
	cin >> n;
	vector<long> values;
	values.reserve(n);
	long v;
	for (auto i = 0; i < n; i++)
	{
		cin >> v;
		values.push_back(v);
	}
	size_t k;
	cin >> k;

	cout << GetMaxInRange_Queue(values, k) << endl;

	char q;
	cin >> q;
	return 0;
}

