#include <cstdio>
using namespace std;
const char *str[3] = {
	"수식을 출력하면 계산 결과가 출력됩니다.",
	"10 + 5 = 15",
	"내 생일은 2005년 6월 17일 입니다."
};

int main() {
	for(int i=0; i<3; i++) {
		printf("%s\n", str[i]);
	}
	return 0;
}
