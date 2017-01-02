// http://www.spoj.com/problems/HOTELS

#include "stdafx.h"
#include "CppUnitTest.h"
#include <limits>

#include <algorithm>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

#if 0
namespace SPOJ
{
	TEST_CLASS(HOTELS)
	{
		long GetBestOffer(long budget, const vector<long>& hotels)
		{
			long offer = 0;
			auto s = hotels.begin();
			auto e = hotels.begin();

			long cur = 0;
			while (s != hotels.end())
			{
				if (budget - cur < *e)
				{
					cur -= *s;
					++s;
				}
				else
				{
					cur += *e;
					if (offer < cur) offer = cur;

					++e;
					if (e == hotels.end()) return offer;
				}
			}

			return offer;
		}

#if 0
		int main()
		{
			long c, budget;
			cin >> c >> budget;

			vector<long> hotels;
			hotels.reserve(c);
			for (long i = 0; i < c; i++)
			{
				long h;
				cin >> h;
				hotels.push_back(h);
			}
			cout << GetBestOffer(budget, hotels) << endl;

			char q;
			cin >> q;
			return 0;
		}
#endif

	public:
		TEST_METHOD(SingleCanBuy_No)
		{
			Assert::AreEqual<long>(0, GetBestOffer(3, vector<long>{7}));
		}

		TEST_METHOD(SingleCanBuy_Yes)
		{
			Assert::AreEqual<long>(7, GetBestOffer(8, vector<long>{7}));
		}

		TEST_METHOD(Prefix)
		{
			Assert::AreEqual<long>(9, GetBestOffer(9, vector<long>{5, 4, 2, 1}));
		}

		TEST_METHOD(Middle)
		{
			Assert::AreEqual<long>(9, GetBestOffer(9, vector<long>{1, 5, 4, 2, 1}));
		}

		TEST_METHOD(Suffix)
		{
			Assert::AreEqual<long>(9, GetBestOffer(9, vector<long>{1, 2, 3, 5, 4}));
		}

		TEST_METHOD(All)
		{
			Assert::AreEqual<long>(10, GetBestOffer(10, vector<long>{2, 4, 3, 1}));
		}

		TEST_METHOD(ExpensivePalace)
		{
			Assert::AreEqual<long>(8, GetBestOffer(9, vector<long>{1, 2, 3, 5, 12, 1}));
		}

		TEST_METHOD(Max)
		{
			vector<long> hotels(300000, 1000000);
			Assert::AreEqual<long>(2147000000, GetBestOffer(numeric_limits<long>::max() - 10, hotels));
		}

		TEST_METHOD(FromSpoj)
		{
			Assert::AreEqual<long>(12, GetBestOffer(12, vector<long>{2, 1, 3, 4, 5}));
			Assert::AreEqual<long>(8, GetBestOffer(9, vector<long>{7, 3, 5, 6}));
		}
	};
}
#endif