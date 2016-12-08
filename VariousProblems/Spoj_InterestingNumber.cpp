// From: http://www.spoj.com/problems/INUMBER/

#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <string>
#include <set>

using namespace std;

class CINumber
{
	unsigned m_n;
	vector<unsigned> m_rems_base; // int - p, unsigned - 10^p % n
	vector<unsigned> m_rems_9; // 9...9 modulo n (index into vector -- number of nines)

public:
	CINumber(unsigned n)
		: m_n(n)
		, m_rems_base(m_n * 2, 0)
		, m_rems_9(m_n * 2, 0)
	{
		m_rems_base[0] = 1;
		m_rems_9[0] = 0;

		for (int i = 1; i < m_n * 2; i++)
		{
			m_rems_base[i] = (m_rems_base[i - 1] * 10) % m_n;
			m_rems_9[i] = (m_rems_base[i - 1] * 9 + m_rems_9[i - 1]) % m_n;
		}
	}

	unsigned RemainderOf(string candidate)
	{
		unsigned rem = 0;
		int place = 0;
		for (auto dit = candidate.rbegin(); dit != candidate.rend(); ++dit)
		{
			char d = *dit;
			rem = (rem + stoi(&d) * m_rems_base[place]) % m_n;
			place++;
		}
		return rem;
	}

	set<tuple<unsigned, unsigned, unsigned>> m_seen;
	string Decomp(unsigned sum, unsigned places, unsigned rem)
	{
		if (sum > places * 9) return "";

		if (places == 1) return sum % m_n == rem ? to_string(sum) : "";

		if (sum == places * 9)
			return m_rems_9[places] == rem ? string(places, '9') : ""; // unique possible decomposition of all nines

		for (unsigned d = 0; d < 10; d++)
		{
			auto d_rem = d * m_rems_base[places - 1] % m_n;
			auto new_rem = (d_rem > rem) ? (m_n + rem - d_rem) % m_n : (rem - d_rem) % m_n;

			auto it = m_seen.find(make_tuple(sum - d, places - 1, new_rem));
			if (it != m_seen.end())
				continue;

			auto decomp = Decomp(sum - d, places - 1, new_rem);
			if (!decomp.empty())
				return to_string(d) + decomp;

			m_seen.insert(make_tuple(sum - d, places - 1, new_rem));
		}

		return "";
	}

	string FindInterestingNumber()
	{
		unsigned places = m_n / 9 + ((m_n % 9 == 0) ? 0 : 1); // start from min possible digits
		while (places < m_n * 2)
		{
			string found = Decomp(m_n, places, 0);
			if (!found.empty())
			{
				if (RemainderOf(found) != 0) throw 0;
				return found;
			}

			places++;
		}
		return string("Gave up after checking numbers up to ") + to_string(m_n * 2) + " digits";
	}
};
#if 0
int main()
{
	int cases;
	cin >> cases;
	vector<unsigned> inputs;
	for (int i = 0; i < cases; i++)
	{
		unsigned t;
		cin >> t;
		inputs.push_back(t);
	}

	for (const auto& input : inputs)
	{
		CINumber solver(input);
		cout << solver.FindInterestingNumber() << endl;
	}
	//char quit;
	//cin >> quit;
	//return 0;
}
#endif
// 7 -> 7
// 10 -> 190
// 100 -> 19999999999900
// 43 -> 99889
// 165 -> 709...95 (17 9's in the middle)

