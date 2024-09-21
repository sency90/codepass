#include <cstdio>
using namespace std;
const char *str[2] = {
	"5 Dan",
	"5 * 2 = 10"
};

int main() {
	for(int i=0; i<2; i++) {
		printf("%s\n", str[i]);
	}
	return 0;
}
