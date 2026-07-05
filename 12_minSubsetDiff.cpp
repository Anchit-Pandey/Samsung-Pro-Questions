#include <bits/stdc++.h> 
using namespace std;

int main() {
    int t;
    cin>>t;
    for(int test = 1; test <= t; test++) {
        int n;
        cin>>n;
        vector<int> arr(n);
        for(int i = 0; i < n; i++)
        cin>>arr[i];
        bitset<10001> dp;
        dp[0] = 1;
        int sum = 0;
        for(int i = 0; i < n; i++) {
            dp |= (dp << arr[i]);
            sum += arr[i];
        }
        for(int i = sum/2; i >= 0; i--) {
            if(dp[i]) {
                cout<<"#"<<test<<" "<<sum - 2*i<<'\n';
                break;
            }
        }
    }
    return 0;
}