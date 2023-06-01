#include <stdio.h>
int vx[10001], vy[10001], tmp[10001];
inline int abs(int x) { return x<0?-x:x; }
void msort(int *v, int s, int e) {
	if(s+1>=e) return;
	int m = (s+e)>>1;
	msort(v, s, m); msort(v, m, e);

	int i=s, j=m, k=s;
	while(i<m && j<e) {
		if(v[i]<v[j]) tmp[k++]=v[i++];
		else tmp[k++] = v[j++];
	}
	while(i<m) { tmp[k++] = v[i++]; }
	while(j<e) { tmp[k++] = v[j++]; }

	for(i=s; i<e; i++) v[i] = tmp[i];
}
int main() {
    int n, m;
    scanf("%d%d", &n,&m);
    for(int i=0; i<m; i++) {
        scanf("%d%d",&vx[i],&vy[i]);
    }
	msort(vx, 0, m);
	msort(vy, 0, m);

    int ans = 0, M=m>>1;
    for(int i=0; i<m; i++) {
        ans += abs(vx[i]-vx[M]);
        ans += abs(vy[i]-vy[M]);
    }

    printf("%d\n", ans);

    return 0;
}
