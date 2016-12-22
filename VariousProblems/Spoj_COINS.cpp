// http://www.spoj.com/problems/COINS/

#include "stdafx.h"

#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <unordered_map>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

#if 0
namespace SPOJ
{
	class CoinExchange
	{
		unordered_map<long, unsigned long> seen;

		void Reset()
		{
			seen.clear();
			seen[0] = 0;
			seen[1] = 1;
			seen[2] = 2;
			seen[3] = 3;
		}
	public:
		CoinExchange()
		{
			Reset();
		}

		unsigned long Exchange(long coin)
		{
			if (seen.size() > 10000000) Reset();
			auto fourth = (seen.count(coin / 4) == 1) ? seen[coin / 4] : Exchange(coin / 4);
			auto third = (seen.count(coin / 3) == 1) ? seen[coin / 3] : Exchange(coin / 3);
			auto half = (seen.count(coin / 2) == 1) ? seen[coin / 2] : Exchange(coin / 2);

			seen[coin] = max(static_cast<unsigned long>(coin), half + third + fourth);
			return seen[coin];
		}

	};

	int main()
	{
		vector<long> coins;
		long c;
		while (coins.size() < 10 && cin >> c)
			coins.push_back(c);

		CoinExchange cs;
		for (auto coin : coins)
			cout << cs.Exchange(coin) << endl;

		char quit;
		std::cin >> quit;
		return 0;
	}
}
#endif