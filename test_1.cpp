#include <stdio.h>

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
	void print() const {
		printf("%d %d %d %d %d %d\n", x,y,px,py,dir,score);
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
		int i=2,l=1;
		const Info &info = arr[sz--];
		for(; i<sz; i<<=1) { //i, i<<1, (i<<1)+1
			if(i+1<sz && arr[i+1]<arr[i]) i++;
			if(arr[i] < info) {
				arr[i>>1]=arr[i];
				l=i;
			}
		}
		arr[l] = info;
	}
};
PQ mnh;

int main() {
		mnh.push(Info(1,2,3,4,5,6));
		mnh.push(Info(1,1,1,1,1,0));
		mnh.push(Info(2,2,2,2,2,1));
		mnh.push(Info(3,3,3,3,3,3));
		mnh.push(Info(4,4,4,4,4,2));
		while(!mnh.empty()) {
			for(int i=1; i<=mnh.sz; i++) {
				mnh.arr[i].print();
			}
			Info info = mnh.top(); mnh.pop();
			printf("mnh.pop() => ");
			info.print();
			puts("");
		}
	return 0;
}
