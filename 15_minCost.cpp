/*
    PROBLEM  (Codeforces blog/entry/63962)
    --------
    Given a tree with n vertices, vertex i has value a[i].
    Distance between two vertices = number of edges on the path.
    Pick a vertex v to MAXIMISE   sum_i ( dist(i, v) * a[i] ).
    Print that maximum value.

    APPROACH  —  Rerooting DP (two DFS passes)
    -----------------------------------------
    Root the tree at vertex 1.

    PASS 1 (precalc, downward DFS):
        subtreeSum[u] = sum of a[i] over u's subtree.
        dist[u]       = sum over u's subtree of (distance from u) * a[i].
        For the ROOT, dist[root] already equals the full answer for v = root,
        because its subtree is the whole tree.

        Recurrence: when u pulls child x, every node in x's subtree is 1 edge
        farther from u than from x, so
            dist[u] += dist[x] + subtreeSum[x].

    PASS 2 (reroot, downward DFS):
        Now dist[u] holds the FULL answer for v = u. To move the root from u
        to its child x:
          * nodes in x's subtree get 1 edge CLOSER  -> subtract subtreeSum[x]
          * all other nodes get 1 edge FARTHER      -> add (totalSum - subtreeSum[x])
        Hence
            dist[x] = dist[u] - subtreeSum[x] + (totalSum - subtreeSum[x])
        where totalSum = sum of all a[i] (constant).

    This O(1) formula replaces the given code's "modify-then-revert" block,
    which manually added/removed subtree pieces. The formula is equivalent but
    far clearer: subtreeSum never changes, we just propagate dist downward.

    COMPLEXITY: O(n) time, O(n) space.
*/

#include <bits/stdc++.h>
using namespace std;

int n;
vector<long long> a;            // a[i] = value on vertex i (1-indexed)
vector<vector<int>> g;          // adjacency list
vector<long long> subtreeSum;   // sum of a over subtree (fixed after pass 1)
vector<long long> dist;         // dist[v] = full weighted-distance sum for root v
long long totalSum = 0;
long long best = LLONG_MIN;

// Pass 1: compute subtreeSum[] and dist[] for the rooted tree (root = 1).
void precalc(int u, int parent) {
    subtreeSum[u] = a[u];
    dist[u] = 0;                // distance from u to itself is 0
    for (int x : g[u]) {
        if (x == parent) continue;
        precalc(x, u);
        subtreeSum[u] += subtreeSum[x];
        dist[u] += dist[x] + subtreeSum[x];   // +1 edge for every node in x's subtree
    }
}

// Pass 2: reroot. dist[u] is already the full answer for v = u.
void reroot(int u, int parent) {
    best = max(best, dist[u]);
    for (int x : g[u]) {
        if (x == parent) continue;
        long long saved = dist[x];
        // shift root u -> x: x's subtree gets closer, the rest gets farther
        dist[x] = dist[u] - subtreeSum[x] + (totalSum - subtreeSum[x]);
        reroot(x, u);
        dist[x] = saved;        // restore (keeps dist[] clean; not strictly required)
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    a.assign(n + 1, 0);
    g.assign(n + 1, {});
    subtreeSum.assign(n + 1, 0);
    dist.assign(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        totalSum += a[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    precalc(1, -1);
    reroot(1, -1);      // propagate to every other vertex, track the max

    cout << best << "\n";
    return 0;
}
