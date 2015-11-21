#pragma once

#include <vector>
#include <string>

std::vector<int> get_suffix_array(std::string& s);

// returns all indices in s that are the start of the pattern p
std::vector<int> rabin_karp(std::string& p, std::string& s);

// returns all indices in s that are the start of the pattern p
std::vector<int> kmp(std::string& pattern, std::string& s);
