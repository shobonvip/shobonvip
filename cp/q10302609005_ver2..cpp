#include<bits/stdc++.h>
using namespace std;

const int sum_target = 2080 / 2;
const int square_target = 89440 / 2;

int main(){

	random_device seed_gen;
	mt19937 engine(seed_gen());
	uniform_int_distribution<int> dist(0, 1);

	vector seen(64, vector(square_target+1, vector<bool>(sum_target+1)));
	vector pos_use(64, vector(square_target+1, vector<bool>(sum_target+1)));
	vector pos_nouse(64, vector(square_target+1, vector<bool>(sum_target+1)));
	vector<int> now_data(64, -1);
	int now_sum = 0;
	int cnt = 0;

	auto output = [&](vector<int> &a) -> void {
		for (int i=0; i<8; i++){
			for (int j=0; j<8; j++){
				cout << a[i*8+j] << ' ';
			}
			cout << '\n';
		}
		return;
	};

	auto check = [&](vector<int> &a) -> bool {
		int sum_check = 0;
		int square_check = 0;
		for (int i=0; i<8; i++){
			for (int j=0; j<8; j++){
				sum_check += a[(7-j)*8+i] * (i*8+j+1);
				square_check += a[(7-j)*8+i] * (i*8+j+1) * (i*8+j+1);
			}
		}
		return sum_target == sum_check && square_target == square_check;
	};

	long long cnt_valid = 0;
	long long cnt_invalid = 0;
	int cnt_num = 0;

	auto dfs = [&](auto self, int ind, int left, int rem) -> bool {
		if (ind == 64){
			if (left == 0 && rem == 0){
				if (cnt_num == 32){
					if (!check(now_data)){
						cnt_invalid++;
						output(now_data);
						cout << endl;
					}else{
						cnt_valid++;
					}
				}
				return true;
			}
			return false;
		}

		if (seen[ind][left][rem]) {
			bool ret = false;

			if (dist(engine) == 1){
				if (pos_use[ind][left][rem]) {
					now_data[ind] = 1;
					cnt_num += 1;
					self(self, ind+1, left-(ind+1)*(ind+1), rem-(ind+1));
					now_data[ind] = -1;
					cnt_num -= 1;
					ret = true;
				}

				if (pos_nouse[ind][left][rem]){
					now_data[ind] = 0;
					self(self, ind+1, left, rem);
					now_data[ind] = -1;
					ret = true;
				}
			}else{
				if (pos_nouse[ind][left][rem]){
					now_data[ind] = 0;
					self(self, ind+1, left, rem);
					now_data[ind] = -1;
					ret = true;
				}
				if (pos_use[ind][left][rem]) {
					now_data[ind] = 1;
					cnt_num += 1;
					self(self, ind+1, left-(ind+1)*(ind+1), rem-(ind+1));
					now_data[ind] = -1;
					cnt_num -= 1;
					ret = true;
				}
			}

			return ret;
		}

		
		cnt += 1;
		if (cnt % 1000000 == 0) {
			cout << cnt << ' ' << ind << ' ' << left << ' ' << rem << ' ' << cnt_num << endl;
			cout << "  valid " << cnt_valid << endl;
			cout << "invalid " << cnt_invalid << endl;
		}
		

		if (dist(engine) == 0){
			if (left-(ind+1)*(ind+1) >= 0 && rem-(ind+1) >= 0){
				now_data[ind] = 1;
				cnt_num += 1;
				bool tmp = self(self, ind+1, left-(ind+1)*(ind+1), rem-(ind+1));
				now_data[ind] = -1;
				cnt_num -= 1;
				if (tmp) {
					pos_use[ind][left][rem] = true;
				}
			}

			{
				now_data[ind] = 0;
				bool tmp = self(self, ind+1, left, rem);
				now_data[ind] = -1;
				if (tmp) {
					pos_nouse[ind][left][rem] = true;
				}
			}
		}else{
			{
				now_data[ind] = 0;
				bool tmp = self(self, ind+1, left, rem);
				now_data[ind] = -1;
				if (tmp) {
					pos_nouse[ind][left][rem] = true;
				}
			}
			
			if (left-(ind+1)*(ind+1) >= 0 && rem-(ind+1) >= 0){
				now_data[ind] = 1;
				cnt_num += 1;
				bool tmp = self(self, ind+1, left-(ind+1)*(ind+1), rem-(ind+1));
				now_data[ind] = -1;
				cnt_num -= 1;
				if (tmp) {
					pos_use[ind][left][rem] = true;
				}
			}
		}

		seen[ind][left][rem] = 1;
		return pos_use[ind][left][rem] | pos_nouse[ind][left][rem];
	};

	dfs(dfs, 0, square_target, sum_target);

	cout << cnt_valid << endl;
	cout << cnt_invalid << endl;
}