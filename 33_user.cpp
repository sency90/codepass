/// ***** user.cpp *****
extern void scan(int floorState[3][3]);
extern int move(void);
extern void turn(int mCommand);

int cx,cy,cdir;
int fs[3][3];
int m[130][130]; //Map
int dx[4] = {-1,0,1,0};
int dy[4] = {0,-1,0,1};

void init(void) {
	cx=cy=64; cdir=0;
}
bool HasBeen() {
	for(int i=-1; i<=1; i++) {
		for(int j=-1; j<=1; j++) {
			if(m[cx+i][cy+j]<0) return false;
		}
	}
	return true;
}
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

void cleanHouse(void) {
	for(int i=0; i<130; i++) {
		for(int j=0; j<130; j++) {
			m[i][j] = -1;
		}
	}

	while(true) {
		if(!HasBeen()) {
			scan(fs);
			DrawMap(fs);
		}

		for(int i=0; i<4; i++) {
			int ndir = (cdir+i)%4;
			int nx=cx+dx[ndir], ny=cy+dy[ndir];
			if(m[nx][ny] == 0) {
				m[nx][ny] = 2;
			}
		}
	}
}
