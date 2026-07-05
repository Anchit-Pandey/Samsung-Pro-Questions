#include<bits/stdc++.h>
using namespace std;

int func(vector<pair<int, int>> v, int i, int day) {
    if(!day) return 0;
    if(!i) return INT_MIN;
    int notSell = 0 + func(v, i-1, day);
    int sell = INT_MIN;
    int sub = func(v, i-1, day-1);
    if(sub != INT_MIN)
    sell = sub + v[i-1].second+v[i-1].first*day;
    return max(sell, notSell);
}

int main() {
    int t;
    cin>>t;
    for(int test = 1; test <= t; test++) {
        int n, k, asum = 0, bsum = 0;
        cin>>n>>k;
        vector<pair<int, int>> v(n);
        int a, b;
        for(int i = 0; i < n; i++) {
            cin>>a>>b;
            asum += a;
            bsum += b;
            v[i] = {b, a};
        }
        if(asum+bsum <= k) {
            cout<<"#"<<test<<" "<<0<<'\n';
            continue;
        }
        sort(v.begin(), v.end());
        int ans = -1;
        for(int d = 0; d <= n; d++) {
            int savings = func(v, n, d);
            if(savings == INT_MIN) continue;
            if(asum+bsum*d-savings <= k) {
                cout<<"#"<<test<<" "<<d<<'\n';
                return 0;
            }
        }
    }
    return 0;
}