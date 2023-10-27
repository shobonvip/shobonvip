// ‚±‚ÌÀ‘•‚Å‚Í‹——£‚ª inf ‚Ìê‡‚Ìˆ—‚ğ–³‹‚µ‚Ä‚¢‚é‚ª, ‘½•ª‘åä•v‚¾‚Æv‚¤

#include<bits/stdc++.h>
using namespace std;
#include<atcoder/modint>
typedef atcoder::modint998244353 mint;
typedef long long ll;
const ll inf = 3e18;

vector<ll> dijkstra(int n, vector<vector<pair<int,ll>>> &edge, int st){
	vector<ll> d(n, inf);
	d[st] = 0;
	priority_queue<pair<ll,int>> pq;
	pq.push(pair(0, st));
	while(!pq.empty()){
		auto [tmp, i] = pq.top();
		pq.pop();
		tmp = - tmp;
		if (tmp > d[i]) continue;
		for (auto [j, c]: edge[i]){
			ll targ = c + tmp;
			if (targ < d[j]){
				d[j] = targ;
				pq.push(pair(-d[j], j));
			}
		}
	}
	return d;
}

int main(){
	int n, m; cin >> n >> m;
	vector<vector<pair<int,ll>>> edge1(n, vector<pair<int,ll>>(0));
	vector<vector<pair<int,ll>>> edge2(n, vector<pair<int,ll>>(0));
	for (int i=0; i<m; i++){
		int a, b; cin >> a >> b;
		ll c; cin >> c;
		a--; b--;
		edge1[a].push_back(pair(b, c));
		edge2[b].push_back(pair(a, c));
	}
	vector<ll> a = dijkstra(n, edge1, 0);
	vector<ll> b = dijkstra(n, edge2, n-1);
	ll c = a[n-1];
	sort(b.begin(), b.end());
	vector<mint> rui(n+1);
	for (int i=0; i<n; i++){
		rui[i+1] = rui[i] + b[i];
	}

	mint ans = 0;
	for (int i=0; i<n; i++){
		ll x = c - a[i];
		int z = lower_bound(b.begin(), b.end(), x) - b.begin();
		ans += mint(z) * x - rui[z];
	}
	cout << ans.val() << '\n';
}