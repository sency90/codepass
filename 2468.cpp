#include <cstdio>
using namespace std;
typedef unsigned long long ull;
const int NA = -1;
int main() {
	ull x; scanf("%llu", &x);
	ull last_bit = x&-x;
	int l=NA,r=NA;
	for(int i=0; i<64; i++) {
		if((last_bit>>i)&1ULL) {
			r=i;
			break;
		}
	}
	if(r==NA) {
		puts("0 0");
		return 0;
	}

	l=r;
	for(int i=r+1; i<64; i++) {
		if(r>=0 && (x>>i)&1ULL) {
			l=i;
		}
		else break;
	}

	ull big=0;
	if(l<63) {
		big = x;
		for(int i=r; i<=l; i++) {
			big ^= (1ULL<<i);
		}
		big |= (1ULL<<(l+1));
		for(int i=0; i<l-r; i++) {
			big |= (1ULL<<i);
		}
	}

	if(r!=0) {
		ull sml = (x^last_bit) | (1ULL<<(r-1));
		printf("%llu %llu\n", sml, big);
		return 0;
	}

	int pr=r, pl=l;

	for(int i=l+1; i<64; i++) {
		if((x>>i)&1) {
			r=i;
			break;
		}
	}

	ull sml = 0;
	//printf("[2] l:%d, r:%d\n", l,r);
	if(l<r) {
		sml = x^(1ULL<<r) | (1ULL<<(r-1)); //pl-pr+1개만큼 그 아래 bit들을 켜준다.
		for(int i=pr; i<=pl; i++) {
			sml ^= (1ULL<<i);
		}
		for(int i=r-2, j=0; j<pl-pr+1; i--, j++) {
			sml |= (1ULL<<i);
		}
	}
	printf("%llu %llu\n", sml, big);
	return 0;
}
