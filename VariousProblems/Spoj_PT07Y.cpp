// http://www.spoj.com/problems/PT07Y/

#include "stdafx.h"
#include "CppUnitTest.h"

#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

#if 1
namespace SPOJ
{
	using EDGES = vector<pair<int, int>>;

	class CGraph
	{
		unordered_map<int /*vertex*/, unordered_set<int> /*incident vertices*/> m_vs;
		int m_root = -1;
		int m_edges_count = 0;

	public:
		CGraph() {}
		CGraph(const EDGES& edges)
		{
			m_root = edges.front().first; // doesn't matter which vertex is asigned to be the root
			m_edges_count = edges.size();
			for (auto& e : edges)
			{
				m_vs[e.first].insert(e.second);
				m_vs[e.second].insert(e.first);
			}
		}
		size_t VertexCount() const { return m_vs.size(); }
		void AddEdge(int v1, int v2)
		{
			m_root = v1;
			m_edges_count++;
			m_vs[v1].insert(v2);
			m_vs[v2].insert(v1);
		}

		bool IsTree()
		{
			if (m_vs.size() != m_edges_count + 1) return false;

			// check connectedness
			queue<int> in_progress;
			in_progress.push(m_root);

			unordered_set<int> seen;
			seen.insert(m_root);

			while (!in_progress.empty())
			{
				auto cur = in_progress.front();
				for (auto v : m_vs[cur])
				{
					if (seen.count(v) == 0)
					{
						in_progress.push(v);
						seen.insert(v);
					}
				}

				in_progress.pop();
			}
			return seen.size() == m_vs.size();
		}
	};

	TEST_CLASS(PT07Y)
	{
	public:
		TEST_METHOD(IsTree)
		{
			EDGES edges{ { 4,3 },{ 4,5 },{ 4,6 },{ 3,1 },{ 3,2 },{ 6,7 },{ 7,8 } };
			Assert::IsTrue(CGraph(edges).IsTree());
		}

		TEST_METHOD(ConnectedWithCycle)
		{
			EDGES edges{ { 4,3 },{ 4,5 },{ 4,6 },{ 3,1 },{ 3,2 },{ 6,7 },{ 7,8 },{ 4,8 } };
			Assert::IsFalse(CGraph(edges).IsTree());
		}

		TEST_METHOD(DisconnectedSubTrees)
		{
			EDGES edges{ { 4,3 },{ 4,5 },{ 4,6 },{ 3,1 },{ 3,2 },{ 6,7 },{ 7,8 },{ 9,10 }, { 9,11 }, { 9,12 }, { 11,13 } };
			Assert::IsFalse(CGraph(edges).IsTree());
		}

		TEST_METHOD(DisconnectedWithCycles)
		{
			EDGES edges{ { 4,3 },{ 4,5 },{ 4,6 },{ 3,1 },{ 3,2 },{ 6,7 },{ 7,8 },{ 9,10 },{ 9,11 },{ 9,12 },{ 11,13 },{ 12,13 } };
			Assert::IsFalse(CGraph(edges).IsTree());
		}

		TEST_METHOD(MaxVertices)
		{
			EDGES edges;
			for (int i = 2; i <= 10000; i++)
				edges.push_back({ 1, i });
			Assert::IsTrue(CGraph(edges).IsTree());
		}
	};
}
#endif