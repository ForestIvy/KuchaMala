// http://www.spoj.com/problems/AIBOHP (similar to TRT)

#include "stdafx.h"
#include "CppUnitTest.h"

#include <algorithm>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

#if 1
namespace SPOJ
{
	int MakePalinCost(const string& s)
	{
		return 0;
	}

	TEST_CLASS(AIBOHP)
	{
	public:
		TEST_METHOD(SingleLetter)
		{
			Assert::AreEqual(0, MakePalinCost("a"));
		}
	};
}
#endif