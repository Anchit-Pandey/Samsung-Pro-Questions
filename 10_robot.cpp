#include<bits/stdc++.h>
using namespace std;

int solve(vector<int> &arr, int ind, int lastInd, vector<vector<int>> &dp, int m) {
    if(dp[ind][lastInd] != -1) return dp[ind][lastInd];
    if(ind  == arr.size()) return 0;
    int notPlace = arr[ind]*(ind-lastInd) + solve(arr, ind+1, lastInd, dp, m);
    int place = m + solve(arr, ind+1, ind, dp, m);
    return dp[ind][lastInd] = min(place, notPlace);
}

int main() {
    int t;
    cin>>t;
    for(int test = 1; test <= t; test++) {
        int n, m;
        cin>>n>>m;
        vector<int> arr(n);
        for(int i = 0; i< n; i++)
        cin>>arr[i];
        int i = 0;
        for(; i < n; i++) {
            if(arr[i] != 0)
            break;
        }
        if(i == n) {
            cout<<"#"<<test<<" "<<0<<'\n';
            return 0;
        }
        vector<vector<int>> dp(n+1, vector<int>(n+1, -1));
        cout<<"#"<<test<<" "<<m+solve(arr, i+1, i, dp, m)<<'\n';
    }
    return 0;
}