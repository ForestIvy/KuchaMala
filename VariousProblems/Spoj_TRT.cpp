// http://www.spoj.com/problems/TRT

#include "stdafx.h"
#include "CppUnitTest.h"

#include <algorithm>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

#if 1
namespace SPOJ
{
	long SellTreats(const vector<int>& treats)
	{
		if (treats.empty()) return 0;

		return treats[0];
	}
	TEST_CLASS(FARIDA)
	{
	public:
		TEST_METHOD(SingleTreat)
		{
			Assert::AreEqual<long>(7, SellTreats(vector<int>{7}));
		}
	};
}
#endif