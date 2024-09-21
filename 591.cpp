#include <cstdio>
using namespace std;
int d[51];
int f(int x) {
	if(x<=1) return x;
	else if(d[x]) return d[x];
	else return d[x] = f(x/2) + f(x-1);
}
int main() {
	int n; scanf("%d", &n);
	printf("%d\n", f(n));
	return 0;
}
