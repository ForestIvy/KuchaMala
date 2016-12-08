// From http://codeforces.com/contest/127/problem/C

// without the discreet requirements the answer would be:
// hot: std::min(hm, cm*(t - ct)/(ht - t));
// cold: h*(ht - t) / (t - ct);
// but because of rounding need to go through all possible values for
// one tap, calculate corresponding cold, compare to target, and choose max
// amond those that are closest to target

#include "stdafx.h"
#include "CppUnitTest.h"
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#if 0
namespace VariousProblems
{
	std::pair<int, int> GetTapSettings(int ct, int ht, int cm, int hm, int t)
	{
		if (t == ct && t == ht)
			return std::make_pair(cm, hm);

		if (t == ct)
			return std::make_pair(cm, 0);

		if (t == ht)
			return std::make_pair(0, hm);

		int c = 0;
		int h = hm;
		double best = ht - t;
		
		for (int cy = 1; cy <= cm; ++cy)
		{
			double h_ideal = std::min(cy*(t - ct) / (ht - t), hm);

			for (int hy = h_ideal; hy <= h_ideal + 1; ++hy)
			{
				double target = static_cast<double>(cy*ct + hy*ht) / (cy + hy);
				if (target >= t && target - t <= best)
				{
					if (target - t == best && cy + hy > c + h || target - t < best)
					{
						c = cy;
						h = hy;
						best = target - t;
					}
				}
			}
		}
		return std::make_pair(c, h);
	}

	TEST_CLASS(HotTub)
	{
	public:

		TEST_METHOD(SameColdAndHotTemperatures)
		{
			auto r = GetTapSettings(10, 10, 17, 42, 10);
			Assert::AreEqual(17, r.first);
			Assert::AreEqual(42, r.second);
		}

		TEST_METHOD(TargetSameAsCold)
		{
			auto r = GetTapSettings(10, 14, 17, 42, 10);
			Assert::AreEqual(17, r.first);
			Assert::AreEqual(0, r.second);
		}

		TEST_METHOD(TargetSameAsHot)
		{
			auto r = GetTapSettings(10, 14, 17, 42, 14);
			Assert::AreEqual(0, r.first);
			Assert::AreEqual(42, r.second);
		}

		TEST_METHOD(EqualFlow)
		{
			auto r = GetTapSettings(10, 14, 17, 17, 12);
			double t = (10.0 * r.first + 14 * r.second) / (r.first + r.second);
			std::wstring message = std::to_wstring(r.first) + L" " + std::to_wstring(r.second) + L" : " + std::to_wstring(t);

			Assert::AreEqual(17, r.first, message.c_str());
			Assert::AreEqual(17, r.second);

			Assert::AreEqual(12, (10 * r.first + 14 * r.second) / (r.first + r.second));
		}

		// tests from the site
		TEST_METHOD(FirstTestFromJudge)
		{
			auto r = GetTapSettings(10, 70, 100, 100, 25);
			Assert::AreEqual(99, r.first);
			Assert::AreEqual(33, r.second);

			Assert::AreEqual(25, (10 * r.first + 70 * r.second) / (r.first + r.second));
		}

		TEST_METHOD(SecondTestFromJudge)
		{
			auto r = GetTapSettings(143, 456, 110, 117, 273);

			double mine = (143.0 * r.first + 456 * r.second) / (r.first + r.second);
			std::wstring message = std::to_wstring(r.first) + L" " + std::to_wstring(r.second) + L" : " + std::to_wstring(mine);

			Assert::AreEqual(76, r.first, message.c_str());
			Assert::AreEqual(54, r.second);
		}

	};
}
#endif