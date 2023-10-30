#include "Mainloop.h"
#include "Command.h"
#include <stdio.h>
#define		NULL	0

/************************************************* Command: helloWorld************************************************* */
bool hw_exec(Command* this) {
	printf("hello world!\n");
	return 1;
}

CmdPostExecHandler hw_post = NULL;
const char* hw_name = "hello_world";
const char* hw_help = "say hello";