#include <cstdio>
using namespace std;
int m[5][3] = {
	{ 0,0,0 },
	{ 1,2,3 },
	{ 4,5,6 },
	{ 7,8,9 },
	{ 0,0,0 }
};
int main() {
	int rx=2, ry=1;
	for(int dir=0; dir<4; dir++) {
		switch(dir) {
			case 0:
				for(int i=rx-1; i<=rx+1; i++) {
					for(int j=ry-1; j<=ry+1; j++) {
						printf("%d ", m[i][j]);
					}
					puts("");
				}
				puts("");
				break;
			case 1:
				for(int i=ry-1; i<=ry+1; i++) {
					for(int j=rx+1; j>=rx-1; j--) {
						printf("%d ", m[j][i]);
					}
					puts("");
				}
				puts("");
				break;
			case 2:
				for(int i=rx+1; i>=rx-1; i--) {
					for(int j=ry+1; j>=ry-1; j--) {
						printf("%d ", m[i][j]);
					}
					puts("");
				}
				puts("");
				break;
			case 3:
				for(int i=ry+1; i>=ry-1; i--) {
					for(int j=rx-1; j<=rx+1; j++) {
						printf("%d ", m[j][i]);
					}
					puts("");
				}
				puts("");
				break;
			default:
				break;
		}
	}
	return 0;
}
