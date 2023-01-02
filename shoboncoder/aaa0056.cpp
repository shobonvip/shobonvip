/*
計算量 O((log N)^4)

--- 想定解 ---
popcount(i) = m となる k を固定し,
i が m の倍数であることと popcount(i) = m であることを
ともに満たすものを数え上げる.
- dp[i][j][k]: 上から2進表記で i 桁目まで見たとき,
  ビット 1 が立っている数の個数が j,
  m で割ったあまりが k である.
として, いわゆる桁DPを O(log N) 回だけ行う.
DPは O((log N)^3) なので, 結局 O((log N)^4) となる.
*/

#include <bits/stdc++.h>
using namespace std;

long long calc(long long n, int m){
	vector<vector<long long>> dp(m+1, vector<long long>(m));
	vector<int> v(0);
	while (n > 0){
		v.push_back(n % 2);
		n /= 2;
	}
	reverse(v.begin(), v.end());
	int size = v.size();
	int now_popcount = 0;
	int now_modulo = 0;
	for (int i=0; i<size; i++){
		vector<vector<long long>> ndp(m+1, vector<long long>(m));
		for (int j=0; j<m; j++){
			for (int k=0; k<m; k++){
				ndp[j+1][(2*k+1)%m] += dp[j][k];
			}
		}
		for (int j=0; j<m+1; j++){
			for (int k=0; k<m; k++){
				ndp[j][(2*k)%m] += dp[j][k];
			}
		}
		if (i > 0) ndp[1][1%m] += 1;
		if (i > 0 && v[i] == 1 && now_popcount <= m){
			ndp[now_popcount][(2*now_modulo)%m] += 1;
		}
		if (v[i] == 1) now_popcount += 1;
		now_modulo = (2*now_modulo+v[i])%m;
		dp = ndp;
	}
	if (now_popcount <= m) dp[now_popcount][now_modulo] += 1;
	return dp[m][0];
}

int main(){
	long long n;
	cin >> n;
	long long ans = 0;
	for (int m=1; m<60; m++){
		ans += calc(n, m);
	}
	cout << ans << endl;
}