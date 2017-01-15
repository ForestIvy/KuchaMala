// console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
	size_t n;
	cin >> n;
	vector<string> results;
	results.reserve(n);

	for (auto& r : results) cout << r << endl;

	char q;
	cin >> q;
	return 0;
}

