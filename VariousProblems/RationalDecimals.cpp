// From https://leetcode.com/problems/fraction-to-recurring-decimal/

#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#if 0
namespace VariousProblems
{
	std::string GetDecimalNotation(unsigned int a, unsigned int b)
	{
		std::string whole = std::to_string(a / b);

		// TODO: sequence of remainders -> perf: replace with a set/map?
		std::vector<unsigned int> rs; 

		std::string decimal;
		a = a % b;
		while (a != 0)
		{
			rs.push_back(a);

			a *= 10;
			decimal.append(std::to_string(a / b));
			a = a % b;

			auto pos = std::find(rs.cbegin(), rs.cend(), a);
			if (pos != rs.end())
			{
				decimal = decimal.substr(0, pos - rs.begin()) + 
					std::string("(") + decimal.substr(pos - rs.begin()) + ")";

				break;
			}
		}

		return (decimal.empty()) ? whole : whole + "." + decimal;
	}

	TEST_CLASS(RationalDecimals)
	{
	public:

		TEST_METHOD(WholeNumber)
		{
			Assert::AreEqual(std::string("1"), GetDecimalNotation(1, 1));
		}

		TEST_METHOD(FinateDecimal_OneDigit)
		{
			Assert::AreEqual(std::string("0.5"), GetDecimalNotation(1, 2));
		}

		TEST_METHOD(FinateDecimal_TreeDigits)
		{
			Assert::AreEqual(std::string("0.042"), GetDecimalNotation(21, 500));
		}

		TEST_METHOD(CycleOfLengthOne_NoPreCycle)
		{
			Assert::AreEqual(std::string("0.(3)"), GetDecimalNotation(1, 3));
		}

		TEST_METHOD(LongCycle_NoPreCycle)
		{
			Assert::AreEqual(std::string("0.(142857)"), GetDecimalNotation(1, 7));
		}

		TEST_METHOD(ShortCycle_PreCycle)
		{
			Assert::AreEqual(std::string("0.1(6)"), GetDecimalNotation(1, 6));
		}

		TEST_METHOD(BiggerDenominator)
		{
			Assert::AreEqual(std::string("0.02(27)"), GetDecimalNotation(1, 44));
		}
	};
}
#endif