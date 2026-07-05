#include<bits/stdc++.h>
using namespace std;

int solve(string s, int sum, int ind, int tight,vector<vector<vector<int>>> &dp) {
    if(dp[ind][sum][tight] != -1) return dp[ind][sum][tight];
    if(ind == s.size()) return sum == 0;
    int limit = tight ? s[ind]-'0' : 9;
    int ans = 0;
    for(int d = 0; d <= limit; d++) {
        if(d <= sum)
        ans += solve(s, sum-d, ind+1, tight && (d == limit), dp);
    }
    return dp[ind][sum][tight] = ans;
}

int main() {
    int t;
    cin>>t;
    for(int test = 1; test <= t; test++) {
        string s;
        int sum;
        cin>>s>>sum;
        int n = s.size();
        vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(sum+1, vector<int>(2, -1)));
        cout<<"#"<<test<<" "<<solve(s, sum, 0, 1, dp)<<'\n';
    }
    return 0;
}