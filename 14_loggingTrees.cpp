#include<bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin>>t;
    for(int test = 1; test <= t; test++) {
        unordered_map<int, vector<int>> mp;
        int l, r, n;
        cin>>n;
        int maxHeight = 0;
        for(int i = 0; i <= n; i++) {
            cin>>l>>r;
            maxHeight = max(maxHeight, max(l, r));
            if(l) mp[l].push_back(i);
            if(r) mp[r].push_back(i);
        }
        vector<int> costCount(maxHeight+1);
        for(auto it : mp) {
            auto v = it.second;
            int sz = v.size();
            int ans = 1;
            for(int i = 1; i < sz; i++) {
                ans += (v[i]-v[i-1]);
                ans++;
            }
            costCount[it.first] = ans;
        }
        vector<vector<int>> dp(maxHeight+1, vector<int>(n+2, -1));
        auto func = [&](int len, int pos, auto&& func) {
            if(!len)
            return abs(n-pos);
            if(mp.find(len) == mp.end())
            return func(len-1, pos, func);
            if(dp[len][pos] != -1) return dp[len][pos];
            int left = mp[len][0];
            int sz = mp[len].size();
            int right = mp[len][sz-1];
            int leftToRight = abs(pos-left) + costCount[len] + func(len-1, right, func);
            int rightToLeft = abs(pos-right) + costCount[len] + func(len-1, left, func);
            return dp[len][pos] = min(leftToRight, rightToLeft);
        };
        cout<<"#"<<test<<" "<<func(maxHeight, 0, func)<<'\n';
    }
    return 0;
}