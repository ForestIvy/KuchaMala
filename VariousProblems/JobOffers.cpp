// From "The Algorithm Design Manual" by Steven S. Skienf
// 1.2 Selecting the Right Jobs

#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#if 0
namespace VariousProblems
{
	struct Segment
	{
		double l;
		double r;

		Segment(double l_in, double r_in)
		: l(l_in)
		, r(r_in)
		{
			if (l > r) std::terminate;
		}

		Segment(const Segment& other)
		: l(other.l)
		, r(other.r)
		{
		}

		bool operator==(const Segment& other) const
		{
			return l == other.l && r == other.r;
		}

		bool operator!=(const Segment& other) const
		{
			return !(*this == other);
		}

		bool StartsEarlier (const Segment& other) const
		{
			return l < other.l;
		}
	};

	std::vector<Segment> SelectJobOffers(std::vector<Segment> offers)
	{
		std::sort(
			offers.begin(), offers.end(), 
			[](const Segment& first, const Segment& second) { return first.StartsEarlier(second); });

		std::vector<Segment> accepted;
		size_t candidate = 0;
		while (candidate < offers.size())
		{
			auto next = candidate + 1;
			while (next < offers.size())
			{
				if (offers[candidate].r >= offers[next].r) // next is inside current
				{
					candidate = next;
					break;
				}
				if (offers[candidate].r <= offers[next].l) // next doesn't overlap with current
				{
					accepted.push_back(offers[candidate]);
					candidate = next;
					break;
				}
				++next;
			}
			if (next == offers.size())
				break;
		}
		if (candidate < offers.size())
			accepted.push_back(offers[candidate]);

		return accepted;
	}


	TEST_CLASS(JobOffers)
	{
	public:
		
		TEST_METHOD(SelectJobOffers_OneOffer)
		{
			Segment offer{ 1, 2 };
			auto jobs = SelectJobOffers(std::vector<Segment>{offer});
			Assert::AreEqual(size_t{ 1 }, jobs.size());
			Assert::IsTrue(offer == jobs[0]);
		}

		TEST_METHOD(SelectJobOffers_TwoOverlapping)
		{
			Segment offer1{ 1, 3 };
			Segment offer2{ 2, 4 };
			auto jobs = SelectJobOffers(std::vector<Segment>{offer1, offer2});
			Assert::AreEqual(size_t{ 1 }, jobs.size());
			Assert::IsTrue(offer1 == jobs[0]);
		}

		TEST_METHOD(SelectJobOffers_OneInsideAnother)
		{
			Segment offer1{ 1, 4 };
			Segment offer2{ 2, 3 };
			auto jobs = SelectJobOffers(std::vector<Segment>{offer1, offer2});
			Assert::AreEqual(size_t{ 1 }, jobs.size());
			Assert::IsTrue(offer2 == jobs[0]);
		}

		TEST_METHOD(SelectJobOffers_TwoNonOverlapping)
		{
			Segment offer1{ 1, 3 };
			Segment offer2{ 4, 5 };
			auto jobs = SelectJobOffers(std::vector<Segment>{offer1, offer2});
			Assert::AreEqual(size_t{ 2 }, jobs.size());
			Assert::IsTrue(offer1 == jobs[0]);
			Assert::IsTrue(offer2 == jobs[1]);
		}

		TEST_METHOD(SelectJobOffers_Three)
		{
			Segment offer1{ 1, 3 };
			Segment offer2{ 2, 5 };
			Segment offer3{ 4, 6 };
			auto jobs = SelectJobOffers(std::vector<Segment>{offer1, offer2, offer3});
			Assert::AreEqual(size_t{ 2 }, jobs.size());
			Assert::IsTrue(offer1 == jobs[0]);
			Assert::IsTrue(offer3 == jobs[1]);
		}

	};
}
#endif