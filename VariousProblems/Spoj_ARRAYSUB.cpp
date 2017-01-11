// http://www.spoj.com/problems/ARRAYSUB/

#include "stdafx.h"
#include "CppUnitTest.h"

#include <algorithm>
#include <vector>
#include <numeric>
#include <queue>
#include <deque>
#include <random>

#include "ToString.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

#if 0
namespace SPOJ
{
	vector<long> GetMaxInRange_BF(const vector<long>& v, size_t k)
	{
		vector<long> maxInSub;
		maxInSub.reserve(v.size() + 1 - k);

		auto prev = max_element(v.begin(), v.begin() + k);
		maxInSub.push_back(*prev);

		for (auto it = v.begin() + k; it != v.end(); ++it)
		{
			if (*it >= *prev) prev = it;
			else if (it - prev > k) prev = max_element(v.begin(), v.begin() + k);

			maxInSub.push_back(*prev);
		}
		return maxInSub;
	}

	template<typename T>
	class queue_with_max
	{
		queue<T> values;
		deque<T> cur_max;

	public:
		queue_with_max(){}
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

	vector<long> GetMaxInRange_Queue(const vector<long>& v, size_t k)
	{
		vector<long> maxInSub;
		maxInSub.reserve(v.size() + 1 - k);

		queue_with_max<long> q;
		for (size_t i = 0; i < k - 1; i++) q.push(v[i]);

		for (size_t i = k - 1; i < v.size(); i++)
		{
			q.push(v[i]);
			maxInSub.push_back(q.get_max());
			q.pop();
		}
		return maxInSub;
	}

	TEST_CLASS(ARRAYSUB)
	{
		string GetMaxInRange_(const vector<long>& v, size_t k)
		{
			return VectorToString(GetMaxInRange_Queue(v, k));
		}

		vector<long> values;

	public:
		ARRAYSUB()
		{
			for (size_t i = 0; i < 1000000; i++) values.push_back(i);
			shuffle(values.begin(), values.end(), std::default_random_engine(42));
		}

		TEST_METHOD(queue_with_max_general)
		{
			queue_with_max<int> q(vector<int>{1, 3, 7, 10, 2, 9, 3, 4, 1, 7, 4, 9, 8, 2});
			Assert::AreEqual(10, q.get_max());

			q.pop(); q.pop(); q.pop();
			Assert::AreEqual(10, q.get_max());

			q.pop();
			Assert::AreEqual(9, q.get_max());

			q.pop();
			Assert::AreEqual(9, q.get_max());

			q.push(12);
			Assert::AreEqual(12, q.get_max());
		}

		TEST_METHOD(queue_with_max_same_items)
		{
			queue_with_max<int> q(vector<int>{3, 3, 3});
			Assert::AreEqual(3, q.get_max());

			q.pop();
			Assert::AreEqual(3, q.get_max());

			q.pop();
		}

		TEST_METHOD(queue_with_max_deplete)
		{
			queue_with_max<int> q(vector<int>{3, 2, 1});
			Assert::AreEqual(3, q.get_max());

			q.pop(); q.pop();
			Assert::AreEqual(1, q.get_max());
		}

		TEST_METHOD(SubOfLength1)
		{
			Assert::AreEqual<string>("1 3 2", GetMaxInRange_(vector<long>{1, 3, 2}, 1));
		}

		TEST_METHOD(SubOfLength3)
		{
			Assert::AreEqual<string>("3 4 5 6 7", GetMaxInRange_(vector<long>{1,2,3,4,5,6,7}, 3));
			Assert::AreEqual<string>("7 6 5 4 3", GetMaxInRange_(vector<long>{7,6,5,4,3,2,1}, 3));
			Assert::AreEqual<string>("7 7 6 5 5", GetMaxInRange_(vector<long>{1,7,6,3,2,5,4}, 3));
		}

		TEST_METHOD(MaxOfTheArray)
		{
			Assert::AreEqual<string>("3", GetMaxInRange_(vector<long>{1, 3, 2}, 3));
		}

		TEST_METHOD(MaxSize_10_BF)
		{
			GetMaxInRange_BF(values, 10);
		}
		TEST_METHOD(MaxSize_10_Queue)
		{
			GetMaxInRange_Queue(values, 10);
		}

		TEST_METHOD(MaxSize_100_BF)
		{
			GetMaxInRange_BF(values, 100);
		}
		TEST_METHOD(MaxSize_100_Queue)
		{
			GetMaxInRange_Queue(values, 100);
		}

		TEST_METHOD(MaxSize_1000_BF)
		{
			GetMaxInRange_BF(values, 1000);
		}
		TEST_METHOD(MaxSize_1000_Queue)
		{
			GetMaxInRange_Queue(values, 1000);
		}

		TEST_METHOD(MaxSize_10000_BF)
		{
			GetMaxInRange_BF(values, 10000);
		}
		TEST_METHOD(MaxSize_10000_Queue)
		{
			GetMaxInRange_Queue(values, 10000);
		}

		TEST_METHOD(MaxSize_100000_Queue) // BF doesn't finish in reasonable time
		{
			GetMaxInRange_Queue(values, 100000);
		}
	};
}
#endif