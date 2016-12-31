// http://www.spoj.com/problems/PARTY/

#include "stdafx.h"
#include "CppUnitTest.h"

#include <algorithm>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

#if 1
namespace SPOJ
{
	struct Item
	{
		int size = 0;
		int value = 0;
		Item(int s, int v) : size(s), value(v) {}
	};

	Item Fill(int capacity, vector<Item> items)
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

	TEST_CLASS(PARTY)
	{
	public:
		TEST_METHOD(SingleItemDoesNotFit)
		{
			auto res = Fill(10, vector<Item> { {15, 1}});
			Assert::AreEqual(0, res.size);
			Assert::AreEqual(0, res.value);
		}

		TEST_METHOD(SingleItemFits)
		{
			auto res = Fill(10, vector<Item> { {7, 1}});
			Assert::AreEqual(7, res.size);
			Assert::AreEqual(1, res.value);
		}

		TEST_METHOD(TwoItemsNeitherFits)
		{
			auto res = Fill(10, vector<Item> { {17, 1}, { 11, 2 }});
			Assert::AreEqual(0, res.size);
			Assert::AreEqual(0, res.value);
		}

		TEST_METHOD(TwoItemsOnlyFirstFits)
		{
			auto res = Fill(10, vector<Item> { {7, 1}, { 11, 2 }});
			Assert::AreEqual(7, res.size);
			Assert::AreEqual(1, res.value);
		}

		TEST_METHOD(TwoItemsOnlySecondFits)
		{
			auto res = Fill(10, vector<Item> { {17, 1}, { 4, 2 }});
			Assert::AreEqual(4, res.size);
			Assert::AreEqual(2, res.value);
		}

		TEST_METHOD(TwoItemsBothFit)
		{
			auto res = Fill(10, vector<Item> { {5, 1}, { 4, 2 }});
			Assert::AreEqual(9, res.size);
			Assert::AreEqual(3, res.value);
		}

		TEST_METHOD(TwoItemsSameSizeDifferntValue)
		{
			auto res = Fill(10, vector<Item> { {6, 1}, { 6, 2 }});
			Assert::AreEqual(6, res.size);
			Assert::AreEqual(2, res.value);
		}

		TEST_METHOD(TwoItemsSameValueDifferentSize)
		{
			auto res = Fill(10, vector<Item> { {5, 2}, { 6, 2 }});
			Assert::AreEqual(5, res.size);
			Assert::AreEqual(2, res.value);

			auto res2 = Fill(10, vector<Item> { {6, 2}, { 5, 2 }});
			Assert::AreEqual(5, res2.size);
			Assert::AreEqual(2, res2.value);

		}

		TEST_METHOD(ThreeItemsChoseTwo)
		{
			auto res = Fill(5, vector<Item> { {3, 4}, { 3, 5 }, { 2, 1 }});
			Assert::AreEqual(5, res.size);
			Assert::AreEqual(6, res.value);
		}

		TEST_METHOD(ThreeItemsChoseOne)
		{
			auto res = Fill(5, vector<Item> { {2, 4}, { 5, 8 }, { 2, 3 }});
			Assert::AreEqual(5, res.size);
			Assert::AreEqual(8, res.value);
		}

		TEST_METHOD(ThreeItemsSameValueDifferentSize)
		{
			auto res1 = Fill(5, vector<Item> { {2, 3}, { 5, 8 }, { 2, 5 }});
			Assert::AreEqual(4, res1.size);
			Assert::AreEqual(8, res1.value);

			auto res2 = Fill(5, vector<Item> { { 5, 8 }, { 2, 3 }, { 2, 5 }});
			Assert::AreEqual(4, res2.size);
			Assert::AreEqual(8, res2.value);

			auto res3 = Fill(5, vector<Item> { { 4, 8 }, { 3, 3 }, { 2, 5 }});
			Assert::AreEqual(4, res3.size);
			Assert::AreEqual(8, res3.value);
		}

		TEST_METHOD(SampleFromSpoj_1)
		{
			vector<Item> items{ { 12,3 },{ 15,8 },{ 16,9 },{ 16,6 },{ 10,2 },{ 21,9 },{ 18,4 },{ 12,4 },{ 17,8 },{ 18,9 } };
			auto res = Fill(50, items);
			Assert::AreEqual(49, res.size);
			Assert::AreEqual(26, res.value);
		}

		TEST_METHOD(SampleFromSpoj_2)
		{
			vector<Item> items{ { 13,8 },{ 19,10 },{ 16,8 },{ 12,9 },{ 10,2 },{ 12,8 },{ 13,5 },{ 15,5 },{ 11,7 },{ 16,2 } };
			auto res = Fill(50, items);
			Assert::AreEqual(48, res.size);
			Assert::AreEqual(32, res.value);

		}
	};
}
#endif