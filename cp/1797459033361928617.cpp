// https://x.com/shobonvip/status/1797467567692644676
// �̎���. �قƂ�Ǐo�͂�����.
// ��Ԍv�Z�ʁE���Ԍv�Z�ʂƂ��� O(N 2^N).
// �o�͂��Ȃ��ꍇ n=24 �� 1sec �O��œ���.

#include<bits/stdc++.h>
using namespace std;

int main() {
	// ���o�͍�����
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n; cin >> n;
	vector<bool> seen(1 << n); // ����������?
	vector<bool> valid(1 << n); // ���̏�Ԃ��犮���܂Ŏ����Ă����邩?
	
	// ���̏�Ԃ��犮���Ɏ����Ă������߂Ɍ���ׂ����̗v�f�͉���?
	vector<vector<int>> a(1 << n, vector<int>(0));

	vector<int> b; // ���ݍ��グ�Ă��鏇��
	int piv = 1 << n; // �c�菇��
	vector<vector<int>> ans; // ����

	auto dfs = [&](auto self, int i) -> bool {
		// ����!
		if (i == (1<<n)-1) {
			ans.push_back(b);
			piv--;
			return true;
		}

		if (seen[i]) {
			// ���������ł��Ȃ��Ȃ� return false;
			if (!valid[i]) return false;

			for (int j: a[i]){ // a[i] ... �������犮���\�Ȏ��̗v�f�̏W��
				if (piv == 0) break;
				b.push_back(j);
				self(self, i|(1<<j));
				b.pop_back();
			}	
			return true;
		}

		for (int j=0; j<n; j++){
			if (piv == 0) break;
			if (i >> j & 1) continue; // �����g�p���Ă����ꍇ
			if (__builtin_popcount(i) == j) continue; // ���S����łȂ�

			b.push_back(j);
			if(self(self, i|(1<<j))){ // �������犮���\�ȏꍇ
				a[i].push_back(j);
			}
			b.pop_back();
		}
		seen[i] = 1;
		valid[i] = !a[i].empty(); // �������犮���\�ȏꍇ, valid[i] = true
		return valid[i];
	};

	dfs(dfs, 0);

	// �����̏o��
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