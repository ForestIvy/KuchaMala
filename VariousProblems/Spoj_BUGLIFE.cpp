// http://www.spoj.com/problems/BUGLIFE/

#include "stdafx.h"
#include "CppUnitTest.h"

#include <algorithm>
#include <vector>
#include <numeric>
#include <stack>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

#if 1
namespace SPOJ
{
	class BugColony
	{
		int max_id;
		vector<vector<int>> relations;

	public:
		BugColony(int id) : max_id(id), relations(max_id + 1, vector<int>()) {}

		bool AddRelationship(int one, int another)
		{
			if (max_id < max(one, another)) throw 0;
			relations[one].push_back(another);
			relations[another].push_back(one);
		}
		bool IsConforming()
		{
			if (relations.size() <= 2) return true;

			vector<int> seen(max_id + 1, -1);
			stack<int> in_progress;

			auto start_at = seen.begin() + 1;
			while (start_at != seen.end())
			{
				*start_at = 0;
				in_progress.push(start_at - seen.begin());
				while (!in_progress.empty())
				{
					int cur = in_progress.top();
					bool shouldPop = true;
					for (int i = 0; i < relations[cur].size(); i++)
					{
						int next = relations[cur][i];
						if (seen[next] == -1)
						{
							seen[next] = in_progress.size();
							in_progress.push(next);
							shouldPop = false;
							break;
						}
						else
						{
							int dist = in_progress.size() - seen[next];
							if (dist % 2 != 0) return false;
						}
					}
					if (shouldPop)
						in_progress.pop();
				}
				start_at = find_if(start_at, seen.end(), [](int n) { return n == -1;});
			}
			return true;
		}
	};
	TEST_CLASS(BUGLIFE)
	{
		bool IsConforming(int max_id, vector<pair<int, int>> rels)
		{
			BugColony bc(max_id);
			for (auto& rel : rels) bc.AddRelationship(rel.first, rel.second);

			return bc.IsConforming();
		}
	public:
		TEST_METHOD(LoneBug)
		{
			Assert::IsTrue(IsConforming(1,vector<pair<int, int>>{}));
		}

		TEST_METHOD(OverallOddCycle)
		{
			Assert::IsFalse(IsConforming(3,vector<pair<int, int>>{ {1,2},{2,3},{1,3} }), L"3");
			Assert::IsFalse(IsConforming(5, vector<pair<int, int>>{ {1, 2}, { 2,3 }, { 3,4 }, { 4,5 }, { 5,1 } }), L"5");
		}

		TEST_METHOD(OverallEvenCycle)
		{
			Assert::IsTrue(IsConforming(4, vector<pair<int, int>>{ {1, 2}, { 2,3 }, { 3,4 }, { 4,1 }}));
		}

		TEST_METHOD(OddAndEvenConnectedCycles)
		{
			Assert::IsFalse(IsConforming(5, vector<pair<int, int>>{ {1, 2}, { 2,3 }, { 3,4 }, { 4,5 }, { 1,5 }, { 2,5 }}));
		}

		TEST_METHOD(DisconnectedOddCycle)
		{
			Assert::IsFalse(IsConforming(5, vector<pair<int, int>>{ {1, 2}, { 3,4 }, { 4,5 }, { 5,3 }}));
		}
	};
}
#endif