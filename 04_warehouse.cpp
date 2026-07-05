#include<bits/stdc++.h>
using namespace std;

vector<pair<int, int>> dir = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

void bfs(vector<vector<int>> &mat, vector<vector<int>> &dist, int i, int j) {
    int h = mat.size(), w = mat[0].size();
    dist[i][j] = 0;
    queue<pair<int, int>> q;
    q.push({i, j});
    while(!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        for(auto it : dir) {
            int nr = r + it.first;
            int nc = c + it.second;
            if(nr >= 0 && nr < h && nc >= 0 && nc < w && mat[nr][nc] != 1 && 
            dist[nr][nc] > 1 + dist[r][c]) {
                dist[nr][nc] = 1 + dist[r][c];
                q.push({nr, nc});
            }
        }
    }
}

int solve(vector<vector<int>> &mat, vector<pair<int, int>> &warehouse, int c) {
    int h = mat.size(), w = mat[0].size();
    vector<vector<int>> gw(h, vector<int>(w, INT_MAX));
    vector<vector<int>> wa(h, vector<int>(w, INT_MAX));
    bfs(mat, gw, 0, 0);
    bfs(mat, wa, h-1, w-1);
    int maxGoods = 0;
    for(auto it : warehouse) {
        int currentCost = c;
        currentCost -= gw[it.first][it.second];
        int goods = currentCost/wa[it.first][it.second]-1;
        maxGoods = max(maxGoods, goods);
    }
    return maxGoods;
}

int main() {
    int t;
    cin>>t;
    for(int test = 1; test <= t; test++) {
        int h, w, c;
        cin>>h>>w>>c;
        vector<vector<int>> mat(h, vector<int>(w));
        vector<pair<int, int>> warehouse;
        for(int i = 0; i < h; i++) {
            for(int j = 0; j < w; j++) {
                cin>>mat[i][j];
                if(mat[i][j] == 3)
                warehouse.push_back({i, j});
            }
        }
        cout<<"#"<<test<<" "<<solve(mat, warehouse, c)<<'\n';
    }
    return 0;
}