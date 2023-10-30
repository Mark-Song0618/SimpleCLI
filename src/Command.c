#include "Command.h"
#include <stdlib.h>

bool addBoolOption(const char* cmdName, const char* optName, const char* help)
{
	Command* cmd = getCommand(cmdName);
	for (int pos = 0; pos < MAX_OPTION_NUM; ++pos) {
		if (cmd->_options[pos] == NULL) {
			Option* newOption = (Option*)calloc(1, sizeof(Option));
			if (newOption == NULL) {
				return false;
			}
			newOption->_help = help;
			newOption->_name = optName;
			newOption->_type = BOOL;
			newOption->_valid = false;
			cmd->_options[pos] = newOption;
			return true;
		}
	}
	return false;
}

bool addIntOption(const char* cmdName, const char* optName, const char* help)
{
	Command* cmd = getCommand(cmdName);
	for (int pos = 0; pos < MAX_OPTION_NUM; ++pos) {
		Option* newOption = (Option*)calloc(1, sizeof(Option));
		if (cmd->_options[pos] == NULL) {
			if (newOption == NULL) {
				return false;
			}
			newOption->_help = help;
			newOption->_name = optName;
			newOption->_type = INT;
			newOption->_valid = false;
			cmd->_options[pos] = newOption;
			return true;
		}
	}
	return false;
}

bool addUintOption(const char* cmdName, const char* optName, const char* help)
{
	Command* cmd = getCommand(cmdName);
	for (int pos = 0; pos < MAX_OPTION_NUM; ++pos) {
		if (cmd->_options[pos] == NULL) {
			Option* newOption = (Option*)calloc(1, sizeof(Option));
			if (newOption == NULL) {
				return false;
			}
			newOption->_help = help;
			newOption->_name = optName;
			newOption->_type = UINT;
			newOption->_valid = false;
			cmd->_options[pos] = newOption;
			return true;
		}
	}
	return false;
}

bool addStrOption(const char* cmdName, const char* optName, const char* help)
{
	Command* cmd = getCommand(cmdName);
	for (int pos = 0; pos < MAX_OPTION_NUM; ++pos) {
		if (cmd->_options[pos] == NULL) {
			Option* newOption = (Option*)calloc(1, sizeof(Option));
			if (newOption == NULL) {
				return false;
			}
			newOption->_help = help;
			newOption->_name = optName;
			newOption->_type = STR;
			newOption->_valid = false;
			cmd->_options[pos] = newOption;
			return true;
		}
	}
	return false;
}

void defaultPostExecHandler(Command* this)
{
	// clean cache: set valid false
	for (int pos = 0; pos < MAX_OPTION_NUM; ++pos) {
		if (this->_options[pos] != NULL) {
			this->_options[pos]->_valid = false;
		}
	}
}

bool registerCmd(const char* cmdName, CmdExecHandler exec, CmdPostExecHandler postExec, const char* help)
{
	if (cmdName == NULL || exec == NULL) {
		return false;
	}

	for (int pos = 0; pos < MAX_CMD_NUM; ++pos) {
		Command* cmd = cmdMgr._cmds[pos];
		if (cmd == NULL) {
			Command* newCmd = (Command*)calloc(1, sizeof(Command));
			if (newCmd == NULL) {
				return false;
			}
			newCmd->_name = cmdName;
			newCmd->_execHd = exec;
			newCmd->_postExecHd = postExec;
			newCmd->_helpMsg = help;
			cmdMgr._cmds[pos] = newCmd;
			return true;
		} else if (!strcmp(cmd->_name, cmdName)) {
			return false;
		}
	}

	return false;
}

bool removeCmd(const char* cmdName)
{
	for (int pos = 0; pos < MAX_OPTION_NUM; ++pos) {
		if (!strcmp(cmdName, cmdMgr._cmds[pos]->_name)) {
			removeOptions(cmdMgr._cmds[pos]);
			cmdMgr._cmds[pos] = NULL;
			return true;
		}
	}
	return false;
}

void removeOptions(Command* cmd) {
	if (cmd == NULL) {
		return;
	}
	for (int pos = 0; pos < MAX_OPTION_NUM; ++pos) {
		if (cmd->_options[pos] != NULL) {
			if (cmd->_options[pos]->_type == STR) {
				free(cmd->_options[pos]->_val._str);
				cmd->_options[pos]->_val._str = NULL;
			}
			free(cmd->_options[pos]);
			cmd->_options[pos] = NULL;
		}
	}
}
void storeArgument(const char* arg, Command* cmd)
{
	for (int i = 0; i < MAX_ARG_NUM; ++i) {
		if (cmd->_args[i] == NULL) {
			int len = strlen(arg);
			if (cmd->_args[i] = calloc(1, len+1)) {
				memcpy(cmd->_args[i], arg, len+1);
			}
		}
	}
}


void cleanArguments(Command* cmd) {
	for (int i = 0; i < MAX_ARG_NUM; ++i) {
		if (cmd->_args[i] != NULL) {
			free(cmd->_args[i]);
			continue;
		}
		break;
	}
}

Command*
getCommand(const char* cmd)
{
	Command** ret = cmdMgr._cmds;
	while (*ret != NULL) {
		if (strcmp(cmd, (*ret)->_name))
			++ret;
		else
			break;
	}
	return *ret;
}

Option*
getOption(const char* cmdName, const char* option) {
	Command* cmd = getCommand(cmdName);
	if (cmd != NULL) {
		for (Option** opt = cmd->_options;; ++opt) {
			if (*opt == NULL) {
				return NULL;
			}
			else if (!strcmp((*opt)->_name, option)) {
				return *opt;
			}
			else {
				continue;
			}
		}
	}
	else {
		return NULL;
	}
}

bool getBool(const char* buf, bool* val)
{
	if (!strcmp(buf, "0")) {
		*val = false;
	}
	else if (!strcmp(buf, "false")) {
		*val = false;
	}
	else if (!strcmp(buf, "False")) {
		*val = false;
	}
	else {
		*val = true;
	}
	return true;
}

bool getInt(const char* buf, int* val)
{
	const char* pos = buf;
	if (*pos == '-' || *pos == '+') {
		++pos;
	}
	for (; *pos != '\0'; ++pos) {
		if (*pos < '0' || *pos >'9') {
			return false;
		}
	}
	*val = atoi(buf);
	return true;
}

bool getUint(const char* buf, unsigned* val)
{
	for (const char* pos = buf; *pos != '\0'; ++pos) {
		if (*pos < '0' || *pos >'9') {
			return false;
		}
	}
	*val = (unsigned)atoi(buf);
	return true;
}

bool getStr(const char* buf, char** val)
{
	size_t len = strlen(buf);
	char* orig = *val;
	*val = realloc(*val, len+1);
	if (*val == NULL) {
		*val = orig;
		return false;
	}
	memcpy(*val, buf, len);
	*val[len] = '\0';
	return true;
}