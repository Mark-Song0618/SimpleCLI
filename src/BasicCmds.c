#include "BasicCmds.h"
#include <stdio.h>

void registerBasicCommands() {
	registerCmd(man_name, man_exec, man_post, man_help);
	addStrOption(man_name, man_opt1, man_opt1_help);

	registerCmd(quit_name, quit_exec, quit_post, quit_help);
	registerCmd(setPromp_name, setPrompt_exec, setPrompt_post, setPromp_help);
}

/************************************************* Command: man ************************************************* */
bool man_exec(Command* this) {
	Option* opt = getOption(this->_name, man_opt1);
	if (opt == NULL || !opt->_valid) {
		// show registered command
		printf("registered commands:\r\n");
		Command** pCmds = cmdMgr._cmds;
		while (*pCmds != NULL) {
			printf("\t%s:\n\t\t%s\n", (*pCmds)->_name, (*pCmds)->_helpMsg);
			++pCmds;
		}
	}
	else {
		// show options of command
		Command* cmd = getCommand(opt->_name);
		printf("%s:\n\t%s:\n", cmd->_name, cmd->_helpMsg);
		printf("Options:\n");
		Option** pOpt = cmd->_options;
		while (*pOpt != NULL) {
			printf("%s:%s", (*pOpt)->_name, (*pOpt)->_help);
			++pOpt;
		}
	}
	return true;
}

/************************************************* Command: set_prompt ************************************************* */
void setPrompt(const char* prompt);	//defined in Mainloop.c
bool setPrompt_exec(Command* this)
{
    const char* newPrompt = this->_args[0];
	setPrompt(newPrompt);
	return true;
}
