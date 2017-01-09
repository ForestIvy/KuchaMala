#pragma once

#include <vector>
#include <string>

using namespace std;

template<typename T>
string VectorToString(const vector<T>& v)
{
	string output("");
	for (const auto& i : v) output.append(to_string(i) + " ");

	if (!output.empty()) output.resize(output.size() - 1);
	return output;
}