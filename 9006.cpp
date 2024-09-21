#include <cstdio>
using namespace std;
const char *str[3] = {
	"수를 출력할 때는 따옴표를 생략합니다.",
	"123",
	"6.500000"
};
int main() {
	for(int i=0; i<3; i++) {
		printf("%s\n", str[i]);
	}
	return 0;
}
