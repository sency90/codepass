#include <queue>
#include <vector>
#include <functional>
#include <cstdio>
#include <cstring>
using namespace std;
/// ***** user.cpp *****
extern void scan(int floorState[3][3]);
extern int move(void);
extern void turn(int mCommand);

int cx,cy,cdir;
int fs[3][3];
int m[130][130]; //Map
int dx[4] = {-1,0,1,0};
int dy[4] = {0,-1,0,1};
int chk[130][130];
int CV;
int rev_dir[3][3];

void init(void) {
	cx=cy=64; cdir=0;
	CV=0;

	for(int i=0; i<4; i++) {
		rev_dir[dx[i]+1][dy[i]+1] = i;
	}
}
bool HasBeen() {
	int cnt=0;
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
			for(int i=0,u=cx-1; i<=2; i++,u++) {
				for(int j=0,v=cy-1; j<=2; j++,v++) {
					if(m[u][v]<0) m[u][v] = fs[i][j];
				}
			}
			break;
		case 1:
			for(int i=0,v=cy-1; i<3; i++,v++) {
				for(int j=0,u=cx+1; j<3; j++,u--) {
					if(m[u][v]<0) m[u][v] = fs[i][j];
				}
			}
			break;
		case 2:
			for(int i=0,u=cx+1; i<3; i++,u--) {
				for(int j=0,v=cy+1; j<3; j++,v--) {
					if(m[u][v]<0) m[u][v] = fs[i][j];
				}
			}
			break;
		case 3:
			for(int i=0,v=cy+1; i<3; i++,v--) {
				for(int j=0,u=cx-1; j<3; j++,u++) {
					if(m[u][v]<0) m[u][v] = fs[i][j];
				}
			}
			break;
	}
}

struct Info{
	int x, y, px, py, dir, score;
	Info() {}
	Info(int x, int y, int px, int py, int dir, int score):x(x),y(y),px(px),py(py),dir(dir),score(score) {}
	bool operator<(const Info & rhs) const {
		return score < rhs.score;
	}
	bool operator>(const Info & rhs) const {
		return score > rhs.score;
	}
};

struct PQ{
	Info arr[130*130];
	int sz;

	PQ():sz(0) {}
	void clear() { sz = 0; }
	bool empty() { return sz==0; }

	void push(const Info & info) {
		int i=++sz;
		for(; i>1 && arr[i]<arr[i>>1]; i>>=1) {
			arr[i] = arr[i>>1];
		}
		arr[i] = info;
	}

	const Info & top() {
		return arr[1];
	}
	void pop() {
		int i=2;
		const Info &info = arr[sz--];
		for(; i<=sz; i<<=1) { //i, i<<1, (i<<1)+1
			if(i+1<=sz && arr[i+1]<arr[i]) i++;
			if(arr[i] < info) arr[i>>1]=arr[i];
			else break;
		}
		if(sz) arr[i>>1] = info;
	}
};
PQ mnh;
//priority_queue<Info, vector<Info>, greater<Info>> mnh;
//priority_queue<Info> mnh;

struct Coord{
	int x,y;
	Coord() {}
	Coord(int x, int y):x(x),y(y) {}
};

Coord prv[130][130];

bool FindTarget(int &tx, int &ty) {
	CV++;
	tx=ty=-1;
	mnh.push(Info(cx,cy,-1,-1,cdir,0));
	memset(prv, -1, sizeof(prv));
	while(!mnh.empty()) {
		Info info = mnh.top(); mnh.pop();
		if(chk[info.x][info.y] == CV) continue;
		chk[info.x][info.y] = CV;
		prv[info.x][info.y] = Coord(info.px, info.py);
		if(m[info.x][info.y]==0) {
			tx=info.x; ty=info.y;
			return true;
		}

		for(int i=0; i<4; i++) {
			int nx=info.x+dx[i], ny=info.y+dy[i];
			if(nx<0||ny<0||nx>=130||ny>=130) continue;
			if(m[nx][ny]==1 || m[nx][ny]<0) continue; //wall & unscanned
			if(chk[nx][ny]==CV) continue;
			if(m[nx][ny]==0 || m[nx][ny]==2) {
				mnh.push(Info(nx,ny,info.x,info.y,i,info.score+10+((i==info.dir)?0:15)));
			}
		}
	}
	return false;
}



void Go(int tx, int ty) {
	if(prv[tx][ty].x<0 && prv[tx][ty].y<0) {
		return;
	}
	Go(prv[tx][ty].x, prv[tx][ty].y);

	int ndir = rev_dir[tx-cx+1][ty-cy+1];
	if(ndir != cdir) {
		turn((ndir-cdir+4)%4);
		cdir = ndir;
	}
	move();
	cx=tx; cy=ty;
	m[cx][cy]=2;

	if(!HasBeen()) {
		scan(fs);
		DrawMap(fs);
	}
}

void cleanHouse(void) {
	for(int i=0; i<130; i++) {
		for(int j=0; j<130; j++) {
			m[i][j] = -1;
		}
	}
	memset(chk,0,sizeof(chk));
	cx=cy=64; cdir=0;
	CV=0;
	m[cx][cy]=2;

	while(true) {
		if(!HasBeen()) {
			scan(fs);
			DrawMap(fs);
		}

		bool did_go = false;
		for(int i=0; i<4; i++) {
			int ndir = (cdir+i)%4;
			int nx=cx+dx[ndir], ny=cy+dy[ndir];
			if(nx<0||ny<0||nx>=130||ny>=130) continue;
			if(m[nx][ny] == 0) {
				m[nx][ny] = 2;

				if(ndir != cdir) {
					turn(i);
					cdir = ndir;
				}
				move();
				cx=nx, cy=ny;
				did_go = true;
				break;
			}
		}

		if(!did_go) {
			int tx,ty;
			mnh.clear();
			if(FindTarget(tx,ty)) Go(tx,ty);
			else break;

		}
	}
}
