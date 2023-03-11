#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
dp[i] : (3進数で) 今の各人の状態を表す
状態 0 ... まだ参加するか聞かれてない
状態 1 ... 参加した
状態 2 ... 参加しない

もらう dp を行う.
dp[i] で状態 1, 2 の各人 j について, dp[i] から人 j が状態 0 になったものから人 j が選ばれたとする.
人 j の状態は すでに選ばれた人に仲が悪い人がいるかどうかで決まる.
bit演算による高速化を行えば, O(N * 3^N) でok.
*/

int main(){
	int n, m; cin >> n >> m;
	vector<int> v(n); // 仲が悪いもののリスト (bit)
	for (int i=0; i<m; i++){
		int a, b; cin >> a >> b;
		a--; b--;
		v[a] ^= 1 << b;
		v[b] ^= 1 << a;
	}

	// 3 のべきを準備
	int siz = 1;
	vector<int> beki_3(n + 1, 1);
	for (int i=0; i<n; i++){
		siz *= 3;
		beki_3[i+1] = siz;
	}
	
	// DP をする
	vector<ll> dp(siz);
	dp[0] = 1;
	for (int i=0; i<siz; i++){
		int x = 0; // 参加者リスト (bit)
		int t = i;
		for (int j=0; j<n; j++){
			int p = t % 3;
			t /= 3;
			if (p == 1) x ^= 1 << j;
		}
		t = i;
		for (int j=0; j<n; j++){
			int p = t % 3;
			t /= 3;
			if (p > 0){
				if ((x & v[j]) == 0 && p == 1){
					dp[i] += dp[i - beki_3[j]];
				}
				if ((x & v[j]) != 0 && p == 2){
					dp[i] += dp[i - 2 * beki_3[j]];
				}
			}
		}
	}

	// 参加者数ごとに集計 
	vector<ll> ans(n+1);
	for (int i=0; i<siz; i++){
		int cnt = 0;
		bool mode = true;
		int t = i;
		for (int j=0; j<n; j++){
			int p = t % 3;
			t /= 3;
			if (p == 1) cnt++;
			if (p == 0){
				mode = false;
				break;
			}
		}
		if (dp[i] > 0 && mode){
			ans[cnt] += dp[i];
		}
	}

	// 答えを出力
	int ans1 = 0;
	ll ans2 = 0;
	for (int i=0; i<n+1; i++){
		if (ans[i] > 0){
			ans1 = i;
			ans2 = ans[i];
		}
	}

	cout << ans1 << " " << ans2 << endl;
}
