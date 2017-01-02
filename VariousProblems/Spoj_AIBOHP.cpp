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
	bool IsPalindrome(const string& s)
	{
		auto l = s.begin();
		auto r = s.end() - 1;
		while (l < r)
		{
			if (*l != *r) return false;
			++l;
			--r;
		}
		return true;
	}

	int MakePalinCost(const string& s)
	{
		if (s.length() < 2) return 0;

		vector<int> costs(s.length(), 0);
		while (costs.size() > 1)
		{
			for (int i = 0; i < costs.size() - 1; i++)
			{
				if (IsPalindrome(s.substr(i, s.length() - costs.size() + 2))) costs[i] = 0;
				else costs[i] = 1 + min(costs[i], costs[i + 1]);
			}
			costs.resize(costs.size() - 1);
		}
		return costs.front();
	}

	TEST_CLASS(AIBOHP)
	{
	public:
		TEST_METHOD(IsPalindrome_Test)
		{
			Assert::IsTrue(IsPalindrome("a"), L"a");
			Assert::IsTrue(IsPalindrome("aba"), L"aba");
			Assert::IsTrue(IsPalindrome("abccba"), L"abccba");
			Assert::IsFalse(IsPalindrome("ab"), L"ab");
			Assert::IsFalse(IsPalindrome("aab"), L"aab");
		}

		TEST_METHOD(SingleLetter)
		{
			Assert::AreEqual(0, MakePalinCost("a"));
		}

		TEST_METHOD(TwoLetters)
		{
			Assert::AreEqual(0, MakePalinCost("aa"), L"aa");
			Assert::AreEqual(1, MakePalinCost("ab"), L"ab");
		}

		TEST_METHOD(ThreeLetters)
		{
			Assert::AreEqual(0, MakePalinCost("aaa"), L"aaa");
			Assert::AreEqual(0, MakePalinCost("aba"), L"aba");
			Assert::AreEqual(1, MakePalinCost("abb"), L"abb -> abba");
			Assert::AreEqual(2, MakePalinCost("abc"), L"abc -> abcba");
		}

		TEST_METHOD(MaxLength)
		{
			string s(6100, 'a');
			Assert::AreEqual(0, MakePalinCost(s));
		}
	};
}
#endif