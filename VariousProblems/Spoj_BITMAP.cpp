// http://www.spoj.com/problems/BITMAP/

#include "stdafx.h"
#include "CppUnitTest.h"

#include <algorithm>
#include <vector>
#include <numeric>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

#if 1
namespace SPOJ
{
	vector<int> GetDistances(const vector<int>& pixels)
	{
		return pixels;
	}

	TEST_CLASS(BITMAP)
	{
		string GetDistances_(const vector<int>& pixels)
		{
			auto dists = GetDistances(pixels);
			string s{ "" };
			for (auto d : dists) s.append(to_string(d));
			return s;
		}
	public:
		TEST_METHOD(SinglePixel)
		{
			Assert::AreEqual<string>("0", GetDistances_(vector<int>{1}));
		}
	};
}
#endif