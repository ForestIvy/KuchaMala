// http://www.spoj.com/problems/PALIN/

#include "stdafx.h"
#include "CppUnitTest.h"

#include <limits>
#include <vector>
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

#if 1
namespace SPOJ
{
	string NextPalindrome(string number)
	{
		if (number.empty()) return "1";
		
		auto n = number.length();
		string flipped = number.substr(0, n / 2);
		reverse(flipped.begin(), flipped.end());
		if (flipped > number.substr((n + 1) / 2, n / 2)) 
			return number.replace((n + 1) / 2, n / 2, flipped.c_str());

		long k = n / 2;
		while (k >= 0)
		{
			auto digit = stoi(number.substr(k, 1));
			if (digit < 9)
			{
				string head = number.substr(0, k) + to_string(digit + 1);
				string head_flipped = head;
				reverse(head_flipped.begin(), head_flipped.end());

				number.replace(k, n - k, n - k, '0');
				number.replace(k, 1, to_string(digit + 1));
				number.replace(n - head.length(), head.length(), head_flipped);
				return number;
			}
			else
				k--;
		}

		// all nines
		string ret(number.length() + 1, '0');
		return ret.replace(0, 1, "1").replace(number.length(), 1, "1");
	}

	TEST_CLASS(PALIN)
	{
	public:
		TEST_METHOD(EmptyString)
		{
			Assert::AreEqual<string>("1", NextPalindrome(""));
		}
		TEST_METHOD(SingleDigit)
		{
			Assert::AreEqual<string>("3", NextPalindrome("2"));
		}

		TEST_METHOD(CanFlipFirstHalf)
		{
			Assert::AreEqual<string>("55", NextPalindrome("51"));
			Assert::AreEqual<string>("271172", NextPalindrome("271153"));
			Assert::AreEqual<string>("797", NextPalindrome("791"));
			Assert::AreEqual<string>("987789", NextPalindrome("987699"));
		}

		TEST_METHOD(OddLength_MidPointNotNine)
		{
			Assert::AreEqual<string>("525", NextPalindrome("517"));
			Assert::AreEqual<string>("9871789", NextPalindrome("9870999"));
		}

		TEST_METHOD(OddLength_NinesInTheMiddle)
		{
			Assert::AreEqual<string>("606", NextPalindrome("597"));
			Assert::AreEqual<string>("9900099", NextPalindrome("9899999"));
		}

		TEST_METHOD(AllNines)
		{
			Assert::AreEqual<string>("11", NextPalindrome("9"));
			Assert::AreEqual<string>("1001", NextPalindrome("999"));
			Assert::AreEqual<string>("10001", NextPalindrome("9999"));
			Assert::AreEqual<string>("10000001", NextPalindrome("9999999"));
		}

		TEST_METHOD(EvenLength_NinesInTheMiddle)
		{
			Assert::AreEqual<string>("6006", NextPalindrome("5997"));
			Assert::AreEqual<string>("99000099", NextPalindrome("98999997"));
		}

		TEST_METHOD(MaxLength)
		{
			Assert::AreEqual<string>(string(1000000, '2'), NextPalindrome(string(999999, '2') + "1"));
			Assert::AreEqual<string>(string("1") + string(999999, '0') + "1", NextPalindrome(string(1000000, '9')));
			Assert::AreEqual<string>(string(1000000, '9'), NextPalindrome(string(999999, '9') + "7"));
			Assert::AreEqual<string>(string("8") + string(999998, '0') + "8", NextPalindrome(string("7") + string(999999, '9')));
		}
	};
}
#endif