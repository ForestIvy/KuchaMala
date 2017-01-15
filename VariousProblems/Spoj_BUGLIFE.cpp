// http://www.spoj.com/problems/BUGLIFE/

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
	TEST_CLASS(BUGLIFE)
	{
	public:
		TEST_METHOD(LoneBug)
		{
			Assert::Fail();
		}
	};
}
#endif