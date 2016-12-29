// http://www.spoj.com/problems/PT07Z/
// My algorithm: start from any vertext and find the furthest vertex from it. 
// Now start from this furthest vertex and find the furthest from it.
// This is the longest path.

#include "stdafx.h"
#include "CppUnitTest.h"

#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <stack>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

#if 0
namespace SPOJ
{
	using EDGES = vector<pair<int, int>>;

	class CTree
	{
		unordered_map<int /*vertex*/, unordered_set<int> /*incident vertices*/> m_vs;
		int m_root = -1;

	public:
		CTree() {}
		CTree(const EDGES& edges)
		{
			m_root = edges.front().first; // doesn't matter which vertex is asigned to be the root
			for (auto& e : edges)
			{
				m_vs[e.first].insert(e.second);
				m_vs[e.second].insert(e.first);
			}
		}
		size_t VertexCount() const { return m_vs.size();  }
		void AddEdge(int v1, int v2)
		{
			m_root = v1;
			m_vs[v1].insert(v2);
			m_vs[v2].insert(v1);
		}

		pair<int /*vertex*/, int /*distance*/> FindFurthestFrom(int start)
		{
			unordered_set<int> seen;
			seen.insert(start);
			stack<int> in_progress;
			in_progress.push(start);

			int cand = start;
			int max_dist = 0;

			int dist = 0;
			while (!in_progress.empty())
			{
				int cur = in_progress.top();
				bool f_pop = true;
				for (auto v : m_vs[cur])
				{
					if (seen.count(v) == 0)
					{
						dist++;
						in_progress.push(v);
						seen.insert(v);
						f_pop = false;
						break;
					}
				}

				if (f_pop)
				{
					if (dist > max_dist)
					{
						max_dist = dist;
						cand = cur;
					}
					dist--;
					in_progress.pop();
				}
			}

			return make_pair(cand, max_dist);
		}

		int LongestPath()
		{
			auto furthest_from_root = FindFurthestFrom(m_root);
			return FindFurthestFrom(furthest_from_root.first).second;
		}
	};

	TEST_CLASS(PT07Z)
	{
	public:
		TEST_METHOD(ReadTree)
		{
			Assert::AreEqual<size_t>(2, CTree(EDGES{ {1,2} }).VertexCount());
			Assert::AreEqual<size_t>(3, CTree(EDGES{ {1,2}, {2,3} }).VertexCount());
			Assert::AreEqual<size_t>(4, CTree(EDGES{ {1,2}, {2,3}, {2,4} }).VertexCount());
			Assert::AreEqual<size_t>(5, CTree(EDGES{ {1,2}, {2,3}, {2,4}, {3,5} }).VertexCount());
		}

		TEST_METHOD(FindFurthestFrom_PathGraph)
		{
			CTree t(EDGES{ {1,2},{2,3},{3,4},{4,5} });

			auto furthest = t.FindFurthestFrom(1);
			Assert::AreEqual(5, furthest.first, L"vertex");
			Assert::AreEqual(4, furthest.second, L"distance");

			auto furthest2 = t.FindFurthestFrom(2);
			Assert::AreEqual(5, furthest2.first, L"vertex");
			Assert::AreEqual(3, furthest2.second, L"distance");
		}

		TEST_METHOD(FindFurthestFrom)
		{
			CTree t(EDGES{{ 4,3 },{ 4,5 },{ 4,6 },{ 3,1 },{ 3,2 },{ 6,7 },{ 7,8} });

			auto furthest1 = t.FindFurthestFrom(1);
			Assert::AreEqual(8, furthest1.first, L"vertex from 1");
			Assert::AreEqual(5, furthest1.second, L"distance from 1");

			auto furthest3 = t.FindFurthestFrom(3);
			Assert::AreEqual(8, furthest3.first, L"vertex from 3");
			Assert::AreEqual(4, furthest3.second, L"distance from 3");

			auto furthest5 = t.FindFurthestFrom(5);
			Assert::AreEqual(8, furthest5.first, L"vertex from 5");
			Assert::AreEqual(4, furthest5.second, L"distance from 5");

			Assert::AreEqual(4, t.FindFurthestFrom(7).second, L"distance from 7");
			Assert::AreEqual(5, t.FindFurthestFrom(8).second, L"distance from 8");
		}

		TEST_METHOD(FindLongestPath)
		{
			CTree t1(EDGES{ { 4,3 },{ 4,5 },{ 4,6 },{ 3,1 },{ 3,2 },{ 6,7 },{ 7,8 } });
			Assert::AreEqual(5, t1.LongestPath());

			CTree t2(EDGES{ { 3,1 },{ 4,3 },{ 4,5 },{ 4,6 },{ 3,2 },{ 6,7 },{ 7,8 } });
			Assert::AreEqual(5, t2.LongestPath());

			CTree t3(EDGES{ { 6,7 },{ 4,3 },{ 3,2 },{ 7,8 },{ 4,5 },{ 4,6 },{ 3,1 } });
			Assert::AreEqual(5, t3.LongestPath());
		}

		TEST_METHOD(FindLongestPath_PathGraph)
		{
			CTree t(EDGES{ { 6,7 },{ 1,2 },{ 5,6 },{ 2,3 },{ 3,4 },{ 4,5 },{ 7,8 } });
			Assert::AreEqual(7, t.LongestPath());
		}

		TEST_METHOD(Perf_MaxPathGraph)
		{
			CTree t;
			for (int i = 1; i < 10000; i++)
				t.AddEdge(i, i + 1);

			Assert::AreEqual(9999, t.LongestPath());
		}

		TEST_METHOD(Perf_MaxStarGraph)
		{
			CTree t;
			for (int i = 1; i < 10000; i++)
				t.AddEdge(1, i + 1);

			Assert::AreEqual(2, t.LongestPath());
		}

		TEST_METHOD(Perf_ChainedStars)
		{
			CTree t;
			for (int j = 0; j < 10; j++)
			{
				for (int i = j*1000 + 1; i <= (j + 1) * 1000; i++)
					t.AddEdge(j * 1000 + 1, i + 1);
			}

			Assert::AreEqual(11, t.LongestPath());
		}
	};
}
#endif