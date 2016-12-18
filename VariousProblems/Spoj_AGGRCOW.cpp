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

		int FindMinInterval()
		{
			int minInterval = FindMaxInterval();
			for (auto i = 1; i < m_v.size(); i++)
			{
				auto cand = m_v[i] - m_v[i - 1];
				if (cand < minInterval)
					minInterval = cand;
			}
			return minInterval;
		}

		int FindMaxInterval()
		{
			return m_v.back() - m_v.front();
		}
	};

	TEST_CLASS(AGGRCOW)
	{
	public:

		TEST_METHOD(FindMinAndMaxBoundaries)
		{
			vector<int> v{4, 17, 10, 9, 6, 1};
			CAggrCow ac(v);
			Assert::AreEqual(1, ac.FindMinInterval());
			Assert::AreEqual(16, ac.FindMaxInterval());
		}
	};
}