#include "string_algorithms.hh"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

vector<int> suffix_array_naive(string& s){
    vector<string> suffixes;
    for(int i = 0; i < s.size(); i++)
        suffixes.push_back(s.substr(i));
    sort(suffixes.begin(), suffixes.end());
    vector<int> SA(s.size());;
    for(int i = 0; i < s.size(); i++){
        int pos = s.size() - suffixes[i].size();
        SA[i] = pos;
    }
    return SA;
}

vector<int> naive_pattern_matching(string& p, string& s){
    int k = p.size();
    int n = s.size();
    vector<int> positions;
    for(int i = 0; i <= n-k; i++){
        if(s.substr(i,k) == p)
            positions.push_back(i);
    }
    return positions;
}

string get_random_string(vector<char>& alphabet, int length){
    string s;
    for(int i = 0; i < length; i++){
        s += alphabet[rand()%alphabet.size()];
    }
    return s;
}

vector<string> all_binary_substrings_up_to(int k){
    vector<string> ans;
    for(int length = 1; length <= k; length++){
        for(int mask = 0; mask < (1 << length); mask++){
            string s = "";
            for(int i = 0; i < length; i++){
                if(mask & (1 << i)) s += 'a';
                else s += 'b';
            }
            ans.push_back(s);
        }
    }
    return ans;
}

int main(int argc, char** argv){
    srand(time(0));
    // Test all binary strings with length <= maxlength
    int SA_max = 16;
    for(string s : all_binary_substrings_up_to(SA_max)) 
        assert(suffix_array_naive(s) == get_suffix_array(s));
    cout << "Suffix array correct for all substrings of length <= " << SA_max << endl;
    
    int kmp_max = 10;
    vector<string> kmp_all = all_binary_substrings_up_to(kmp_max);
    for(string s : kmp_all){
        for(string p : kmp_all){
            assert(naive_pattern_matching(p,s) == kmp(p,s));
        }
    }
    cout << "KMP correct for all substrings of length <= " << kmp_max << endl;

    int rabin_karp_max = 10;
    vector<string> rabin_karp_all = all_binary_substrings_up_to(rabin_karp_max);
    for(string s : rabin_karp_all){
        for(string p : rabin_karp_all){
            assert(naive_pattern_matching(p,s) == rabin_karp(p,s));
        }
    }
    cout << "Rabin Karp correct for all substrings of length <= " << rabin_karp_max << endl;
}