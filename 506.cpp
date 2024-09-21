#include <cstdio>
using namespace std;
const char *str[4] = {
	"My height",
	"170",
	"My weight",
	"68.600000"
};
int main() {
	for(int i=0; i<4; i++) {
		printf("%s\n", str[i]);
	}
	return 0;
}
