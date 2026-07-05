#include<bits/stdc++.h>
using namespace std;

bool inSegments(int val, vector<pair<int, int>> &range) {
    int low = 0, high = range.size()-1;
    int ans = -1;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(val >= range[mid].first) {
            ans = mid;
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    if(ans == -1) return false;
    return (val <= range[ans].second);
}

vector<pair<int, int>> mergeIntervals(vector<pair<int, int>> &intervals) {
    sort(intervals.begin(), intervals.end());
    vector<pair<int, int>> merge;
    for(int i = 0; i < intervals.size(); i++) {
        if(merge.empty() || intervals[i].first > merge.back().second)
        merge.push_back(intervals[i]);
        else
        merge.back().second = max(merge.back().second, intervals[i].second);
    }
    return merge;
}

int countPoints(vector<int> &Xp, vector<int> &Yp, vector<int> &Xq, vector<int> &Yq) {
    int n = Xp.size();
    int m = Xq.size();
    unordered_map<int, vector<pair<int, int>>> horSeg;
    unordered_map<int, vector<pair<int, int>>> verSeg;
    for(int i = 1; i < n; i++) {
        if(Xp[i] == Xp[i-1])
        verSeg[Xp[i]].push_back({min(Yp[i], Yp[i-1]), max(Yp[i], Yp[i-1])});
        else
        horSeg[Yp[i]].push_back({min(Xp[i], Xp[i-1]), max(Xp[i], Xp[i-1])});
    }
    unordered_map<int, vector<pair<int, int>>> horizontal;
    unordered_map<int, vector<pair<int, int>>> vertical;
    for(auto s : verSeg)
    vertical[s.first] = mergeIntervals(s.second);
    for(auto s : horSeg)
    horizontal[s.first] = mergeIntervals(s.second);
    int count = 0;
    for(int i = 0; i < m; i++) {
        bool inHor = horizontal.count(Yq[i]) && inSegments(Xq[i], horizontal[Yq[i]]);
        bool inVer = vertical.count(Xq[i]) && inSegments(Yq[i], vertical[Xq[i]]);
        if(inHor || inVer) count++;
    }
    return count;
}

int main() {
    int t;
    cin>>t;
    for(int test = 1; test <= t; test++) {
        int n, m;
        cin>>n>>m;
        vector<int> Xp(n), Xq(m), Yp(n), Yq(m);
        for(int i = 0; i < n; i++) cin>>Xp[i];
        for(int i = 0; i < n; i++) cin>>Yp[i];
        for(int i = 0; i < m; i++) cin>>Xq[i];
        for(int i = 0; i < m; i++) cin>>Yq[i];
        cout<<"#"<<test<<" "<<countPoints(Xp, Yp, Xq, Yq);
    }
    return 0;
}