#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ull = unsigned long long;
vector<bool> v,u;
int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	ull x; cin >> x;

	if(x==0ULL) v.push_back(false);
	while(x) {
		if(x&1) v.push_back(true);
		else v.push_back(false);
		x>>=1;
	}
	v.push_back(false);
	reverse(v.begin(), v.end());

	
	u = v;
	ull sml=0, big=0;
	if(prev_permutation(u.begin(), u.end())) {
		reverse(u.begin(), u.end());
		for(int i=0; i<(int)u.size(); i++) {
			if(u[i]) sml |= (1ULL<<i);
		}
	}
	if(next_permutation(v.begin(), v.end())) {
		reverse(v.begin(), v.end());
		for(int i=0; i<(int)v.size(); i++) {
			if(v[i]) big |= (1ULL<<i);
		}
	}
	printf("%llu %llu\n", sml, big);
	return 0;
}
