// http://www.spoj.com/problems/BITMAP/

#include "stdafx.h"
#include "CppUnitTest.h"

#include <algorithm>
#include <vector>
#include <numeric>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

#if 0
namespace SPOJ
{
	constexpr int no_white = numeric_limits<int>::max() - 1;
	vector<int> GetDistances(const string& pixels)
	{
		vector<int> dists(pixels.size(), no_white);
		int white = pixels.size();
		for (int i = 0; i < pixels.size(); i++)
		{
			if (pixels[i] == '1')
			{
				dists[i] = 0;
				// backtrack
				for (int j = i - 1; j >= 0; j--)
				{
					if (dists[j] > i - j) dists[j] = i - j;
					else break;
				}
				white = i;
			}
			else
			{
				if (white < pixels.size())
					dists[i] = i - white;
			}
		}
		return dists;
	}

	vector<vector<int>> GetDistances(const vector<string>& pixels)
	{
		const int rows = pixels.size();
		const int cols = pixels.front().length();

		vector<vector<int>> dists;
		dists.reserve(rows);
		for (const auto& row : pixels)
			dists.push_back(GetDistances(row));

		// go column by column
		for (int col = 0; col < cols; col++)
		{
			for (int row = 1; row < rows; row++)
			{
				if (dists[row][col] > dists[row - 1][col] + 1)
					dists[row][col] = dists[row - 1][col] + 1;
				else
				{
					for (int j = row - 1; j >= 0; j--)
					{
						if (dists[j][col] > dists[row][col] + (row - j)) dists[j][col] = dists[row][col] + (row - j);
						else break;
					}
				}
			}
		}
		return dists;
	}

	TEST_CLASS(BITMAP)
	{
		string GetDistances_(const string& pixels)
		{
			auto dists = GetDistances(pixels);
			string s{ "" };
			for (auto d : dists) s.append(to_string(d) + " ");
			if (!s.empty()) s.resize(s.size() - 1);
			return s;
		}

		string GetDistances_(const vector<string>& pixels)
		{
			auto dists = GetDistances(pixels);
			string s{ "" };
			for (auto row : dists)
			{
				for (auto d : row)
					s.append(to_string(d) + " ");
				if (!s.empty()) s.resize(s.size() - 1);
				s.append(";");
			}
			if (!s.empty()) s.resize(s.size() - 1);
			return s;
		}
	public:
		TEST_METHOD(Row_SinglePixel)
		{
			Assert::AreEqual<string>("0", GetDistances_("1"));
			Assert::AreEqual<string>(to_string(no_white), GetDistances_("0"));
		}

		TEST_METHOD(Row_FirstPixelWhite)
		{
			Assert::AreEqual<string>("0 1 2 3", GetDistances_("1000"));
		}

		TEST_METHOD(Row_LastPixelWhite)
		{
			Assert::AreEqual<string>("3 2 1 0", GetDistances_("0001"));
		}

		TEST_METHOD(Row_TwoWhitePixels)
		{
			Assert::AreEqual<string>("1 0 1 2 1 0 1 2", GetDistances_("01000100"));
		}

		TEST_METHOD(IdenticalRows)
		{
			Assert::AreEqual<string>("0 1 2;0 1 2", GetDistances_(vector<string>{"100", "100"}));
		}

		TEST_METHOD(FirstRowWhite_SecondRowBlack)
		{
			Assert::AreEqual<string>("0 0 0;1 1 1", GetDistances_(vector<string>{"111", "000"}));
		}

		TEST_METHOD(FirstRowBlack_SecondRowWhite)
		{
			Assert::AreEqual<string>("1 1 1;0 0 0", GetDistances_(vector<string>{"000", "111"}));
		}

		TEST_METHOD(BottomRightPixelWhite)
		{
			Assert::AreEqual<string>("5 4 3 2;4 3 2 1;3 2 1 0", GetDistances_(vector<string>{"0000", "0000", "0001"}));
		}

		TEST_METHOD(BottomLeftPixelWhite)
		{
			Assert::AreEqual<string>("2 3 4 5;1 2 3 4;0 1 2 3", GetDistances_(vector<string>{"0000", "0000", "1000"}));
		}

		TEST_METHOD(ExampleFromSpoj)
		{
			Assert::AreEqual<string>("3 2 1 0;2 1 0 0;1 0 0 1", GetDistances_(vector<string>{"0001", "0011", "0110"}));
		}

		TEST_METHOD(MaxSize)
		{
			vector<string> bitmap;
			bitmap.push_back(string(181, '0') + string("1"));
			for (int i = 1; i < 181; i++)
				bitmap.push_back(string(181 - i, '0') + string("1") + string(i, '0'));
			bitmap.push_back(string("1") + string(181, '0'));

			Assert::AreEqual<string>("181 180 179 178 177 176 175 174 173 ", GetDistances_(bitmap).substr(0, 36));

		}
	};
}
#endif