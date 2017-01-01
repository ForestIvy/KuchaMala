// http://www.spoj.com/problems/FARIDA

#include "stdafx.h"
#include "CppUnitTest.h"

#include <algorithm>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

#if 1
namespace SPOJ
{
	long long CollectCoins(const vector<long>& coins)
	{
		if (coins.empty()) return 0;
		if (coins.size() == 1) return coins[0];
		if (coins.size() == 2) return max(coins[0], coins[1]);

		long long prev1 = max(coins[0], coins[1]);
		long long prev2 = coins[0];
		for (int i = 2; i < coins.size(); i++)
		{
			auto cur = max(coins[i] + prev2, prev1);
			prev2 = prev1;
			prev1 = cur;
		}
		return prev1;
	}

	struct CoinCollector
	{
		long long prev1 = 0;
		long long prev2 = 0;

		void Inspect(long coin)
		{
			auto cur = max(coin + prev2, prev1);
			prev2 = prev1;
			prev1 = cur;
		}
	};

	TEST_CLASS(FARIDA)
	{
		string CollectCoins_(const vector<long>& coins)
		{
			CoinCollector cc;
			for (auto c : coins) cc.Inspect(c);
			return to_string(cc.prev1);
		}

	public:
		TEST_METHOD(SingleMonster)
		{
			Assert::AreEqual<string>("7", CollectCoins_(vector<long>{7}));


		}

		TEST_METHOD(TwoMonsters)
		{
			Assert::AreEqual<string>("7", CollectCoins_(vector<long>{7, 4}), L"7 4");
			Assert::AreEqual<string>("7", CollectCoins_(vector<long>{4, 7}), L"4 7");
		}

		TEST_METHOD(ThreeMonsters)
		{
			Assert::AreEqual<string>(to_string(7 + 3), CollectCoins_(vector<long>{3, 4, 7}), L"3 4 7");
			Assert::AreEqual<string>(to_string(12), CollectCoins_(vector<long>{3, 12, 7}), L"3 12 7");
		}

		TEST_METHOD(FourMonsters)
		{
			Assert::AreEqual<string>(to_string(3 + 7), CollectCoins_(vector<long>{3, 4, 7, 5}), L"3 4 7 5");
			Assert::AreEqual<string>(to_string(6 + 5), CollectCoins_(vector<long>{3, 6, 7, 5}), L"3 6 7 5");
			Assert::AreEqual<string>(to_string(7 + 5), CollectCoins_(vector<long>{7, 5, 4, 5}), L"7 5 4 5");
		}

		TEST_METHOD(MaxMonsters)
		{
			Assert::AreEqual<string>("5000000000000", CollectCoins_(vector<long>(10000,1000000000)));
		}
	};
}
#endif