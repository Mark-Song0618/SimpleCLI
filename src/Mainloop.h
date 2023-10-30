#pragma once
#include "Command.h"
#include "simpleCliExport.h"

/******************************************************* user interface*******************************************************/
void simpleCli_EXPORT	mainLoop();


/******************************************************* internal API*******************************************************/
void					prompt(bool CR);

void					setPrompt(const char* prompt);

bool					stripCarReturn(char* buffer);	// return true if stripped cr

bool					isQuitCmd(Command* cmd);

const char*				parseCommand(const char*, Command**);

void					parseCmdErrorHandler(const char* cmd);

const char*				parseOption(const char*, Command*);

void					parseOptionErrorHandler();

void					postExecuteHandler(Command*, bool);

static char*		    _prompt = NULL;