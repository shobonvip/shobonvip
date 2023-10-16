import heapq
n = int(input())
p = list(map(int,input().split()))
q = [0] * n
r = [i+1 for i in range(n)]
heapq.heapify(r)

for i in range(n-1):
	x = heapq.heappop(r)
	if x == p[i]:
		y = heapq.heappop(r)
		heapq.heappush(r, x)
		x = y
	q[i] = x

q[n-1] = heapq.heappop(r)

if q[n-1] == p[n-1]:
	q[n-2], q[n-1] = q[n-1], q[n-2]

print(*q)