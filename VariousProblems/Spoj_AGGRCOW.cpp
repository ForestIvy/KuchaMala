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

		int MinInterval() const
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

		int MaxInterval() const
		{
			return m_v.back() - m_v.front();
		}

		pair<int /*cows*/, int /*spacing*/> PlaceAsCloseAs(int dist) const
		{
			int cows = 1;
			int cur_dist = 0;
			int spacing = MaxInterval();
			for (auto i = 1; i < m_v.size(); i++)
			{
				cur_dist += m_v[i] - m_v[i - 1];
				if (cur_dist >= dist)
				{
					spacing = min(spacing, cur_dist);
					cows++;

					cur_dist = 0;
				}

			}
			return make_pair(cows, spacing);
		}

		int SpacingFor(int cows) const 
		{
			int low = MinInterval();
			int high = MaxInterval();

			while (low < high)
			{

			}

			return 0;
		}

	};

	TEST_CLASS(AGGRCOW)
	{
	public:
		string Dump(pair<int, int> p)
		{
			return to_string(p.first) + "," + to_string(p.second);
		}
		TEST_METHOD(MinAndMaxBoundaries)
		{
			vector<int> v{4, 17, 10, 9, 6, 1};
			CAggrCow ac(v);
			Assert::AreEqual(1, ac.MinInterval());
			Assert::AreEqual(16, ac.MaxInterval());
		}

		TEST_METHOD(NumberOfCowsAtGivenSpacing)
		{
			vector<int> v{ 4, 17, 10, 9, 6, 1 };
			CAggrCow ac(v);
			Assert::AreEqual("2,16", Dump(ac.PlaceAsCloseAs(16)).c_str(), L"16");
			Assert::AreEqual("2,16", Dump(ac.PlaceAsCloseAs(15)).c_str(), L"15");
			Assert::AreEqual("2,16", Dump(ac.PlaceAsCloseAs(14)).c_str(), L"14");
			Assert::AreEqual("2,16", Dump(ac.PlaceAsCloseAs(13)).c_str(), L"13");
			Assert::AreEqual("2,16", Dump(ac.PlaceAsCloseAs(12)).c_str(), L"12");
			Assert::AreEqual("2,16", Dump(ac.PlaceAsCloseAs(11)).c_str(), L"11");
			Assert::AreEqual("2,16", Dump(ac.PlaceAsCloseAs(10)).c_str(), L"10");
			Assert::AreEqual("2,16", Dump(ac.PlaceAsCloseAs(9)).c_str(), L"9");
			Assert::AreEqual("2,16", Dump(ac.PlaceAsCloseAs(8)).c_str(), L"8");
			Assert::AreEqual("3,7", Dump(ac.PlaceAsCloseAs(7)).c_str(), L"7");
			Assert::AreEqual("3,7", Dump(ac.PlaceAsCloseAs(6)).c_str(), L"6");
			Assert::AreEqual("3,7", Dump(ac.PlaceAsCloseAs(5)).c_str(), L"5");
			Assert::AreEqual("4,4", Dump(ac.PlaceAsCloseAs(4)).c_str(), L"4");
			Assert::AreEqual("4,4", Dump(ac.PlaceAsCloseAs(3)).c_str(), L"3");
			Assert::AreEqual("5,2", Dump(ac.PlaceAsCloseAs(2)).c_str(), L"2");
			Assert::AreEqual("6,1", Dump(ac.PlaceAsCloseAs(1)).c_str(), L"1");
		}
	};
}