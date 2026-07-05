#include<bits/stdc++.h>
using namespace std;

int countTiles(vector<vector<int>> &prefix, int h1, int w1, int h2, int w2) {
    int count = prefix[h2][w2];
    if(h1 > 0) count -= prefix[h1-1][w2];
    if(w1 > 0) count -= prefix[h2][w1-1];
    if(h1 > 0 && w1 > 0) count += prefix[h1-1][w1-1];
    return count;
}

bool possible(vector<vector<int>> &prefix, int mid, int k) {
    for(int i = 0; i+mid< 401; i++) {
        for(int j = 0; j+mid < 401; j++) {
            int cnt = countTiles(prefix, i, j, i+mid, j+mid);
            if(cnt >= k)
            return true;
        }
    }
    return false;
}

int main() {
    int t;
    cin>>t;
    for(int test = 1; test <= t; test++) {
        int n, k;
        cin>>n>>k;
        vector<vector<int>> freq(401, vector<int>(401, 0));
        int h, w;
        for(int i = 0; i < n; i++) {
            cin>>h>>w;
            freq[h][w]++;
        }
        vector<vector<int>> prefix(401, vector<int>(401, 0));
        for(int i = 0; i < 401; i++) {
            for(int j = 0; j < 401; j++) {
                prefix[i][j] = freq[i][j];
                if(i > 0) prefix[i][j] += prefix[i-1][j];
                if(j > 0) prefix[i][j] += prefix[i][j-1];
                if(i > 0 && j > 0) prefix[i][j] -= prefix[i-1][j-1];
            }
        }
        int low = 0, high = 400;
        while(low <= high) {
            int mid = low + (high - low) / 2;
            if(possible(prefix, mid, k))
            high = mid - 1;
            else
            low = mid + 1;
        }
        cout<<"#"<<test<<" "<<low<<'\n';
    }
    return 0;
}