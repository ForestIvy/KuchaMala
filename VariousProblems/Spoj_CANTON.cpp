// http://www.spoj.com/problems/CANTON

#include "stdafx.h"
#include "CppUnitTest.h"

#include <algorithm>
#include <vector>
#include <numeric>

#include "ToString.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

#if 0
namespace SPOJ
{
	/*
	find max k : k(k + 1) / 2 < n
		k(k + 1) < 2n
		check k = sqrt(2n) - 1, k = sqrt(2n), +1
		then n is in the(k + 1)th diagonal
		let the number we are looking for be a / b
		then a + b = k + 1 + 1
		if k + 1 even a grows with n
			need to step n - k(k + 1) / 2 - 1 times to
			(1 + n - k(k + 1) / 2 - 1) / (k + 2 - 1 - n + k(k + 1) / 2 + 1)
			(n - k(k + 1) / 2) / (k + 2 - n + k(k + 1) / 2)
			if k + 1 odd b grows with n
			(k + 2 - n + k(k + 1) / 2) / (n - k(k + 1) / 2)

		n = 7
		sqrt(14) = 3.741657386773941
		k = 3: 3 * 4 / 2 = 6 < 7 (and 4 * 5 / 2 = 10 > 7)
		k + 1 is even so
		(7 - 6) / (5 - 7 + 6) = > 1 / 4

		n = 14
		sqrt(2 * 14) = 5.291502622129181
		k = 5: 5 * 6 / 2 = 15
		k = 4 : 4 * 5 / 2 = 10
		k + 1 is odd :
		(4 + 2 - 14 + 10) / (14 - 10) = > 2 / 4
	*/

	pair<long, long> CantorsNumber(long n)
	{
		long k = sqrt(2 * n);
		long tri = k*(k + 1) / 2;
		if (tri >= n) {	k--; tri = k*(k + 1) / 2; }

		if ((k + 1)*(k + 2) / 2 < n) throw 0;
		
		if ((k + 1) % 2 == 0) return { (n - tri), (k + 2 - n + tri) };
		return{ (k + 2 - n + tri), (n - tri) };
	}

	string CantorsNumber_(long n)
	{
		auto p = CantorsNumber(n);
		return string("TERM ") + to_string(n) + " IS " + to_string(p.first) + "/" + to_string(p.second);
	}


	TEST_CLASS(CANTON)
	{
	public:
		TEST_METHOD(SampleFromSpoj)
		{
			Assert::AreEqual<string>("TERM 3 IS 2/1", CantorsNumber_(3));
			Assert::AreEqual<string>("TERM 14 IS 2/4", CantorsNumber_(14));
			Assert::AreEqual<string>("TERM 7 IS 1/4", CantorsNumber_(7));
		}


		TEST_METHOD(MaxNumber)
		{
			Assert::AreEqual<string>("TERM 10000000 IS 2844/1629", CantorsNumber_(10000000));
		}

		TEST_METHOD(Stress)
		{
			for (long n = 1; n < 1000000; n++)
				CantorsNumber(n);
		}

	};
}
#endif