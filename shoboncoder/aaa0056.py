# 計算量 O((log N)^4)

# --- 想定解 ---
# popcount(i) = m となる k を固定し,
# i が m の倍数であることと popcount(i) = m であることを
# ともに満たすものを数え上げる.
# dp[i][j][k]: 上から2進表記で i 桁目まで見たとき,
# ビット 1 が立っている数の個数が j,
# m で割ったあまりが k である.
# として, いわゆる桁DPを O(log N) 回だけ行う.
# DPは O((log N)^3) なので, 結局 O((log N)^4) となる.

def calc(n, m):
	dp = [[0] * m for i in range(m+1)]
	v = list(map(int,bin(n)[2:]))
	size = len(v)
	now_popcount = 0
	now_modulo = 0
	for i in range(size):
		ndp = [[0] * m for i in range(m+1)]
		
		for j in range(m):
			for k in range(m):
				ndp[j+1][(2*k+1)%m] += dp[j][k]
		for j in range(m+1):
			for k in range(m):
				ndp[j][(2*k)%m] += dp[j][k]
		
		if i > 0:
			ndp[1][1%m] += 1
		
		if i > 0 and v[i] == 1 and now_popcount <= m:
			ndp[now_popcount][(2*now_modulo)%m] += 1
		
		if v[i] == 1:
			now_popcount += 1
		now_modulo = (2*now_modulo+v[i])%m
		
		dp = ndp
	
	if now_popcount <= m:
		dp[now_popcount][now_modulo] += 1
	
	return dp[m][0]

n = int(input())
ans = 0
for m in range(1, 60):
	ans += calc(n, m)
print(ans)