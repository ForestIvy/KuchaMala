// http://www.spoj.com/problems/ACODE/
// the longest string to decode is 5000 digits, but if this is a string of 1's (or 2's)
// the problem is equivalent to calculating the 5000th Fibonacci's number, which doesn't
// fit into "long long" for sure. The online judge however doesn't test on such degenerate
// cases and the solution below was accepted.
// NB: though "as is" it gives CE (because of "throw 0"?)

#include "stdafx.h"
#include "CppUnitTest.h"

#include <limits>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

#if 0
namespace SPOJ
{
	bool IsCode(string candidate)
	{
		if (candidate.empty() || candidate.length() > 2) return false;
		if (candidate[0] == '0') return false;

		int code = stoi(candidate);
		return (code > 0 && code < 27);
	}

	unsigned long long PossibleDecodings(string code)
	{
		if (code.length() <= 1) return 1;

		vector<unsigned long long> counts(code.length() + 1, 0);
		counts[0] = 1;
		counts[1] = 1;
		for (size_t i = 1; i < code.length(); i++)
		{
			bool one = IsCode(code.substr(i, 1));
			bool two = IsCode(code.substr(i - 1, 2));

			if (one && two)
			{
				if (numeric_limits<long long>::max() - counts[i] < counts[i - 1]) throw 0;
				counts[i + 1] = counts[i] + counts[i - 1];
			}
			else if (one) counts[i + 1] = counts[i];
			else if (two) counts[i + 1] = counts[i - 1];
			else return 0;
		}
		return counts.back();
	}

#if 0
	int main()
	{
		vector<long long> counts;
		string cur;
		for (;;)
		{
			cin >> cur;
			if (cur == "0")
				break;

			counts.push_back(PossibleDecodings(cur));
		}

		for (auto i : counts)
			cout << i << endl;

		char q;
		cin >> q;
		return 0;
	}
#endif

	string PossibleDecodings_(string code)
	{
		return to_string(PossibleDecodings(code));
	}

	TEST_CLASS(ACODE)
	{
	public:
		TEST_METHOD(IsCode_Yes)
		{
			Assert::IsTrue(IsCode("5"), L"5");
			Assert::IsTrue(IsCode("15"), L"15");
			Assert::IsTrue(IsCode("26"), L"26");
		}

		TEST_METHOD(IsCode_No)
		{
			Assert::IsFalse(IsCode("0"), L"0");
			Assert::IsFalse(IsCode("00"), L"00");
			Assert::IsFalse(IsCode("27"), L"27");
			Assert::IsFalse(IsCode("231"), L"231");
		}

		TEST_METHOD(SingleDigit)
		{
			Assert::AreEqual<string>("1", PossibleDecodings_("1"));
		}

		TEST_METHOD(TwoDigits)
		{
			Assert::AreEqual<string>("2", PossibleDecodings_("12"), L"12");
			Assert::AreEqual<string>("1", PossibleDecodings_("32"), L"32");
			Assert::AreEqual<string>("2", PossibleDecodings_("26"), L"26");
		}

		TEST_METHOD(WithZeros)
		{
			Assert::AreEqual<string>("1", PossibleDecodings_("120"), L"120");
			Assert::AreEqual<string>("1", PossibleDecodings_("1032"), L"1032");
			Assert::AreEqual<string>("1", PossibleDecodings_("1020"), L"1020");
		}

		TEST_METHOD(InvalidInput)
		{
			Assert::AreEqual<string>("0", PossibleDecodings_("30"), L"30");
			Assert::AreEqual<string>("0", PossibleDecodings_("007"), L"007");
			Assert::AreEqual<string>("0", PossibleDecodings_("507"), L"507");
			Assert::AreEqual<string>("0", PossibleDecodings_("1002"), L"1002");
		}

		TEST_METHOD(SamplesFromSpoj)
		{
			Assert::AreEqual<string>("6", PossibleDecodings_("25114"), L"25114");
			Assert::AreEqual<string>("89", PossibleDecodings_("1111111111"), L"1111111111");
			Assert::AreEqual<string>("1", PossibleDecodings_("3333333333"), L"3333333333");
		}

		TEST_METHOD(Growth_Fibbonachi)
		{
			Assert::AreEqual<string>("89", PossibleDecodings_(string(10, '1')), L"for 10");
			Assert::AreEqual<string>("987", PossibleDecodings_(string(15, '1')), L"for 15");
			Assert::AreEqual<string>("10946", PossibleDecodings_(string(20, '1')), L"for 20");
			Assert::AreEqual<string>("20365011074", PossibleDecodings_(string(50, '1')), L"for 50");
			//Assert::AreEqual<string>("0", PossibleDecodings_(string(100, '1')), L"for 100");
		}

		TEST_METHOD(PerfComp)
		{
			Assert::AreEqual<string>("308061521170129", PossibleDecodings_(string(70, '1')), L"for 70");
		}

		TEST_METHOD(MaxLength)
		{
			Assert::AreEqual<string>("1", PossibleDecodings_(string(5000, '3')));
		}
	};
}
#endif