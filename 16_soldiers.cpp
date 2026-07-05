/*
    PROBLEM
    -------
    A tree represents military units. Each node holds some soldiers.
    "Balance" the tree so that every group of siblings (nodes sharing the
    same parent) ends up with the SAME subtree sum.

    Rules:
      * We may ONLY delete (remove) soldiers from nodes — never add.
      * Remove the minimum total number of soldiers.
      * Return the total number of soldiers remaining AFTER balancing.

    WHY THE GREEDY WORKS (target = min of sibling sums)
    ---------------------------------------------------
    At a node u, its children already have balanced subtree sums (computed
    bottom-up). To make the siblings equal we must bring them all down to one
    common value T. Because we can only decrease, T <= every child sum, so the
    largest legal T is min(child sums). Cost = sum(child sums) - k*T, which is
    MINIMISED when T is as large as possible, i.e. T = min(child sums).

    Could picking a SMALLER T ever help an ancestor? No:
      * It costs more locally (extra removal d).
      * It only shrinks this subtree's sum, which can never reduce an
        ancestor's removal by more than d (and may increase it if this node
        was the ancestor's minimum). Net effect is never negative.
    => target = min(child sums) is globally optimal.

    The given code tried EVERY child sum as a target in an O(k^2) loop, but
    only min(child sums) can ever be feasible (every larger target hits a child
    that "can't be increased"), so that loop is redundant. We replace it with a
    single O(k) min + sum pass.
*/

#include<bits/stdc++.h>
using namespace std;

int n;
vector<int> soldiers;
vector<vector<int>> children;
int totalRemoved;

int dfs(int node) {
    if(children[node].empty()) {
        return soldiers[node];
    }
    int childSum = 0;
    int minChild = INT_MAX;
    for(int child : children[node]) {
        int childValue = dfs(child);
        childSum += childValue;
        minChild = min(minChild, childValue);
    }
    int k = children[node].size();
    int remaining = minChild * k;
    int removed = childSum - remaining;
    totalRemoved += removed;
    return soldiers[node] + remaining;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    for(int test = 1; test <= t; test++) {
        cin >> n;
        int root = -1;
        totalRemoved = 0;
        soldiers.assign(n, 0);
        children.assign(n, {});
        for(int i = 0; i < n; i++) {
            int p, s;
            cin >> p >> s;
            soldiers[i] = s;
            if(p == -1) {
                root = i;
            } else {
                children[p].push_back(i);
            }
        }
        int finalSum = dfs(root);
        cout << "Case #" << test << ": " << finalSum << "\n";
    }
    return 0;
}