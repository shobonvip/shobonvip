/*
�v�Z�� O((log N)^4)

--- �z��� ---
popcount(i) = m �ƂȂ� k ���Œ肵,
i �� m �̔{���ł��邱�Ƃ� popcount(i) = m �ł��邱�Ƃ�
�Ƃ��ɖ��������̂𐔂��グ��.
- dp[i][j][k]: �ォ��2�i�\�L�� i ���ڂ܂Ō����Ƃ�,
  �r�b�g 1 �������Ă��鐔�̌��� j,
  m �Ŋ��������܂肪 k �ł���.
�Ƃ���, �����錅DP�� O(log N) �񂾂��s��.
DP�� O((log N)^3) �Ȃ̂�, ���� O((log N)^4) �ƂȂ�.
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