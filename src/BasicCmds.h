#pragma once
#include "Command.h"

void registerBasicCommands();

/************************************************* Command: man ************************************************* */
bool man_exec(Command* this);
CmdPostExecHandler man_post = NULL;
const char* man_name = "man";
const char* man_help = "list all registered commands, or list options of a command";
const char* man_opt1 = "Command";
const char* man_opt1_help = "show options of Command";

/************************************************* Command: quit ************************************************* */
inline bool quit_exec(Command* this) { return true; }
CmdPostExecHandler quit_post = NULL;
const char*		   quit_name = "quit";
const char*        quit_help = "quit man loop";

/************************************************* Command: set_prompt ************************************************* */
bool setPrompt_exec(Command* this);
CmdPostExecHandler setPrompt_post = NULL;
const char* setPromp_name = "set_prompt";
const char* setPromp_help = "set_prompt <your_prompt>";
