# dp[i] : (3進数で) 今の各人の状態を表す
# 状態 0 ... まだ参加するか聞かれてない
# 状態 1 ... 参加した
# 状態 2 ... 参加しない

# もらう dp を行う.
# dp[i] で状態 1, 2 の各人 j について, dp[i] から人 j が状態 0 になったものから人 j が選ばれたとする.
# 人 j の状態は すでに選ばれた人に仲が悪い人がいるかどうかで決まる.
# bit演算による高速化を行えば, O(N * 3^N) でok.


n, m = map(int,input().split())
v = [0] * n # 仲が悪いもののリスト (bit)

for i in range(m):
	a, b = map(int,input().split())
	a -= 1
	b -= 1
	v[a] ^= 1 << b
	v[b] ^= 1 << a

# DP をする
dp = [0] * 3 ** n
dp[0] = 1
for i in range(3 ** n):
	x = 0 # 参加者リスト (bit)
	t = i
	for j in range(n):
		p = t % 3
		t //= 3
		if p == 1:
			x ^= 1 << j
	t = i
	for j in range(n):
		p = t % 3
		t //= 3
		if p > 0:
			if x & v[j] == 0 and p == 1:
				dp[i] += dp[i - 3 ** j]
			if x & v[j] != 0 and p == 2:
				dp[i] += dp[i - 2 * 3 ** j]
	
# 参加者数ごとに集計
ans = [0] * (n+1)

for i in range(3 ** n):
	cnt = 0
	mode = 1
	t = i
	for j in range(n):
		p = t % 3
		t //= 3
		if p == 1:
			cnt += 1
		if p == 0:
			mode = 0
			break

	if dp[i] > 0 and mode:
		ans[cnt] += dp[i]

# 答えを出力
ans1 = 0
ans2 = 0	

for i in range(n + 1):
	if ans[i] > 0:
		ans1 = i
		ans2 = ans[i]

print(ans1, ans2)