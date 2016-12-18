// http://www.spoj.com/problems/AGGRCOW/
// https://www.topcoder.com/community/data-science/data-science-tutorials/binary-search/ 


#include "stdafx.h"

#include <vector>
#include <string>
#include <functional>
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace SPOJ
{
	class CAggrCow
	{
		vector<int> m_v;
	public:
		CAggrCow(vector<int> v)
			: m_v(move(v))
		{
			if (m_v.size() < 2) throw;
			sort(m_v.begin(), m_v.end());
		}

		int MinInterval()
		{
			int minInterval = MaxInterval();
			for (auto i = 1; i < m_v.size(); i++)
			{
				auto cand = m_v[i] - m_v[i - 1];
				if (cand < minInterval)
					minInterval = cand;
			}
			return minInterval;
		}

		int MaxInterval()
		{
			return m_v.back() - m_v.front();
		}

		int PlaceAsCloseAs(int dist)
		{
			int cows = 1;
			int cur_dist = 0;
			for (auto i = 1; i < m_v.size(); i++)
			{
				cur_dist += m_v[i] - m_v[i - 1];
				if (cur_dist >= dist)
				{
					cows++;
					cur_dist = 0;
				}
			}
			return cows;
		}
	};

	TEST_CLASS(AGGRCOW)
	{
	public:

		TEST_METHOD(FindMinAndMaxIntervals)
		{
			vector<int> v{4, 17, 10, 9, 6, 1};
			CAggrCow ac(v);
			Assert::AreEqual(1, ac.MinInterval());
			Assert::AreEqual(16, ac.MaxInterval());
		}

		TEST_METHOD(NumberOfCowsAtGivenDistance)
		{
			vector<int> v{ 4, 17, 10, 9, 6, 1 };
			CAggrCow ac(v);
			Assert::AreEqual(2, ac.PlaceAsCloseAs(16));
			Assert::AreEqual(2, ac.PlaceAsCloseAs(15));
			Assert::AreEqual(2, ac.PlaceAsCloseAs(14));
			Assert::AreEqual(2, ac.PlaceAsCloseAs(13));
			Assert::AreEqual(2, ac.PlaceAsCloseAs(12));
			Assert::AreEqual(2, ac.PlaceAsCloseAs(11));
			Assert::AreEqual(2, ac.PlaceAsCloseAs(10));
			Assert::AreEqual(2, ac.PlaceAsCloseAs(9));
			Assert::AreEqual(3, ac.PlaceAsCloseAs(8));
			Assert::AreEqual(3, ac.PlaceAsCloseAs(7));
			Assert::AreEqual(3, ac.PlaceAsCloseAs(6));
			Assert::AreEqual(3, ac.PlaceAsCloseAs(5));
			Assert::AreEqual(4, ac.PlaceAsCloseAs(4));
			Assert::AreEqual(4, ac.PlaceAsCloseAs(3));
			Assert::AreEqual(5, ac.PlaceAsCloseAs(2));
			Assert::AreEqual(6, ac.PlaceAsCloseAs(1));
		}
	};
}