#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
	int n; ll k;
	cin >> n;
	cin >> k;
	vector<ll> a(n);
	for (int i=0; i<n; i++) cin >> a[i];

	vector<vector<ll>> dp(1<<n, vector<ll>(0));
	for (int i=0; i<n; i++){
		dp[1<<i] = {a[i]};
	}

	for (int i=1; i<1<<n; i++){
		int fst = 0;
		for (int j=0; j<n; j++){
			if (i >> j & 1){
				fst = j;
				break;
			}
		}
		for (int j=i&(i-1); j>0; j=(j-1)&i){
			if (j >> fst & 1){
				for (ll &x: dp[j]){
					for (ll &y: dp[i^j]){
						dp[i].push_back(x+y);
						dp[i].push_back(abs(x-y));
						dp[i].push_back(x*y);
					}
				}
			}
		}
	}

	bool ans = false;
	for (ll &x: dp[(1<<n)-1]){
		if (x == k){
			ans = true;
			break;
		}
	}
	
	if (ans) cout << "Yes\n";
	else cout << "No\n";
}
