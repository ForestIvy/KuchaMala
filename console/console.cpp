// console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>

using namespace std;

bool CanPass(queue<int>& pending)
{
	int last_through = 0;
	stack<int> side;
	while (!pending.empty() || !side.empty())
	{
		if (!pending.empty() && pending.front() == last_through + 1)
		{
			pending.pop();
			last_through++;
		}
		else if (!side.empty() && side.top() == last_through + 1)
		{
			side.pop();
			last_through++;
		}
		else if (!pending.empty())
		{
			side.push(pending.front());
			pending.pop();
		}
		else
		{
			return false;
		}
	}
	return true;
}

int main()
{
	vector<string> results;
	int car_count;
	cin >> car_count;
	while (car_count > 0)
	{
		queue<int> pending;
		for (int i = 0; i < car_count; i++)
		{
			int car;
			cin >> car;
			pending.push(car);
		}
		results.push_back(CanPass(pending) ? "yes" : "no");

		cin >> car_count;
	}

	for (const auto& r : results)
		cout << r << endl;

	char q;
	cin >> q;
	return 0;
}

