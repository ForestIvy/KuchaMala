// http://www.spoj.com/problems/BYTESM2/

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
	class CStonesCollector
	{
		vector<long> m_cache;

	public:
		CStonesCollector(vector<long> first_row)
			: m_cache(move(first_row))
		{
		}

		long GetCurrentMax()
		{
			if (m_cache.empty()) return 0;

			return *max_element(m_cache.begin(), m_cache.end());
		}

		void AddRow(const vector<long> row)
		{
			if (m_cache.empty()) return;

			if (m_cache.size() == 1)
			{
				m_cache[0] += row[0];
				return;
			}

			vector<long> cache(m_cache.size(), 0);
			cache[0] = row[0] + max(m_cache[0], m_cache[1]);
			cache[m_cache.size() - 1] = row.back() + max(m_cache[m_cache.size() - 1], m_cache[m_cache.size() - 2]);
			
			for (size_t i = 1; i < m_cache.size() - 1; i++)
				cache[i] = row[i] + max(m_cache[i - 1], max(m_cache[i], m_cache[i + 1]));

			m_cache.swap(cache);
		}
	};

	TEST_CLASS(BYTESM2)
	{
	public:
		TEST_METHOD(AfterFirstRow)
		{
			Assert::AreEqual(42l, CStonesCollector{ vector<long>{5, 17, 42, 10} }.GetCurrentMax());
		}

		TEST_METHOD(AfterUniformRowAdded)
		{
			CStonesCollector sc{ vector<long>{5, 17, 42, 10} };
			sc.AddRow(vector<long>{1, 1, 1, 1});

			Assert::AreEqual(43l, sc.GetCurrentMax());
		}

		TEST_METHOD(OneItemPerRow)
		{
			CStonesCollector sc{ vector<long>{5} };
			sc.AddRow(vector<long>{1});

			Assert::AreEqual(6l, sc.GetCurrentMax());
		}

		TEST_METHOD(SampleFromSpoj)
		{
			CStonesCollector sc{ 
					  vector<long>{3, 1, 7, 4, 2} };
			sc.AddRow(vector<long>{2, 1, 3, 1, 1});
			sc.AddRow(vector<long>{1, 2, 2, 1, 8});
			sc.AddRow(vector<long>{2, 2, 1, 5, 3});
			sc.AddRow(vector<long>{2, 1, 4, 4, 4});
			sc.AddRow(vector<long>{5, 2, 7, 5, 1});

			Assert::AreEqual(7l + 1 + 8 + 5 + 4 + 7, sc.GetCurrentMax());
		}

		TEST_METHOD(MaxValues)
		{
			vector<long> stones(100, 1000);
			CStonesCollector sc{ stones };
			for (int i = 1; i < 100; i++)
				sc.AddRow(stones);

			Assert::AreEqual(100l * 1000, sc.GetCurrentMax());
		}

		TEST_METHOD(LeftBoundary)
		{
			vector<long> odd{ 7, 1, 2, 1 };
			vector<long> even{ 5, 8, 9, 10 };

			CStonesCollector sc{ odd };
			sc.AddRow(even);
			sc.AddRow(odd);
			sc.AddRow(even);
			sc.AddRow(odd);

			Assert::AreEqual(7l + 8 + 7 + 8 + 7, sc.GetCurrentMax());
		}

		TEST_METHOD(RightBoundary)
		{
			vector<long> odd{ 7, 1, 6, 1 };
			vector<long> even{ 5, 8, 9, 10 };

			CStonesCollector sc{ odd };
			sc.AddRow(even);
			sc.AddRow(odd);
			sc.AddRow(even);
			sc.AddRow(odd);

			Assert::AreEqual(6l + 10 + 6 + 10 + 6, sc.GetCurrentMax());
		}
	};
}
#endif