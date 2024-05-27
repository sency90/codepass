#include <cstdio>
#include <cstring>
using namespace std;

int m[5][5],cdir;
int fs[3][3];
int cx=3, cy=2;

void DrawMap(int (*fs)[3]) {
	switch(cdir) {
		case 0:
			for(int i=0; i<=2; i++) {
				for(int j=0; j<=2; j++) {
					m[cx+i-1][cy+j-1] = fs[i][j];
				}
			}
			break;
		case 1:
			for(int i=0,v=0; i<=2; i++,v++) {
				for(int j=0,u=2; j<=2; j++,u--) {
					m[cx+u-1][cy+v-1] = fs[i][j];
				}
			}
			break;
		case 2:
			for(int i=0,u=2; i<=2; i++,u--) {
				for(int j=0,v=2; j<=2; j++,v--) {
					m[cx+u-1][cy+v-1] = fs[i][j];
				}
			}
			break;
		case 3:
			for(int i=0,v=2; i<=2; i++,v--) {
				for(int j=0,u=0; j<=2; j++,u++) {
					m[cx+u-1][cy+v-1] = fs[i][j];
				}
			}
			break;
	}
}
void PrintM() {
	for(int i=0; i<5; i++) {
		for(int j=0; j<5; j++) {
			if(m[i][j] == 0) printf(".");
			else printf("%d", m[i][j]);
		}
		puts("");
	}
	puts("");
}
int main() {
	int cnt=0;
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			fs[i][j] = ++cnt;
		}
	}

	for(int dir=0; dir<4; dir++) {
		memset(m, 0, sizeof(m));
		cdir = dir;
		DrawMap(fs);
		PrintM();
	}

	return 0;
}
