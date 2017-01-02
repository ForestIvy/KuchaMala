// http://www.spoj.com/problems/HOTELS

#include "stdafx.h"
#include "CppUnitTest.h"

#include <algorithm>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

#if 1
namespace SPOJ
{
	TEST_CLASS(HOTELS)
	{
		long GetBestOffer(long budget, const vector<long>& hotels)
		{
			return 0;
		}
	public:
		TEST_METHOD(SingleCannotBuy)
		{
			Assert::AreEqual<long>(0, GetBestOffer(3, vector<long>{7}));
		}
	};
}
#endif