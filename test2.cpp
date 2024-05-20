#include <cstdio>
#include <cstring>
using namespace std;
typedef unsigned int uint;
int fs[3][3];
int m[9][9];
uint seed = 31;
uint pseudo_rand() {
	return seed = (seed * 511) ^ seed;
}
int main() {
	int cnt=0;
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			fs[i][j] = ++cnt;
		}
	}

	int rx=3, ry=5;

	for(int rdir=0; rdir<4; rdir++) {
		int rx = pseudo_rand()%7+1, ry= pseudo_rand()%7+1;
		printf("(rx,ry) = (%d,%d)\n", rx,ry);
		memset(m, 0, sizeof(m));
		switch(rdir) {
			case 0:
				for(int i=0,u=rx-1; i<3; i++,u++) 
					for(int j=0,v=ry-1; j<3; j++,v++) 
						m[u][v] = fs[i][j];
				break;
			case 1:
				for(int i=0,v=ry-1; i<3; i++,v++) 
					for(int j=0,u=rx+1; j<3; j++,u--) 
						m[u][v] = fs[i][j];
				break;
			case 2:
				for(int i=0,u=rx+1; i<3; i++,u--) 
					for(int j=0,v=ry+1; j<3; j++,v--) 
						m[u][v] = fs[i][j];
				break;
			case 3:
				for(int i=0,v=ry+1; i<3; i++,v--) 
					for(int j=0,u=rx-1; j<3; j++,u++) 
						m[u][v] = fs[i][j];
				break;
		}

		for(int i=0; i<9; i++) {
			for(int j=0; j<9; j++) {
				if(m[i][j]==0) printf(".");
				else printf("%d",m[i][j]);
			}
			puts("");
		}
		puts("");
	}
	return 0;
}
