#include <stdio.h>
struct Coord{
    int x, y;
    Coord() {}
    Coord(int x, int y):x(x), y(y) {}
};
Coord v[10001];
int vx[10001], vy[10001];
inline int abs(int x) {
    return x<0?-x:x;
}
int main() {
    int n, m;
    scanf("%d%d", &n,&m);
    for(int i=0; i<m; i++) {
        scanf("%d%d",&v[i].x,&v[i].y);
        vx[v[i].x]++;
        vy[v[i].y]++;
    }
    int midx, midy, M=(m+1)/2;
    for(int i=1; i<=10000; i++) {
        vx[i] += vx[i-1];
        if(vx[i] >= M) {
            midx = i;
            break;
        }
    }

    for(int i=1; i<=10000; i++) {
        vy[i] += vy[i-1];
        if(vy[i] >= M) {
            midy = i;
            break;
        }
    }

    int ans = 0;
    for(int i=0; i<m; i++) {
        ans += abs(v[i].x-midx);
        ans += abs(v[i].y-midy);
    }

    printf("%d\n", ans);

    return 0;
}
