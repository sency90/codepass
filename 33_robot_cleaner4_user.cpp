/// ***** user.cpp *****
extern void scan(int floorState[3][3]);
extern int move(void);
extern void turn(int mCommand);

int M;
int fs[3][3];
int m[131][131];
void init(void) {
	for(int i=0; i<131; i++) {
		for(int j=0; j<131; j++) {
			m[i][j] = -1;
		}
	}
}

bool has_been(int rx, int ry, int dir) {
	for(int dir=0; dir<4; dir++) {
		switch(dir) {
			case 0:
				for(int i=rx-1; i<=rx+1; i++) {
					for(int j=ry-1; j<=ry+1; j++) {
						if(m[i][j]<0) return false;
					}
				}
				break;
			case 1:
				for(int i=ry-1; i<=ry+1; i++) {
					for(int j=rx+1; j>=rx-1; j--) {
						if(m[j][i]<0) return false;
					}
				}
				break;
			case 2:
				for(int i=rx+1; i>=rx-1; i--) {
					for(int j=ry+1; j>=ry-1; j--) {
						if(m[i][j]<0) return false;
					}
				}
				break;
			case 3:
				for(int i=ry+1; i>=ry-1; i--) {
					for(int j=rx-1; j<=rx+1; j++) {
						if(m[j][i]>0) return false;
					}
				}
				break;
			default:
				break;
		}
	}
	return true;
}

int next_x(int dir) {
	
}


void cleanHouse(void)
{
	int rx=64, ry=64, rdir=0;

	while(true) {
		if(!has_been(rx,ry,rdir)) {
			scan(fs);
		}

		int nx = next_x(rdir), ny = next_y(rdir);
	}


}
