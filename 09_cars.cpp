#include<bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin>>t;
    for(int test = 1; test <= t; test++) {
        int n, p, q, x, y;
        cin>>n>>p>>q;
        vector<int> dist(n);
        int maxDist = 0;
        for(int i = 0; i < n; i++) {
            cin>>x>>y;
            dist[i] = abs(x-p)+abs(y-q);
            maxDist = max(maxDist, dist[i]);
        }
        int parity = dist[0]%2;
        for(int i = 1; i < n; i++) {
            if(dist[i]%2 != parity) {
                cout<<"#"<<test<<" "<<-1<<'\n';
                return 0;
            }
        }
        int k = ceil((1LL*sqrt(1+8*maxDist)-1) / 2.0);
        maxDist = k*(k+1)/2;
        if(maxDist%2 == parity) {
            cout<<"#"<<test<<" "<<k<<'\n';
            return 0;
        }
        maxDist += (k+1);
        if(maxDist%2 == parity) {
            cout<<"#"<<test<<" "<<k+1<<'\n';
            return 0;
        }
        cout<<"#"<<test<<" "<<k+2<<'\n';
    }
    return 0;
}