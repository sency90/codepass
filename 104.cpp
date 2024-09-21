#include <cstdio>
using namespace std;
const char *str[4] = {
	"kor 90",
	"mat 80",
	"eng 100",
	"sum 270"
};
int main() {
	for(int i=0; i<4; i++) {
		printf("%s\n", str[i]);
	}
	return 0;
}
