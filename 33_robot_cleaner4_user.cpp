/// ***** user.cpp *****
extern void scan(int floorState[3][3]);
extern int move(void);
extern void turn(int mCommand);

int M;
int fs[3][3];
int m[131][131];
bool chk[131][131];
int dx[4] = {-1,0,1,0};
int dy[4] = {0,-1,0,1};
int dx2[4] = {1,-1,-1,1}; //right back
int dy2[4] = {1,1,-1,-1}; //right back

void init(void) {
	for(int i=0; i<131; i++) {
		for(int j=0; j<131; j++) {
			m[i][j] = -1;
			chk[i][j] = false;
		}
	}
}

bool has_been(int rx, int ry, int dir) {
	switch(dir) {
		case 0:
			for(int i=rx-1; i<=rx+1; i++) 
				for(int j=ry-1; j<=ry+1; j++) 
					if(m[i][j]<0) return false;
			break;
		case 1:
			for(int j=ry-1; j<=ry+1; j++) 
				for(int i=rx+1; i>=rx-1; i--) 
					if(m[i][j]<0) return false;
			break;
		case 2:
			for(int i=rx+1; i>=rx-1; i--) 
				for(int j=ry+1; j>=ry-1; j--) 
					if(m[i][j]<0) return false;
			break;
		case 3:
			for(int j=ry+1; j>=ry-1; j--) 
				for(int i=rx-1; i<=rx+1; i++) 
					if(m[i][j]<0) return false;
			break;
	}
	return true;
}

void draw_map(int (*fs)[3], int rx, int ry, int rdir) {
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

}

struct Coord{
	int x,y;
	Coord() {}
	Coord(int x, int y):x(x),y(y) {}
	bool operator<(const Coord & rhs) const {
		if(x == rhs.x) return y<rhs.y;
		else return x<rhs.x;
	}

};

int next_dir(int rx, int ry, int rdir) {
	int front_x=rx+dx[rdir], front_y=ry+dy[rdir];
	if(m[front_x][front_y]==1) { //전진 방향이 벽이면,
		int left_dir = (rdir+1)%4;
		return next_dir(rx, ry, left_dir);
	}
	else return rdir;
}


void cleanHouse(void)
{
	int rx=64, ry=64, rdir=0;

	while(true) {
		chk[rx][ry] = true;
		if(!has_been(rx,ry,rdir)) {
			scan(fs);
			draw_map(fs,rx,ry,rdir);
		}

		//벽타기 Logic
		int right_dir = (rdir+3)%4;
		int right_x=rx+dx[right_dir], right_y=ry+dy[right_dir];
		if(m[right_x][right_y]==1) { //오른쪽이 벽이면,
			//전진할건데, 그 자리가 벽인지 확인. 왼쪽으로 돌면서 다음으로 갈 수 있는 곳을 search
			int nrdir = next_dir(rx,ry,rdir);
			if(nrdir != rdir) {
				turn((nrdir+4 - rdir)%4); //방향 전환
				rdir = nrdir;
			}
			move();
			rx += dx[rdir];
			ry += dy[rdir];
		}
		else {
			int right_back_x = rx+dx2[rdir], right_back_y = ry+dy2[rdir];
		}
	}


}
