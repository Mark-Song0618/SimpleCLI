#include "test.h"
int main() {
	registerCmd(hw_name, hw_exec, hw_post, hw_help);
	mainLoop();
	return 0;
}
