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
		if (s.length() < 2) return 0;

		vector<int> costs_prev(s.length(), 0); 
		vector<int> costs(s.length() - 1, 0);
		for (int i = 0; i < costs.size(); i++) costs[i] = (s[i] == s[i + 1]) ? 0 : 1;

		vector<int> cur;
		while (costs.size() > 1)
		{
			cur.resize(costs.size() - 1);
			for (int i = 0; i < cur.size(); i++)
			{
				if (s[i] == s[i + s.length() - cur.size()]) cur[i] = costs_prev[i+1];
				else cur[i] = 1 + min(costs[i], costs[i + 1]);
			}		
			costs_prev.swap(costs);
			costs.swap(cur);
		}
		return costs.front();
	}

	TEST_CLASS(AIBOHP)
	{
	public:
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

		TEST_METHOD(Middle)
		{
			Assert::AreEqual(1, MakePalinCost("abcdacba"), L"abcdabca -> abcdadcba");
		}

		TEST_METHOD(MaxLength)
		{
			string s(6100, 'a');
			Assert::AreEqual(0, MakePalinCost(s));
		}
	};
}
#endif