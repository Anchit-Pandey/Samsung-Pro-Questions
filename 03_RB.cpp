#include<bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin>>t;
    for(int test = 1; test <= t; test++) {
        string s;
        cin>>s;
        map<int, int> prefix;
        prefix[0] = -1;
        int sum = 0;
        int maxLen = 0;
        for(int i = 0; i < s.size(); i++) {
            sum += s[i] == 'R' ? -1 : 1;
            if(prefix.find(sum) == prefix.end())
            prefix[sum] = i;
            else 
            maxLen = max(maxLen, i-prefix[sum]);
        }
        cout<<"#"<<test<<" "<<s.size()-maxLen<<'\n';
    }
    return 0;
}