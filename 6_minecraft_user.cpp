#include <cstdio>
using namespace std;
int v[501][501];
inline int min(int x, int y) {
    return x<y?x:y;
}
inline int max(int x, int y) {
    return x>y?x:y;
}

int main() {
    int n,m,b;
    scanf("%d%d%d",&n,&m,&b);
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            scanf("%d", &v[i][j]);
        }
    }

    const int inf = 0x3f3f3f3f;
    int mnTime=inf, memH=0;
    for(int h=0; h<=256; h++) {
        int Time = 0, B=b;
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                if(v[i][j] > h) {
                    Time += 2*(v[i][j]-h);
                    B += v[i][j]-h;
                }
                else {
                    Time += h-v[i][j];
                    B -= h-v[i][j];
                }
            }
        }
        if(B>=0) {
            if(mnTime > Time) {
                mnTime = Time;
                memH = h;
            }
            else if(mnTime == Time) {
                memH = max(memH, h);
            }
        }
    }

    printf("%d %d\n", mnTime, memH);

    return 0;
}
