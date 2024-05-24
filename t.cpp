#include <cstdio>
using namespace std;

int m[3][3];
int rx,ry,rdir;

void DrawMap(int (*fs)[3]) {
	switch(rdir) {
		case 0:
			for(int i=0; i<3; i++) {
				for(int j=0; j<3; j++) {
					m[rx+i-1][ry+j-1] = fs[i][j];
				}
			}
			break;
		case 1:
			for(int j=0,u=0; j<3; j++,u++) {
				for(int i=2,v=0; i>=0; i--,v++) {
					m[rx+i-1][ry+j-1] = fs[u][v];
				}
			}
			break;
		case 2:
			for(int i=2,u=0; i>=0; i--,u++) {
				for(int j=2,v=0; j>=0; j--,v++) {
					m[rx+i-1][ry+j-1] = fs[u][v];
				}
			}
			break;
		case 3:
			for(int j=2,u=0; j>=0; j--,u++) {
				for(int i=0,v=0; i<3; i++,v++) {
					m[rx+i-1][ry+j-1] = fs[u][v];
				}
			}
			break;
		default:
			break;
	}

}

int fs[3][3];
int main() {
	int order=1;
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			fs[i][j] = order++;
		}
	}

	rx=ry=1;
	for(int k=0; k<4; k++) {
		rdir = k;
		DrawMap(fs);
		for(int i=0; i<3; i++) {
			for(int j=0; j<3; j++) {
				printf("%d ", m[i][j]);
			}
			puts("");
		}
		puts("");
	}

	return 0;
}
