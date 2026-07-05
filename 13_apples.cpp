#include<bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin>>t;
    for(int test = 1; test <= t; test++) {
        int n, m;
        cin>>n>>m;
        vector<vector<int>> grid(n, vector<int>(n));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                cin>>grid[i][j];
            }
        }
        const int dx[4] = {0, 1, 0, -1};
        const int dy[4] = {1, 0, -1, 0};
        vector<vector<vector<vector<int>>>> dp(n, vector<vector<vector<int>>>(
            n, vector<vector<int>>(m+1, vector<int>(4, INT_MAX))));
        deque<array<int, 4>> dq;
        int startCnt = grid[0][0] == 1 ? 1 : 0;
        dp[0][0][startCnt][0] = 0;
        dq.push_front({0, 0, startCnt, 0});
        
        auto tryMove = [&](int r, int c, int cnt, int dir, int cost, bool 
        isTurn) {
            int nr = r + dx[dir];
            int nc = c + dy[dir];
            if(nr < 0 || nr >= n || nc < 0 || nc >= n || grid[nr][nc] == -1)
            return;
            int newCnt = cnt + (grid[nr][nc] == cnt+1 ? 1 : 0);
            if(dp[nr][nc][newCnt][dir] > cost) {
                dp[nr][nc][newCnt][dir] = cost;
                if(isTurn) dq.push_back({nr, nc, newCnt, dir});
                else dq.push_front({nr, nc, newCnt, dir});
            }
        };
        
        while(!dq.empty()) {
            array<int, 4> state = dq.front();
            int r = state[0];
            int c = state[1];
            int cnt = state[2];
            int dir = state[3];
            dq.pop_front();
            int currentCost = dp[r][c][cnt][dir];
            tryMove(r, c, cnt, dir, currentCost, false);
            int newDir = (dir+1) % 4;
            tryMove(r, c, cnt, newDir, currentCost+1, true);
        }
        int ans = INT_MAX;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                for(int d = 0; d < 4; d++) {
                    ans = min(dp[i][j][m][d], ans);
                }
            }
        }
        int finalAns = (ans == INT_MAX) ? -1 : ans;
        cout<<"#"<<test<<" "<<finalAns<<'\n'; 
    }
    return 0;
}