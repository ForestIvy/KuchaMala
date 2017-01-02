// console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

long GetBestOffer(long budget, const vector<long>& hotels)
{
	long offer = 0;
	auto s = hotels.begin();
	auto e = hotels.begin();

	long cur = 0;
	while (s != hotels.end())
	{
		if (budget - cur < *e)
		{
			cur -= *s;
			++s;
		}
		else
		{
			cur += *e;
			if (offer < cur) offer = cur;

			++e;
			if (e == hotels.end()) return offer;
		}
	}

	return offer;
}

int main()
{
	long c, budget;
	cin >> c >> budget;
	
	vector<long> hotels;
	hotels.reserve(c);
	for (long i = 0; i < c; i++)
	{
		long h;
		cin >> h;
		hotels.push_back(h);
	}
	cout << GetBestOffer(budget, hotels) << endl;

	char q;
	cin >> q;
	return 0;
}

