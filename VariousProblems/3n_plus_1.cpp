// From http://www.programming-challenges.com/pg.php?page=downloadproblem&probid=110101&format=html
// when submitting remove include for stdafx.h and make a loop on cin for input:
//int main()
//{
//	long a, b;
//	while (std::cin >> a >> b)
//	{
//		std::cout << a << " " << b << " " << MaxChainLength(std::min(a, b), std::max(a, b)) << std::endl;
//	}
//	return 0;
//}


#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include <algorithm>
#include <limits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#if 0
namespace VariousProblems
{
	long MaxChainLength(long a, long b)
	{
		unsigned long l = 1;
		std::vector<unsigned long> check(b - a + 1, 0);

		const auto cur_max = (std::numeric_limits<unsigned long long>::max() - 1)/3;

		for (auto i = a; i <= b; i++)
		{
			unsigned long long cur = i;
			unsigned long li = 1;
			while (cur != 1)
			{
				if (cur >= a && cur <= b)
				{
					if (check[cur - a] >= li) break;
					check[cur - a] = li;
				}

				if (cur % 2 == 0) 
					cur = cur / 2;
				else
				{
					if (cur > cur_max) throw 0;
					cur = 3 * cur + 1;
				}

				li++;
			}
			l = std::max(l, li);
		}
		return l;
	}

	TEST_CLASS(ThreeN_plus_One)
	{
	public:

		TEST_METHOD(SingleNumber_PowerOfTwo)
		{
			Assert::AreEqual(4l, MaxChainLength(8, 8));
		}

		TEST_METHOD(SingleNumber_9)
		{
			Assert::AreEqual(20l, MaxChainLength(9, 9));
		}

		TEST_METHOD(Range_1_10)
		{
			Assert::AreEqual(20l, MaxChainLength(1, 10));
		}

		TEST_METHOD(Range_100_200)
		{
			Assert::AreEqual(125l, MaxChainLength(100, 200));
		}

		TEST_METHOD(Range_201_210)
		{
			Assert::AreEqual(89l, MaxChainLength(201, 210));
		}

		TEST_METHOD(Range_900_1000)
		{
			Assert::AreEqual(174l, MaxChainLength(900, 1000));
		}

		TEST_METHOD(Range_1_100000)
		{
			Assert::AreEqual(351l, MaxChainLength(1, 100000));
		}

		TEST_METHOD(Range_long_overflow)
		{
			Assert::AreEqual(241l, MaxChainLength(191335, 191335));
		}

		TEST_METHOD(Range_1_1000000)
		{
			Assert::AreEqual(525l, MaxChainLength(1, 1000000));
			Assert::AreEqual(MaxChainLength(1, 1000000), std::max(MaxChainLength(1, 9999), MaxChainLength(9999, 1000000)));
		}
	};
}
#endif