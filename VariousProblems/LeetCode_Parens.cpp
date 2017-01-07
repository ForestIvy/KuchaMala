// https://leetcode.com/problems/longest-valid-parentheses/

#include "stdafx.h"
#include "CppUnitTest.h"

#include <algorithm>
#include <vector>
#include <stack>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

#if 0
namespace LeetCode
{
	int LWFP(string s) // longest well formed parentheses
	{
		// first linear pass through the string: collapse pared parentheses 
		// by replacing them with '_' in the string
		stack<int> opens;
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] == '(') opens.push(i);
			else if (!opens.empty())
			{
				s[i] = '_';
				s[opens.top()] = '_';
				opens.pop();
			}
		}

		// second linear pass through the string: find the longest
		// range consisting of '_'
		int lwf = 0;
		int cur = 0;
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] == '_') cur++;
			else if (cur > lwf)
			{
				lwf = cur;
				cur = 0;
			}
		}
		return max(lwf, cur);
	}

	TEST_CLASS(LongestWellFormedParens)
	{
	public:
		TEST_METHOD(Single)
		{
			Assert::AreEqual(0, LWFP("("), L"(");
			Assert::AreEqual(0, LWFP(")"), L")");
		}

		TEST_METHOD(Pair)
		{
			Assert::AreEqual(0, LWFP(")("), L")(");
			Assert::AreEqual(0, LWFP("))"), L"))");
			Assert::AreEqual(0, LWFP("(("), L"()");
			Assert::AreEqual(2, LWFP("()"), L"()");
		}

		TEST_METHOD(Three)
		{
			Assert::AreEqual(0, LWFP(")(("), L")((");
			Assert::AreEqual(2, LWFP("())"), L"())");
			Assert::AreEqual(2, LWFP("(()"), L"(()");
		}

		TEST_METHOD(TwoGroups)
		{
			Assert::AreEqual(4, LWFP("()(()()"), L"()(()()");
			Assert::AreEqual(4, LWFP("(()))()"), L"(()))()");
			Assert::AreEqual(6, LWFP("(())()"), L"(())()");
		}

		TEST_METHOD(FullyWellFormed)
		{
			string s("(()(())()(((()()))))");
			Assert::AreEqual<int>(s.length(), LWFP(s));
		}

		TEST_METHOD(WellFormedPrefix)
		{
			string s("(()(())()(((()()))))");
			string tail(")(())");
			Assert::AreEqual<int>(s.length(), LWFP(s + tail));
		}

		TEST_METHOD(WellFormedSuffix)
		{
			string s("(()(())()(((()()))))");
			string head("))())");
			Assert::AreEqual<int>(s.length(), LWFP(head + s));
		}

		TEST_METHOD(WellFormedMiddle)
		{
			string s("(()(())()(((()()))))");
			string head("()())");
			string tail(")(())");
			Assert::AreEqual<int>(s.length(), LWFP(head + s + tail));
		}
	};
}
#endif