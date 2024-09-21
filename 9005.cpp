#include <cstdio>
using namespace std;
const char *str[2] = {
	"서식 문자로 출력하는 방법입니다.",
	"이것은 문자열을 나타냅니다."
};
int main() {
	for(int i=0; i<2; i++) {
		printf("%s\n", str[i]);
	}
	return 0;
}
