#include <cassert>
#include <cstring>
#include <vector>
#include <cstdio>
using namespace std;
/// ***** user.cpp *****
extern void scan(int floorState[3][3]);
extern int move(void);
extern void turn(int mCommand);

int rx,ry,rdir;
int m[131][131];
int fs[3][3];
const int dx[] = {-1,0,1,0};
const int dy[] = {0,-1,0,1};
int rev_dir[3][3];
int CI;
int chk[131][131];

void init(void) {
	for(int i=0; i<4; i++) {
		rev_dir[dx[i]+1][dy[i]+1] = i;
	}
	CI=0;
	for(int i=0; i<131; i++) {
		for(int j=0; j<131; j++) {
			chk[i][j] = CI;
		}
	}

}

bool HasBeen() {
	for(int i=rx-1; i<=rx+1; i++) {
		for(int j=ry-1; j<=ry+1; j++) {
			if(m[i][j]<0) {
				return false;
			}
		}
	}
	return true;
}


void DrawMap(int (*fs)[3]) {
	switch(rdir) {
		case 0:
			for(int i=0; i<3; i++) {
				for(int j=0; j<3; j++) {
					if(m[rx+i-1][ry+j-1]<0) m[rx+i-1][ry+j-1] = fs[i][j];
				}
			}
			break;
		case 1:
			for(int j=0,u=0; j<3; j++,u++) {
				for(int i=2,v=0; i>=0; i--,v++) {
					if(m[rx+i-1][ry+j-1]<0) m[rx+i-1][ry+j-1] = fs[u][v];
				}
			}
			break;
		case 2:
			for(int i=2,u=0; i>=0; i--,u++) {
				for(int j=2,v=0; j>=0; j--,v++) {
					if(m[rx+i-1][ry+j-1]<0) m[rx+i-1][ry+j-1] = fs[u][v];
				}
			}
			break;
		case 3:
			for(int j=2,u=0; j>=0; j--,u++) {
				for(int i=0,v=0; i<3; i++,v++) {
					if(m[rx+i-1][ry+j-1]<0) m[rx+i-1][ry+j-1] = fs[u][v];
				}
			}
			break;
		default:
			break;
	}
}

bool Move() {
	int nx=rx+dx[rdir], ny=ry+dy[rdir];	
	if(m[nx][ny]<=0) {
		int ret = move();
		if(ret) {
			rx=nx, ry=ny;
			m[rx][ry]=2;
			return true;
		}
		else m[nx][ny]=1;
	}
	for(int i=(rdir+1)%4, j=0; j<3; j++, i=(i+1)%4) {
		int nx=rx+dx[i], ny=ry+dy[i];
		//if(m[nx][ny]<0) {
		//	//scan(fs);
		//	//DrawMap(fs);
		//	continue;
		//}
		//else 
		if(m[nx][ny]<=0) {
			if(i != rdir) {
				turn((i-rdir+4)%4);
				rdir = i;
			}
			move();
			rx=nx, ry=ny;
			m[rx][ry]=2;
			return true;
		}
	}
	return false;
}

struct Coord{
	int x,y;
	Coord(){}
	Coord(int x, int y):x(x),y(y) {}
	bool operator<(const Coord & rhs) const {
		if(x==rhs.x) return y<rhs.y;
		else return x<rhs.x;
	}
};

#include <queue>
queue<Coord> q;
Coord pco[131][131];
Coord need_scan_co, dest_co;
//int debug_cnt;
bool FindUncleanedPlace() {
	//debug_cnt++;
	while(!q.empty()) q.pop();
	need_scan_co = Coord(-1,-1);
	dest_co = Coord(-1,-1);
	chk[rx][ry] = ++CI;
	q.push(Coord(rx,ry));

	while(!q.empty()) {
		Coord co = q.front(); q.pop();
		for(int i=rdir,j=0; j<4; j++,i=(i+1)%4) {
			int nx=co.x+dx[i], ny=co.y+dy[i];
			if(m[nx][ny]==1) continue;
			else if(m[nx][ny]==-1) {
				need_scan_co = Coord(nx,ny);
				continue;
			}
			if(chk[nx][ny] == CI) continue;

			chk[nx][ny] = CI;
			//case: m[nx][ny] == 0 or 2
			if(m[nx][ny]==2) {
				pco[nx][ny] = co;
				q.push(Coord(nx,ny));
			}
			else if(m[nx][ny]==0) { //Destination
				pco[nx][ny] = co;
				while(!q.empty()) q.pop();
				dest_co = Coord(nx,ny);
				need_scan_co = Coord(-1,-1);
				return true;
			}
		}
	}

	if(need_scan_co.x >= 0) return true; //scan되지 않은 곳이 존재
	else {
		//printf("debug_cnt: %d\n", debug_cnt);
		return false; //scan되지 않은 곳이 없음. (프로그램 종료)
	}
}

vector<Coord> rpath;

bool GetPath(const Coord & tco) {
	while(!q.empty()) q.pop();
	chk[rx][ry] = ++CI;
	q.push(Coord(rx,ry));

	while(!q.empty()) {
		Coord co = q.front(); q.pop();
		for(int i=rdir,j=0; j<4; j++,i=(i+1)%4) {
			int nx=co.x+dx[i], ny=co.y+dy[i];
			if(m[nx][ny]==1) continue;
			if(chk[nx][ny] == CI) continue;

			chk[nx][ny] = CI;
			//case: m[nx][ny] == 2
			if(nx==tco.x && ny==tco.y) { //Destination
				pco[nx][ny] = co;
				while(!q.empty()) q.pop();
				rpath.push_back(Coord(nx,ny));
				while(true) {
					co = pco[nx][ny];
					rpath.push_back(co);
					if(co.x == rx && co.y == ry) break;
					nx=co.x, ny=co.y;
				}
				return true;
			}
			else if(m[nx][ny]==2 || m[nx][ny]==0) {
				pco[nx][ny] = co;
				q.push(Coord(nx,ny));
			}
		}
	}
	return false; //Unreachable Code
}


void GoTo(vector<Coord> & rpath, int idx) {
	for(int i=rpath.size()-2; i>=idx; i--) {
		int ndir = rev_dir[rpath[i].x-rx+1][rpath[i].y-ry+1];
		if(rdir != ndir) {
			turn((ndir-rdir+4)%4);
			rdir = ndir;
		}
		move();
		rx=rpath[i].x;
		ry=rpath[i].y;
		m[rx][ry]=2;
	}
	rpath.clear();
}



void cleanHouse(void) {
	rx=ry=64; rdir=0;
	memset(m, -1, sizeof(m));
	//CI=0;
	m[rx][ry]=2;

	while(true) {
		if(!HasBeen()) {
			scan(fs);
			DrawMap(fs);
		}
		if(!Move()) {
FIND_UNSCANNED:
			if(!FindUncleanedPlace()) break;
			if(dest_co.x<0 && need_scan_co.x>=0) { //scan되지 않은 곳이 존재
				assert(GetPath(need_scan_co));
				GoTo(rpath, 1); //도착지 도달 직전 좌표까지만 이동
				//scan(fs);
				//DrawMap(fs);
				if(m[need_scan_co.x][need_scan_co.y]==0) continue;
				else goto FIND_UNSCANNED;
			}
			else if(dest_co.x>=0) {
				assert(GetPath(dest_co));
				GoTo(rpath, 0); //도착지 도달 좌표까지 모두 이동
			}
			else assert(false);
			//GoTo();
		}
		//for(int i=0; i<130; i++) {
		//	for(int j=0; j<130; j++) {
		//		if(m[i][j]<0) printf("?");
		//		else if(m[i][j]==0) printf(".");
		//		else if(m[i][j]==1) printf("#");
		//		else printf("v");
		//	}
		//	puts("");
		//}
		//puts("");
	}

	//for(int i=0; i<130; i++) {
	//	for(int j=0; j<130; j++) {
	//		if(m[i][j]<0) printf("?");
	//		else if(m[i][j]==0) printf(".");
	//		else if(m[i][j]==1) printf("#");
	//		else printf("v");
	//	}
	//	puts("");
	//}
	//puts("");
}
