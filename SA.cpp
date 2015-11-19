#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
 
using namespace std;
 
typedef long long LL;

vector<int> get_suffix_array(string s){
    int n = s.size();
    vector<int> v(n);
    for(int i = 0; i < n; i++) v[i] = (int) s[i];
    for(int L = 2; L <= n; L *= 2){
        vector<pair<pair<int,int>, int> > pairs(n);
        for(int i = 0; i < n; i++){
            pairs[i] = {{v[i], (i + L/2 < n) ? v[i+L/2] : -1}, i};
        }
        sort(pairs.begin(), pairs.end());
        int rank = 0;
        for(int i = 0; i < n; i++){
            if(i > 0 && pairs[i].first != pairs[i-1].first) rank++;
            v[pairs[i].second] = rank;
        }
    }
    vector<int> SA(n);
    for(int i = 0; i < n; i++) SA[v[i]] = i;
    return SA;
}

int main(){
    string s = "ababbaabbaababaaababa";
    cout << s << endl;
    for(auto x : get_suffix_array(s)) cout << x << " "; cout << endl;
    for(auto x : get_suffix_array(s)) cout << s.substr(x) << endl;
    return 0;
}
