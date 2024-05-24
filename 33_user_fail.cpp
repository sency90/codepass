/*
   33_로봇청소기4_userTest03_FAIL
   custom PQ + array
   Greedy + Shortest Path:
   0. 현재 장소를 청소하고
   1. 상좌하우 중에 청소안한 곳으로 이동한다.
   2. 1에서 이동할 수 있는 곳이 없다면 최단거리 알고리즘을 이용하여 가장 가까운 청소해야할 곳으로 이동한다.
   3. 2의 방법으로 이동할 곳이 없다면 종료한다.
   4. scan()이 필요없는 경우를 검사한 후 scan()호출하기 코드를 추가함.
	SCORE: 8933090
*/

extern void scan(int floorState[3][3]);
extern int move(void);
extern void turn(int mCommand);

#define rnt register int

const int LM = 130;
int dr[] = { -1, 0, 1, 0 }, dc[] = { 0, -1, 0, 1 };
int Map[LM][LM];
int visited[LM][LM][4], vcnt;
int state[3][3];
int row, col, dir; // 초기 청소 시작위치 및 방향 : (r:30, c:30, d:0)으로 가정하고 시작한다.

int entry[LM * LM], ecnt;

struct Data {
	int r, c, ad, rd, path, cost;   // ad: 현재 방향, rd: (r, c)에 오는데 사용한 상대적 방향
	bool operator<(const Data&t)const {
		return cost < t.cost;  // ******
	}
}que[LM * LM], t;  // que[] : 역추적 위한 데이터 백업용
int qcnt;

struct PQ {
	Data heap[LM * LM];
	int hn;
	void clear() { hn = 0; }
	int size() { return hn; }
	bool empty() { return hn == 0; }
	Data top() { return heap[1]; }
	void push(Data nd) {
		rnt c = ++hn;
		for (; c > 1 && nd < heap[c / 2]; c /= 2) {
			heap[c] = heap[c / 2];
		}
		heap[c] = nd;
	}
	void pop() {
		Data nd = heap[hn--];
		rnt c = 2;   // nd의 왼쪽 child 인덱스
		for (; c <= hn; c *= 2) {
			if (c < hn && heap[c + 1] < heap[c]) c++;
			if (heap[c] < nd) heap[c / 2] = heap[c];
			else break;
		}
		heap[c / 2] = nd;
	}
}pq;

void mapUpdate(int r, int c, int d) {
	rnt i, j, nr, nc, flag = 0;
	////////////////////////////////////////////////////////////
	for (i = -1; i < 2; ++i) {
		for (j = -1; j < 2; ++j) {
			if (Map[r + i][c + j] == 3)
				flag++;
		}
	}
	if (flag == 0) return;
	////////////////////////////////////////////////////////////

	scan(state);                   // (row, col)을 중심으로 dir방향으로 3*3정보 얻기
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {
			if (d == 0)      nr = r - 1 + i, nc = c - 1 + j;  // 0(↑)
			else if (d == 1) nr = r - 1 + 2 - j, nc = c - 1 + i;  // 1(←)
			else if (d == 2) nr = r - 1 + 2 - i, nc = c - 1 + 2 - j;  // 2(↓)
			else             nr = r - 1 + j, nc = c - 1 + 2 - i;  // 3(→)
			if (Map[nr][nc] == 3) Map[nr][nc] = state[i][j];
		}
	}
}

void init() { }

void dfs(int idx) {
	if (idx < 2) return;
	dfs(que[idx].path);
	if (que[idx].rd) turn(que[idx].rd);
	move();
}

int findPos() {   // 최소비용으로 이동가능한 위치 찾기
	qcnt = 0;
	++vcnt;

	pq.clear();
	// 현재위치, 절대방향, 상대방향, 경로, 비용
	pq.push({ row, col, dir, 0, 0, 0 });               // 현재 위치와 방향을 시점으로

	while (!pq.empty()) {
		t = pq.top();
		pq.pop();
		if (visited[t.r][t.c][t.ad] == vcnt) continue; // 이미 방문한 경우
		visited[t.r][t.c][t.ad] = vcnt;                // 현재위치에 t.ad방향으로 최소비용으로 도착했음을 표시
		que[++qcnt] = t;                               // 경로 역추적을 위하여 백업해두기 
		if (Map[t.r][t.c] == 0)                        // 최소 이동비용이 드는 청소가능한 위치를 찾은 경우
			break;

		for (rnt rd = 0; rd < 4; ++rd) {
			rnt nd = (t.ad + rd) % 4, cost = 0;
			rnt nr = t.r + dr[nd], nc = t.c + dc[nd];

			// 이미 방문했거나, 벽이거나, 아직 스캔이 안된 곳이라면
			if (visited[nr][nc][nd] == vcnt || Map[nr][nc] == 1 || Map[nr][nc] == 3) continue;

			pq.push({ nr, nc, nd, rd, qcnt, t.cost + 10 + 15 * !!rd });
		}
	}

	if (Map[t.r][t.c]) return 0;                  // 모든 청소를 끝낸 경우

	// 역추적 방법1.
	dfs(qcnt);

	// 역추적 방법2.
	//ecnt = 0;
	//for (rnt i = qcnt; i > 1; i = que[i].path)
	//  entry[ecnt++] = que[i].rd;             // 역추적하며 상대적 방향을 저장
	//for (--ecnt; ecnt >= 0; --ecnt) {                 // 역순으로 저장했으므로
	//  rnt d = entry[ecnt];                          // 방향
	//  if (d) turn(d);                               // 방향 전환하기
	//  move();                                       // 이동하기
	//}

	row = t.r, col = t.c, dir = t.ad;                 // 청소 가능한 위치로 이동한 청소기의 현재위치와 방향
	return 1;                                         // 청소가 가능함.
}

void cleanHouse() {
	rnt i, j;
	// 맵 초기화
	for (i = 0; i < 130; ++i) {
		for (j = 0; j < 130; ++j) {
			Map[i][j] = 3;
		}
	}

	row = col = 64, dir = 0;                          // 맵이 어떻게 전개될 지 모르므로 2*2배 크기로 잡고 중앙에서 시작

	while (1) {
		Map[row][col] = 2;                            // 시작위치 청소하기
		mapUpdate(row, col, dir);                         // 3*3 정보를 Map[][]에 기록하기

		/* 인접셀 이동 코드 생략 가능 */
		rnt ret = 0;
		rnt nr = row + dr[dir], nc = col + dc[dir];  // 현재방향으로 한칸 전진한 위치
		if (Map[nr][nc] == 0) {                   // 현재 방향으로 이동가능한 경우
			ret = move();                             // 이동했으므로 결과는 1이다.
			row = nr, col = nc;                       // 위치만 이동, 방향은 변화없음
		}
		else {
			for (i = 1; i < 4; ++i) {                 // 0:현재방향, 1:왼쪽, 2:뒷쪽, 3:오른쪽
				rnt nd = (dir + i) % 4;
				nr = row + dr[nd], nc = col + dc[nd]; // i 방향으로 한칸 전진한 위치
				if (Map[nr][nc] == 0) {           // i방향으로 이동가능한 경우
					turn(i);                          // 회전하기
					ret = move();                     // 이동했으므로 결과는 1이다.
					row = nr, col = nc, dir = nd;
					break;
				}
			}
		}
		if (ret == 0) {                               // 이동이 불가능한 경우 가장 비용이 적게 드는 청소할 곳을 찾기
			if (findPos() == 0) break;                // 더이상 청소할 곳을 찾지 못한 경우
		}
	}
}
