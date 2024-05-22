#include <stdio.h>
/// ***** user.cpp *****
extern void scan(int floorState[3][3]);
extern int move(void);
extern void turn(int mCommand);

int M;
int fs[3][3];
int m[131][131];
int chk[131][131];
int dx[4] = {-1,0,1,0};
int dy[4] = {0,-1,0,1};
int dx2[4] = {1,-1,-1,1}; //right back
int dy2[4] = {1,1,-1,-1}; //right back

void init(void) {
	for(int i=0; i<131; i++) {
		for(int j=0; j<131; j++) {
			m[i][j] = -1;
			chk[i][j] = 0;
		}
	}
}

inline int min(int x, int y) { return x<y?x:y; }
inline int max(int x, int y) { return x>y?x:y; }

bool HasBeen(int rx, int ry, int dir) {
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

void DrawMap(int (*fs)[3], int rx, int ry, int rdir) {
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

inline int RightDir(int dir) {
	return (dir+3)%4;
}
inline int LeftDir(int dir) {
	return (dir+1)%4;
}
inline void Turn(int & cur_dir, int & next_dir) {
	turn((next_dir+4 - cur_dir)%4);
	cur_dir = next_dir;
}
inline void GoStraight(int & rx, int & ry, int rdir) {
	move();
	rx += dx[rdir];
	ry += dy[rdir];
}


int NextDir(int rx, int ry, int rdir) {
	int front_x=rx+dx[rdir], front_y=ry+dy[rdir];
	if(m[front_x][front_y]==1) { //전진 방향이 벽이면,
		return NextDir(rx, ry, LeftDir(rdir));
	}
	else return rdir;
}


void cleanHouse(void)
{
	int rx=64, ry=64, rdir=0;
	//chk[rx][ry][rdir] = true;
	chk[rx][ry] |= 1<<rdir;

	while(true) { //테두리를 돌면서 맵 윤곽 잡기.
		if(!HasBeen(rx,ry,rdir)) {
			scan(fs);
			DrawMap(fs,rx,ry,rdir);
		}

		//벽타기 Logic
		int right_dir = RightDir(rdir);
		int right_x=rx+dx[right_dir], right_y=ry+dy[right_dir];
		if(m[right_x][right_y]==1) { //오른쪽이 벽이면,
			//전진할건데, 그 자리가 벽인지 확인. 왼쪽으로 돌면서 다음으로 갈 수 있는 곳을 search
			int nrdir = NextDir(rx,ry,rdir);
			if(nrdir != rdir) {
				//if(chk[rx][ry][nrdir]) break;
				if((chk[rx][ry] >> nrdir) & 0x1) break;
				//chk[rx][ry][nrdir] = true;
				chk[rx][ry] |= 1<<nrdir;
				Turn(rdir, nrdir); //방향 전환
			}
				if((chk[rx+dx[rdir]][ry+dy[rdir]] >> rdir) & 0x1) break;
				chk[rx+dx[rdir]][ry+dy[rdir]] |= 1<<rdir;
			GoStraight(rx, ry, rdir);
		}
		else {
			int right_back_x = rx+dx2[rdir], right_back_y = ry+dy2[rdir];
			if(m[right_back_x][right_back_y]==1) { //오른쪽이 벽이 아니면서 오른쪽 뒤가 벽이면,
				int nrdir = RightDir(rdir); //right turn
				if((chk[rx][ry] >> nrdir) & 0x1) break;
				chk[rx][ry] |= 1<<nrdir;
				Turn(rdir, nrdir);
				if((chk[rx+dx[rdir]][ry+dy[rdir]] >> rdir) & 0x1) break;
				chk[rx+dx[rdir]][ry+dy[rdir]] |= 1<<rdir;

				GoStraight(rx, ry, rdir);
			}
			else {
				int nrdir = NextDir(rx,ry,rdir);
				if(nrdir != rdir) {
				if((chk[rx][ry] >> nrdir) & 0x1) break;
				chk[rx][ry] |= 1<<nrdir;
					Turn(rdir, nrdir); //방향 전환
				}
				if((chk[rx+dx[rdir]][ry+dy[rdir]] >> rdir) & 0x1) break;
				chk[rx+dx[rdir]][ry+dy[rdir]] |= 1<<rdir;
				GoStraight(rx, ry, rdir);
			}
		}
	}

#if 1 //DEBUG
	const int inf = 0x3f3f3f3f;
	int sx=inf, sy=inf, ex=0, ey=0;
	for(int i=0; i<131; i++) {
		for(int j=0; j<131; j++) {
			if(m[i][j]>=0) {
				sx = min(sx,i);
				ex = max(ex,i+1);
				sy = min(sy,j);
				ey = max(ey,j+1);
			}
		}
	}

	for(int i=sx; i<ex; i++) {
		for(int j=sy; j<ey; j++) {
			if(i==64 && j==64) printf("*");
			else if(chk[i][j]==0) {
				if(m[i][j]<0) printf("?");
				else if(m[i][j]==0) printf(".");
				else printf("#");
			}
			else printf("%X", chk[i][j]);
		}
		puts("");
	}
	puts("");
	printf("* -> %X\n", chk[64][64]);
#endif


	//while(true) {

	//}
}
