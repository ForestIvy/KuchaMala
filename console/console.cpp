// console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <iostream>

using namespace std;


int main()
{
	vector<long> coins;
	long c;
	while (coins.size() < 10 && cin >> c)
		coins.push_back(c);
	

	char quit;
	std::cin >> quit;
	return 0;
}
