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

		int CowsAsCloseAs(int dist)
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

		int SpacingFor(int cows)
		{
			int low = MinInterval();
			int high = MaxInterval();

			while (low < high)
			{
				int at_low = CowsAsCloseAs(low);
				int at_high = CowsAsCloseAs(high);

				if (at_low < cows) throw 0;
				if (at_high > cows) throw 0;

				int mid = low + (high + 1 - low) / 2;
				int at_mid = CowsAsCloseAs(mid);

				if (at_mid >= cows) low = mid;
				else
				{
					if (high == mid)
						return at_high < cows ? low : high;

					high = mid;
				}
			}
			return high;
		}
	};

	TEST_CLASS(AGGRCOW)
	{
	public:
		TEST_METHOD(Spacing_Duplicates)
		{
			vector<int> v{ 1, 2, 9, 8, 4, 4, 8, 9, 2, 1 };
			CAggrCow ac(v);
			Assert::AreEqual(3, ac.SpacingFor(3));
		}

		TEST_METHOD(Spacing_MaxValues)
		{
			vector<int> v{ 0,50000000,100000000 };
			CAggrCow ac(v);
			Assert::AreEqual(100000000, ac.SpacingFor(2));
		}

		TEST_METHOD(Spacing_Uniform)
		{
			vector<int> v{ 1,2,3,4,5,6,7,8,9,10 };
			CAggrCow ac(v);
			Assert::AreEqual(4, ac.SpacingFor(3));
			Assert::AreEqual(3, ac.SpacingFor(4));
			Assert::AreEqual(2, ac.SpacingFor(5));
		}

		TEST_METHOD(Spacing_SpojSample)
		{
			vector<int> v{ 1,2,8,4,9 };
			CAggrCow ac(v);
			Assert::AreEqual(3, ac.SpacingFor(3));
		}

		TEST_METHOD(Spacing_TwoCows)
		{
			vector<int> v{ 4, 17, 10, 9, 6, 1 };
			CAggrCow ac(v);
			Assert::AreEqual(16, ac.SpacingFor(2));
		}

		TEST_METHOD(Spacing_MaxCows)
		{
			vector<int> v{ 4, 17, 10, 9, 6, 1 };
			CAggrCow ac(v);
			Assert::AreEqual(1, ac.SpacingFor(v.size()));
		}

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
			Assert::AreEqual(2, ac.CowsAsCloseAs(16));
			Assert::AreEqual(2, ac.CowsAsCloseAs(15));
			Assert::AreEqual(2, ac.CowsAsCloseAs(14));
			Assert::AreEqual(2, ac.CowsAsCloseAs(13));
			Assert::AreEqual(2, ac.CowsAsCloseAs(12));
			Assert::AreEqual(2, ac.CowsAsCloseAs(11));
			Assert::AreEqual(2, ac.CowsAsCloseAs(10));
			Assert::AreEqual(2, ac.CowsAsCloseAs(9));
			Assert::AreEqual(3, ac.CowsAsCloseAs(8));
			Assert::AreEqual(3, ac.CowsAsCloseAs(7));
			Assert::AreEqual(3, ac.CowsAsCloseAs(6));
			Assert::AreEqual(3, ac.CowsAsCloseAs(5));
			Assert::AreEqual(4, ac.CowsAsCloseAs(4));
			Assert::AreEqual(4, ac.CowsAsCloseAs(3));
			Assert::AreEqual(5, ac.CowsAsCloseAs(2));
			Assert::AreEqual(6, ac.CowsAsCloseAs(1));
		}
	};
}