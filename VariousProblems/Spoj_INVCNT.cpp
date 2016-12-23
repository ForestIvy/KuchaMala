// http://www.spoj.com/problems/INVCNT/

#include "stdafx.h"
#include "CppUnitTest.h"

#include <algorithm>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

#if 0
namespace SPOJ
{
	long long CountInversions(vector<long>& v, size_t start, size_t end)
	{
		if (start > end) throw 0;
		if (end >= v.size()) throw 0;

		if (end - start == 0) return 0;
		if (end - start == 1)
		{
			if (v[start] <= v[end]) return 0;

			auto t = v[start];
			v[start] = v[end];
			v[end] = t;

			return 1;
		}

		auto left_inv = CountInversions(v, start, (start + end) / 2);
		auto right_inv = CountInversions(v, (start + end) / 2 + 1, end);

		// merge left & right and count inversions as you go
		long long across_inv = 0;

		vector<long> left(v.begin() + start, v.begin() + (start + end) / 2 + 1);
		vector<long> right(v.begin() + (start + end) / 2 + 1, v.begin() + end + 1);

		size_t l = 0; size_t r = 0;
		while (l < left.size() && r < right.size())
		{
			if (left[l] <= right[r])
			{
				v[start + l + r] = left[l];
				l++;
			}
			else
			{
				across_inv += left.size() - l;
				v[start + l + r] = right[r];
				r++;
			}
		}
		while (l < left.size())
		{
			v[start + l + r] = left[l];
			l++;
		}
		while (r < right.size())
		{
			v[start + l + r] = right[r];
			r++;
		}
		return across_inv + left_inv + right_inv;
	}
	
	string CountInversions_(vector<long>& v)
	{
		auto res = CountInversions(v, 0, v.size() - 1);

		for (size_t i = 1; i < v.size(); i++)
			if (v[i - 1] > v[i]) throw 0;

		return to_string(res);
	}

	int main()
	{
		long tests = 0;
		cin >> tests;

		vector<long long> inversions;
		inversions.reserve(tests);
		for (long i = 0; i < tests; i++)
		{
			long n = 0;
			cin >> n;
			vector<long> v;
			v.reserve(n);
			for (long j = 0; j < n; j++)
			{
				long a;
				cin >> a;
				v.push_back(a);
			}
			inversions.push_back(CountInversions(v, 0, v.size() - 1));
		}

		cout << endl;
		for (auto i : inversions)
			cout << i << endl;

		char quit;
		std::cin >> quit;
		return 0;
	}

	TEST_CLASS(INVCNT)
	{
	public:

		TEST_METHOD(SingleItem)
		{
			Assert::AreEqual<string>("0", CountInversions_(vector<long>{1}));
		}

		TEST_METHOD(TwoItems)
		{
			Assert::AreEqual<string>("0", CountInversions_(vector<long>{1, 5}));
			Assert::AreEqual<string>("1", CountInversions_(vector<long>{5, 1}));
		}

		TEST_METHOD(NoInversionsAcrossSplit)
		{
			Assert::AreEqual<string>("1", CountInversions_(vector<long>{5, 1, 7, 9}));
			Assert::AreEqual<string>("2", CountInversions_(vector<long>{5, 1, 9, 7}));
		}

		TEST_METHOD(InversionsAcrossSplit)
		{
			Assert::AreEqual<string>("3", CountInversions_(vector<long>{5, 1, 2, 3}));
			Assert::AreEqual<string>("4", CountInversions_(vector<long>{5, 1, 4, 3}));
		}

		TEST_METHOD(MultipleRecursionRequired)
		{
			Assert::AreEqual<string>("12", CountInversions_(vector<long>{5, 2, 9, 12, 1, 7, 3, 10}));
		}

		TEST_METHOD(MaxInversionsPossible)
		{
			vector<long> v;
			v.reserve(200000);
			v.push_back(10000000);
			for (auto i = 1; i < 200000; i++)
				v.push_back(v.back() - 1);

			long long expected = static_cast<long long>(100000) * 199999;
			Assert::AreEqual<string>(to_string(expected), CountInversions_(v));
		}
	};
}
#endif