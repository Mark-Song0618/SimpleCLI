#include "Mainloop.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void registerBasicCommands(); // forward-declaration

void
mainLoop()
{
	// initialize
	setPrompt("WelCome");
	registerBasicCommands();
	prompt(false);

	// main loop
	while (true) {
		// 1. get input
		char buf[MAX_CMDLINE_INPUT_LEN] = {'\0'};
		fgets(buf, MAX_CMDLINE_INPUT_LEN, stdin);
		stripCarReturn(buf);
		const char* position = NULL;

		// 2. parse
		Command* cmd = NULL;
		position = parseCommand(buf, &cmd);
		if (cmd == NULL) {
			parseCmdErrorHandler(buf);
			continue;
		}

		if (isQuitCmd(cmd)) {
			break;
		}
		
		//printf(cmd->_name);
		
		// if (position > prePosition) means recognized an option; 
		// stop when meet unrecognizable characters or to the end
		const char* prePosition = NULL;
		do {
			prePosition = position;
			position = parseOption(position, cmd);
		} while (position > prePosition);

		if (*position != '\0') {
			// stopped before the end, implies unrecognizable input
			parseOptionErrorHandler(cmd);
			continue;
		}

		// 3. excute
		bool ret = cmd->_execHd(cmd);
		if (cmd->_postExecHd != NULL) {
			cmd->_postExecHd(cmd);
		}
		else {
			defaultPostExecHandler(cmd);
		}

		// 4. post execute
		postExecuteHandler(cmd, ret);

		prompt(true);
	}
}

bool
stripCarReturn(char* buffer) 
{
	size_t len = strlen(buffer);
	char *pLastChar = buffer + len - 1;
	if (*pLastChar == '\n') {
		*pLastChar = '\0';
		return true;
	}
	return false;
}

void
prompt(bool CR)
{
	if (CR) {
		printf("\r\n");
	}
	printf("%s", _prompt);
}

void
setPrompt(const char* prompt)
{
	if (_prompt != NULL) {
		free(_prompt);
	}

	int len = strlen(prompt);
	_prompt = calloc(len + 2, sizeof(char));

	if (_prompt) {
		memcpy(_prompt, prompt, len);
		_prompt[len] = '>';
	}
}

bool
isQuitCmd(Command* cmd)
{
	if (!strcmp(cmd->_name, "quit")) {
		return true;
	}
	else {
		return false;
	}
}

const char*
parseCommand(const char* input, Command** result)
{
	char buf[MAX_CMDLINE_INPUT_LEN] = {'\0'};
	const char* begin = input;
	const char* end   = input;
	while (*end != ' ' && *end != '\0') {
		++end;
	}
	if (end != begin) {
		memcpy(buf, begin, end - begin);
		*result = getCommand(buf);
		if (*result != NULL) {
			return end;
		}
	}
	return input;
}

void
parseCmdErrorHandler(const char* cmd)
{
	printf("can not recognize command: \"%s\"", cmd);
	prompt(true);
}

// todo : support arguments
const char*
parseOption(const char* input, Command* cmd)
{
	bool argument = false;
	char optBuf[MAX_CMDLINE_INPUT_LEN] = { '\0' };
	char valBuf[MAX_CMDLINE_INPUT_LEN] = { '\0' };
	const char* begin = input;
	while (*input == ' ') {
		++input;
	}

	if (*input == '-') {
		// option
		++begin;
	}
	else {
		argument = true;
		// argument
	}
	const char* end = input;
	while (*end != ' ' && *end != '\0') {
		++end;
	}
	
	if (argument) {
		if (end != begin) {
			memcpy(optBuf, begin, end - begin);
			storeArgument(optBuf, cmd);
		}
		return end;
	}

	Option* opt = NULL;
	if (end != begin) {
		memcpy(optBuf, begin, end - begin);
		opt = getOption(cmd->_name, optBuf);
		if (opt == NULL) {
			return input;
		}
	}
	else {
		return input;
	}

	begin = end;
	while (*end != ' ' && *end != '\0') {
		++end;
	}
	if (end != begin) {
		memcpy(valBuf, begin, end - begin);
		switch (opt->_type)
		{
		case BOOL:
			if (getBool(valBuf, &(opt->_val._bool))) {
				break;
			}
		case INT:
			if (getInt(valBuf, &(opt->_val._int))) {
				break;
			}
			break;
		case UINT:
			if (getUint(valBuf, &(opt->_val._uInt))) {
				break;
			}
			break;
		case STR:
			if (getStr(valBuf, &(opt->_val._str))) {
				break;
			}
			break;
		default:
			return input;
		}
		opt->_valid = true;
		return end;
	}
	else {
		return input;
	}
}

void
parseOptionErrorHandler()
{
	// nothing todo so far
}

void
postExecuteHandler(Command* cmd, bool status)
{
	cleanArguments(cmd);
	if (status) {
		prompt(true);
		printf("command executed success\r\n");
	}
	else {
		prompt(true);
		printf("command executed failed\r\n");
	}
}