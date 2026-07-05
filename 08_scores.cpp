#include<bits/stdc++.h>
using namespace std;

int upperBound(vector<int> &arr, int val) {
    int low = 0, high = arr.size()-1;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(val < arr[mid])
        high = mid - 1;
        else
        low = mid + 1;
    }
    return low;
}

int main() {
    int t;
    cin>>t;
    for(int test = 1; test <= t; test++) {
        int n, m;
        cin>>n>>m;
        vector<int> a(n), b(m);
        for(int i = 0; i < n; i++) cin>>a[i];
        for(int i = 0; i < m; i++) cin>>b[i];
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        set<int> s;
        for(auto it : a) s.insert(it);
        for(auto it : b) s.insert(it);
        vector<int> candidates;
        candidates.push_back(*s.begin()-1);
        for(auto it : s)
        candidates.push_back(it);
        candidates.push_back(*s.rbegin()+1);
        int D = -1, maxDiff = INT_MIN;
        for(auto it : candidates) {
            int ca = upperBound(a, it);
            int cb = upperBound(b, it);
            int diff = 2*(n-m) + (cb-ca);
            if(diff > maxDiff) {
                maxDiff = diff;
                D = it;
            }
        }
        cout<<"#"<<test<<" "<<D<<'\n';
    }
    return 0;
}