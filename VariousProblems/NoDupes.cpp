#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include <algorithm>
#include <map>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

#if 0
namespace VariousProblems
{
	int GetLengthWithNoDupes(wstring s)
	{
		int cand = 0;
		std::map<wchar_t, size_t> seen;

		size_t cp = 0;
		for (auto it = s.begin(); it != s.end(); ++it)
		{
			auto cur = it - s.begin();
			auto prev = seen.find(*it);

			if (prev != seen.end() && prev->second >= cp)
			{
				if (cur - cp > cand)
					cand = cur - cp;

				cp = prev->second + 1;
			}

			seen[*it] = cur;
		}
		return max(cand, static_cast<int>(s.length() - cp));
	}

	TEST_CLASS(SubstrWithNoDupes)
	{
	public:

		TEST_METHOD(NoDupes)
		{
			Assert::AreEqual(1, GetLengthWithNoDupes(L"a"));
			Assert::AreEqual(11, GetLengthWithNoDupes(L"abcdefghijk"));
		}

		TEST_METHOD(Tail)
		{
			Assert::AreEqual(7, GetLengthWithNoDupes(L"abcadefg"));
			Assert::AreEqual(4, GetLengthWithNoDupes(L"aaaadddefg"));
		}

		TEST_METHOD(NotTail)
		{
			Assert::AreEqual(8, GetLengthWithNoDupes(L"abcsadefgg"));
			Assert::AreEqual(6, GetLengthWithNoDupes(L"abcdefaaaa"));
			Assert::AreEqual(7, GetLengthWithNoDupes(L"abcdefgaaaab"));
			Assert::AreEqual(9, GetLengthWithNoDupes(L"aaabcdefghiaaaabcde"));
		}

		TEST_METHOD(Andrey)
		{
			Assert::AreEqual(2, GetLengthWithNoDupes(L"ab"));
			Assert::AreEqual(1, GetLengthWithNoDupes(L"aa"));
		}

	};
}
#endif