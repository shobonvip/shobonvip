import pyperclip

A = """#include<bits/stdc++.h>
#include<atcoder/all>
using namespace std;
using namespace atcoder;

typedef modint998244353 mint;
typedef long long ll;

int main(){
	$0
}
"""

name = "tenpure"
arep = A.replace('\n','\\n').replace('\t','\\t')

pyperclip.copy(f'"{name}": {{\n\t"prefix": "{name}",\n\t"body": [\n\t\t"{arep}"\n\t]\n}},')