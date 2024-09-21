#include <cstdio>
using namespace std;
const char *str[5] = {
	" subject score",
	"==============",
	"  korean    90",
	" english   100",
	"computer    80"
};

int main() {
	for(int i=0; i<5; i++) {
		printf("%s\n", str[i]);
	}
	return 0;
}
