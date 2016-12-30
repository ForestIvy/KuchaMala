// http://www.spoj.com/problems/STPAR/

#include "stdafx.h"
#include "CppUnitTest.h"

#include <algorithm>
#include <queue>
#include <stack>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

#if 0
namespace SPOJ
{
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

	bool CanPass(const vector<int>& cars)
	{
		queue<int> pending;
		for (auto c : cars) pending.push(c);

		return CanPass(pending);
	}

	TEST_CLASS(STPAR)
	{
	public:
		TEST_METHOD(SingleCar)
		{
			Assert::IsTrue(CanPass(vector<int>{1}));
		}

		TEST_METHOD(TwoCars)
		{
			Assert::IsTrue(CanPass(vector<int>{1, 2}), L"1 2");
			Assert::IsTrue(CanPass(vector<int>{2, 1}), L"2 1");
		}

		TEST_METHOD(ThreeCars)
		{
			Assert::IsTrue(CanPass(vector<int>{2, 1, 3}), L"2 1 3");
			Assert::IsFalse(CanPass(vector<int>{2, 3, 1}), L"2 3 1");
		}

		TEST_METHOD(FromSpoj)
		{
			Assert::IsTrue(CanPass(vector<int>{5, 1, 2, 4, 3}), L"5 1 2 4 3");
			Assert::IsFalse(CanPass(vector<int>{4, 1, 5, 3, 2}), L"4 1 5 3 2");
		}

		TEST_METHOD(MaxSize_Yes)
		{
			vector<int> cars(1000, 0);
			generate(cars.begin(), cars.end(), []() { static int i = 1001; i--; return i; });
			Assert::IsTrue(CanPass(cars), L"1000 999 ... 3 2 1");
		}

		TEST_METHOD(MaxSize_No)
		{
			vector<int> cars(1000, 0);
			generate(cars.begin(), cars.end(), []() { static int i = 1001; i--; return i; });
			cars[41] = 715;
			cars[714] = 42;
			Assert::IsFalse(CanPass(cars), L"1000 999 ... 3 2 1");
		}
	};
}
#endif