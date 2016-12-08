// From http://www.spoj.com/problems/POUR1/
// Accepted

#include "stdafx.h"
#include "CppUnitTest.h"
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

#if 0
namespace SPOJ
{
	unsigned GCD(long u, long v) {
		while (v != 0) {
			unsigned r = u % v;
			u = v;
			v = r;
		}
		return u;
	}

	class Hasher
	{
	public:
		Hasher() = default;
		size_t operator()(pair<long, long> item) const
		{
			// 9067, 5153, 40009 are prime
			return (9067 * item.first + 5153 * item.second) % 40009;
		}

	};

	class CPour1
	{
		const long m_a;
		const long m_b;
		unsigned m_gcd;

	public:
		CPour1(long a, long b) : m_a(a), m_b(b)
		{
			m_gcd = GCD(m_a, m_b);
		}

		bool IsSolvable(long c)
		{
			return c <= max(m_a, m_b) && c % m_gcd == 0;
		}

		int Solve(long c)
		{
			if (!IsSolvable(c)) return -1;

			unordered_map<pair<long, long>, unsigned, Hasher> seen;
			bool found = false;
			queue<pair<long, long>> in_progress;
			in_progress.push(make_pair(0, 0));
			seen[make_pair(0, 0)] = 0;

			while (!in_progress.empty())
			{
				auto cur = in_progress.front();

				// each state has four "out edges"
				vector<pair<long, long>> should_try{
					make_pair(cur.first, 0),
					make_pair(0, cur.second),
					make_pair(min(cur.first + cur.second, m_a), max(0l, cur.first + cur.second - m_a)),
					make_pair(max(0l, cur.first + cur.second - m_b), min(cur.first + cur.second, m_b)),
					make_pair(cur.first, m_b),
					make_pair(m_a, cur.second)
				};

				for (const auto& e : should_try)
				{
					if (e.first == c || e.second == c)
						return seen[cur] + 1;

					if (seen.count(e) == 0)
					{
						seen[e] = seen[cur] + 1;
						in_progress.push(e);
					}
				}
				in_progress.pop();
			}

			throw 0;
		}
	};

#if 0
	int main()
	{
		int cases;
		cin >> cases;
		vector <tuple<long, long, long>> inputs;
		for (int i = 0; i < cases; i++)
		{
			long a, b, c;
			cin >> a;
			cin >> b;
			cin >> c;
			inputs.push_back(make_tuple(a, b, c));
		}

		for (const auto& input : inputs)
		{
			CPour1 solver(get<0>(input), get<1>(input));
			cout << solver.Solve(get<2>(input)) << endl;
		}
		char quit;
		cin >> quit;
		return 0;
	}
#endif

	TEST_CLASS(POUR1)
	{
	public:

		TEST_METHOD(GCD_NotTrivial)
		{
			Assert::AreEqual(2u, GCD(4, 10));
		}

		TEST_METHOD(GCD_RelativelyPrime)
		{
			Assert::AreEqual(1u, GCD(28, 15));
		}

		TEST_METHOD(NotSolvable_TooLarge)
		{
			Assert::IsFalse(CPour1(2,3).IsSolvable(5));
		}

		TEST_METHOD(NotSolvable_DueToGCD)
		{
			Assert::IsFalse(CPour1(4, 10).IsSolvable(5));
		}

		TEST_METHOD(Solvable)
		{
			Assert::IsTrue(CPour1(4, 10).IsSolvable(2));
		}

		TEST_METHOD(Solve_NotSolvable)
		{
			Assert::AreEqual(-1, CPour1(4, 10).Solve(5));
		}

		TEST_METHOD(Solve_Trivial)
		{
			Assert::AreEqual(1, CPour1(4, 10).Solve(4));
			Assert::AreEqual(1, CPour1(10, 4).Solve(4));
		}

		TEST_METHOD(Solve_a_minus_b)
		{
			Assert::AreEqual(2, CPour1(4, 10).Solve(6));
		}

		TEST_METHOD(Solve_a_plus_a)
		{
			Assert::AreEqual(4, CPour1(4, 10).Solve(8));
		}
	};
}
#endif