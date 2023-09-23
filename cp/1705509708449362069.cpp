#include<bits/stdc++.h>
using namespace std;
#include<atcoder/modint>
typedef atcoder::modint1000000007 mint;
int main(){
	int n; cin >> n;
	vector<mint> dp(n+1), pow2(n+1);
	vector<bool> sieve(n+1, true);
	pow2[0] = 1;
	for (int i=1; i<=n; i++){
		pow2[i] = pow2[i-1] * 2;
	}
	for (int i=1; i<=n; i++){
		dp[i] = pow2[n/i] - n/i - 1;
	}
	for (int p=2; p<=n; p++){
		if (sieve[p]){
			for (int k=1; k<=n/p; k++){
				sieve[k*p] = false;
				dp[k] -= dp[k*p];
			}
		}
	}
	cout << dp[1].val() << '\n';
}