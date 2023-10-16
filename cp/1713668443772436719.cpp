#include<bits/stdc++.h>
using namespace std;
int main(){
	int n; cin >> n;
	vector<int> p(n);
	for (int i=0; i<n; i++){
		cin >> p[i];
		p[i]--;
	}

	set<int> r;
	for (int i=0; i<n; i++){
		r.insert(i);
	}

	vector<int> q(n);
	for (int i=0; i<n-1; i++){
		auto itr = r.begin();
		if (p[i] == (*itr)){
			itr++;
		}
		q[i] = (*itr);
		r.erase(itr);
	}

	q[n-1] = *r.begin();
	if (q[n-1] == p[n-1]){
		swap(q[n-1], q[n-2]);
	}

	for (int i=0; i<n; i++){
		cout << q[i]+1 << ' ';
	}
	cout << '\n';
}