// https://x.com/shobonvip/status/1797467567692644676
// の実装. ほとんど出力が律速.
// 空間計算量・時間計算量ともに O(N 2^N).
// 出力しない場合 n=24 で 1sec 前後で動く.

#include<bits/stdc++.h>
using namespace std;

int main() {
	// 入出力高速化
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n; cin >> n;
	vector<bool> seen(1 << n); // もう見たか?
	vector<bool> valid(1 << n); // この状態から完成まで持っていけるか?
	
	// この状態から完成に持っていくために見るべき次の要素は何か?
	vector<vector<int>> a(1 << n, vector<int>(0));

	vector<int> b; // 現在作り上げている順列
	int piv = 1 << n; // 残り順列数
	vector<vector<int>> ans; // 答え

	auto dfs = [&](auto self, int i) -> bool {
		// 完成!
		if (i == (1<<n)-1) {
			ans.push_back(b);
			piv--;
			return true;
		}

		if (seen[i]) {
			// もし完成できないなら return false;
			if (!valid[i]) return false;

			for (int j: a[i]){ // a[i] ... ここから完成可能な次の要素の集合
				if (piv == 0) break;
				b.push_back(j);
				self(self, i|(1<<j));
				b.pop_back();
			}	
			return true;
		}

		for (int j=0; j<n; j++){
			if (piv == 0) break;
			if (i >> j & 1) continue; // もう使用していた場合
			if (__builtin_popcount(i) == j) continue; // 完全順列でない

			b.push_back(j);
			if(self(self, i|(1<<j))){ // ここから完成可能な場合
				a[i].push_back(j);
			}
			b.pop_back();
		}
		seen[i] = 1;
		valid[i] = !a[i].empty(); // ここから完成可能な場合, valid[i] = true
		return valid[i];
	};

	dfs(dfs, 0);

	// 答えの出力
	if (ans.size() < (1<<n)){
		cout << "-1\n";
	}else{
		for (int i=0; i<1<<n; i++){
			for (int j=0; j<n; j++){
				cout << ans[i][j] + 1 << ' ';
			}
			cout << '\n';
		}
	}

}