#include<bits/stdc++.h>
using namespace std;
#include<atcoder/modint>
typedef atcoder::modint1000000007 mint;
int main(){
	int n; cin >> n;
	vector<mint> dp(n+1);
	for (int i=n; i>=1; i--){
		dp[i] = mint(2).pow(n/i) - n/i - 1;
		for (int j=2*i; j<=n; j+=i){
			dp[i] -= dp[j];
		}
	}
	cout << dp[1].val() << '\n';
}