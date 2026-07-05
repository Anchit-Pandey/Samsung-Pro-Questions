#include<bits/stdc++.h>
using namespace std;

int solve(int i, vector<int> &a, vector<int> &b, int right, vector<vector<int>> &dp) {
    if(i == 1) {
        return right ? a[0] : 0;
    }
    if(dp[i][right] != -1) return dp[i][right];
    int ans;
    if(!right)
    ans = min(solve(i-1, a, b, 0, dp) + a[i-1], solve(i-1, a, b, 1, dp) + 0);
    else
    ans = min(solve(i-1, a, b, 0, dp) + b[i-1], solve(i-1, a, b, 1, dp) + a[i-1]);
    return dp[i][right] = ans;
}

int main() {
    int t;
    cin>>t;
    for(int test = 1; test <= t; test++) {
        int n;
        cin>>n;
        vector<int> a(n), b(n);
        vector<vector<int>> dp(n+1, vector<int>(2, -1));
        for(int i = 0; i < n; i++) cin>>a[i];
        for(int j = 0; j < n; j++) cin>>b[j];
        cout<<"#"<<test<<" "<<solve(n, a, b, 0, dp)<<'\n';
    }
    return 0;
}