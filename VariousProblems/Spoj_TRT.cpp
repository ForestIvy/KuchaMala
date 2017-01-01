// http://www.spoj.com/problems/TRT

#include "stdafx.h"
#include "CppUnitTest.h"

#include <algorithm>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

#if 1
namespace SPOJ
{
	long SellTreats_DP(const vector<int>& treats)
	{
		if (treats.empty()) return 0;

		vector<long> profit(treats.size());
		transform(treats.begin(), treats.end(), profit.begin(), [&](int t) { return treats.size() * t;});

		for (int day = treats.size() - 1; day > 0; day--)
		{
			for (int j = 0; j < day; j++)
			{
				profit[j] = max(day*treats[j] + profit[j + 1], day*treats[j + treats.size() - day] + profit[j]);
			}
			profit.resize(day);
		}
		return profit[0];
	}

	long SellTreats_Greedy(const vector<int>& treats)
	{
		if (treats.empty()) return 0;

		long profit = 0;
		int i = 0;
		int j = treats.size() - 1;
		while (i <= j)
		{
			int day = treats.size() + i - j;
			if (treats[i] <= treats[j])
			{
				profit += treats[i] * day;
				i++;
			}
			else
			{
				profit += treats[j] * day;
				j--;
			}
		}
		return profit;
	}

	TEST_CLASS(TRT)
	{
		long SellTreats(const vector<int>& treats)
		{
			return SellTreats_DP(treats);
		}

	public:
		TEST_METHOD(SingleTreat)
		{
			Assert::AreEqual<long>(7, SellTreats(vector<int>{7}));
		}

		TEST_METHOD(TwoTreats)
		{
			Assert::AreEqual<long>(7*2+5, SellTreats(vector<int>{7, 5}));
		}

		TEST_METHOD(ThreeTreats)
		{
			Assert::AreEqual<long>(8 + 1 * 2 + 3 * 8, SellTreats(vector<int>{8, 1, 8}), L"8 1 8");
			Assert::AreEqual<long>(1 + 2 * 2 + 3 * 8, SellTreats(vector<int>{1, 2, 8}), L"1 2 8");
			Assert::AreEqual<long>(1 + 2 * 2 + 3 * 8, SellTreats(vector<int>{8, 2, 1}), L"8 2 1");
			Assert::AreEqual<long>(1 + 2 * 2 + 3 * 8, SellTreats(vector<int>{8, 2, 1}), L"1 8 2");
		}

		TEST_METHOD(FromSpoj)
		{
			Assert::AreEqual<long>(43, SellTreats(vector<int>{1, 3, 1, 5, 2}));
		}

		TEST_METHOD(MaxProfit)
		{
			Assert::AreEqual<long>(2001000000, SellTreats(vector<int>(2000,1000)));
		}

		TEST_METHOD(CounterForGreedy)
		{
			// greedy yields 71
			Assert::AreEqual<long>(76, SellTreats(vector<int>{5, 4, 3, 2, 1, 6}));
		}
	};
}
#endif