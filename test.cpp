#include <cstdio>
#include <cstring>
using namespace std;
int fs[3][3], houseInfo[3][3];
int m[7][7];
int cx=3, cy=4;
void DrawMap(int (*fs)[3], int cdir) {
	switch(cdir) {
		case 0:
			for(int i=0,u=cx-1; i<=2; i++,u++) {
				for(int j=0,v=cy-1; j<=2; j++,v++) {
					m[u][v] = fs[i][j];
				}
			}
			break;
		case 1:
			for(int i=0,v=cy-1; i<3; i++,v++) {
				for(int j=0,u=cx+1; j<3; j++,u--) {
					m[u][v] = fs[i][j];
				}
			}
			break;
		case 2:
			for(int i=0,u=cx+1; i<3; i++,u--) {
				for(int j=0,v=cy+1; j<3; j++,v--) {
					m[u][v] = fs[i][j];
				}
			}
			break;
		case 3:
			for(int i=0,v=cy+1; i<3; i++,v--) {
				for(int j=0,u=cx-1; j<3; j++,u++) {
					m[u][v] = fs[i][j];
				}
			}
			break;
	}
}
int main() {
	int cnt=0;
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			houseInfo[i][j] = ++cnt;
		}
	}
	int rx=1, ry=1;
	for(int dir=0; dir<4; dir++) {
		switch (dir)
		{
			case 0: // UP
				for (int y = rx - 1, sy = 0; y <= rx + 1; ++y, ++sy)
					for (int x = ry - 1, sx = 0; x <= ry + 1; ++x, ++sx)
						fs[sy][sx] = houseInfo[y][x];
				break;
			case 1: // LEFT
				for (int y = rx - 1, sx = 2; y <= rx + 1; ++y, --sx)
					for (int x = ry - 1, sy = 0; x <= ry + 1; ++x, ++sy)
						fs[sy][sx] = houseInfo[y][x];
				break;
			case 2: // DOWN
				for (int y = rx - 1, sy = 2; y <= rx + 1; ++y, --sy)
					for (int x = ry - 1, sx = 2; x <= ry + 1; ++x, --sx)
						fs[sy][sx] = houseInfo[y][x];
				break;
			case 3: // RIGHT
				for (int y = rx - 1, sx = 0; y <= rx + 1; ++y, ++sx)
					for (int x = ry - 1, sy = 2; x <= ry + 1; ++x, --sy)
						fs[sy][sx] = houseInfo[y][x];
				break;
		}

		memset(m, -1, sizeof(m));
		DrawMap(fs, dir);

		for(int i=cx-1; i<=cx+1; i++) {
			for(int j=cy-1; j<=cy+1; j++) {
				printf("%d ", m[i][j]);
			}
			puts("");
		}
		puts("");
	}

	return 0;
}
