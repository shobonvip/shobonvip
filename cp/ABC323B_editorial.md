各プレイヤーの勝ち数として取りうる値は $0$ 以上 $N-1$ 以下の $N$ 個の整数です。そこで、各整数についてバケツを用意することを考えます。

各プレイヤーは、勝ち数のバケツにプレイヤー番号を入れます。全プレイヤーが番号を入れ終わったあと、$i=N-1, N-2, \cdots, 0$ の順に、$i$ のバケツに含まれる番号を小さい順に出力すればよいです。

このようにしてソートする方法は**バケットソート**と呼ばれます。この問題の場合、時間・空間計算量はともに $O(N)$ です。

実装例(C++)
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	// 入力を受け取る
	int n;
	cin >> n;

	vector<string> c(n);
	for (int i=0; i<n; i++){
		cin >> c[i];
	}

	// 各人についての勝ち数を求める
	vector<int> wins(n);
	for (int i=0; i<n; i++){
		for (int j=0; j<n; j++){
			if (c[i][j] == 'o'){
				wins[i] += 1;
			}
		}
	}

	// 勝ち数は, 0 以上 n-1 以下の整数しか取りえない
	// bucket[i] は勝ち数 i の番号をすべて入れる
	vector bucket(n, vector<int>(0));
	for (int i=0; i<n; i++){
		bucket[wins[i]].push_back(i);
	}

	// さきほど, 番号の小さい順に bucket に入れたので,
	// bucket[i] の中身は, すでに番号の小さい順になっている.
	// 勝ち数の多い方から, bucket[i] の中身を出力していけばよい
	for (int i=n-1; i>=0; i--){
		for (int j: bucket[i]){
			cout << j+1 << ' ';
		}
	}
	cout << '\n';
}
```

実装例(Python)
```python
# 入力を受け取る
n = int(input())
s = [input() for i in range(n)]

# 各人についての勝ち数を求める
wins = [0] * n
for i in range(n):
	for j in range(n):
		if s[i][j] == 'o':
			wins[i] += 1

# 勝ち数は, 0 以上 n-1 以下の整数しか取りえない
# bucket[i] は勝ち数 i の番号をすべて入れる
bucket = [[] for i in range(n)]
for i in range(n):
	bucket[wins[i]].append(i)

# さきほど, 番号の小さい順に bucket に入れたので,
# bucket[i] の中身は, すでに番号の小さい順になっている.
# 勝ち数の多い方から, bucket[i] の中身を答え ans に追加する
ans = []
for i in range(n-1,-1,-1):
	for j in bucket[i]:
		ans.append(j+1)

# 答えを出力
print(*ans)
```