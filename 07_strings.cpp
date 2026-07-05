#include<bits/stdc++.h>
using namespace std;

// int solve(vector<string> &str, int ind, int start, int end, vector<vector<vector<int>>> &dp) {
//     if(ind == str.size()) {
//         if(start == end)
//         return 0;
//         return -1e8;
//     }
//     if(dp[ind][start][end] != -1) return dp[ind][start][end];
//     int ans = solve(str, ind+1, start, end, dp);
//     int sz = str[ind].size();
//     int first = str[ind][0]-'0';
//     int last = str[ind][sz-1]-'0';
//     if(first == end)
//     ans = max(ans, solve(str, ind+1, start, last, dp)+sz);
//     return dp[ind][start][end] = ans;
// }

int main() {
    int t;
    cin>>t;
    for(int test = 1; test <= t; test++) {
        int n;
        cin>>n;
        vector<string> str(n);
        for(int i = 0; i < n; i++)
        cin>>str[i];
        int maxAns = 0;
        vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(10, vector<int>(10, -1e8)));
        for(int s = 0; s < 10; s++) dp[n][s][s] = 0;
        for(int ind = n-1; ind >= 0; ind--) {
            int sz = str[ind].size();
            int first = str[ind][0]-'0';
            int last = str[ind][sz-1]-'0';
            for(int s = 0; s < 10; s++) {
                for(int e = 0; e < 10; e++) {
                    int notTake = dp[ind+1][s][e];
                    int take = (first == e) ? dp[ind+1][s][last]+sz : (int)-1e8;
                    dp[ind][s][e] = max(notTake, take);
                }
            }
        }
        for(int i = 0; i < n; i++) {
            int startChar = str[i][0]-'0';
            maxAns = max(maxAns, dp[i][startChar][startChar]);
        }
        cout<<"#"<<test<<" "<<maxAns<<'\n';
    }
    return 0;
}