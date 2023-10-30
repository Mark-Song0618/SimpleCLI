#pragma once

#include "Define.h"
#include "simpleCliExport.h"
#include <string.h>

typedef enum {
	INVALID,
	BOOL,
	INT,
	UINT,
	STR,
} OptType;

typedef simpleCli_EXPORT enum {
	false = 0,
	true = 1
} bool;


typedef struct Option_t		Option;
typedef struct CmdMgr_t		CmdMgr;
typedef simpleCli_EXPORT struct Command_t	Command;

typedef simpleCli_EXPORT bool (*CmdExecHandler)(Command*);
typedef simpleCli_EXPORT void (*CmdPostExecHandler)(Command*);


struct Option_t
{
	OptType			_type;
	const char*		_name;
	const char*		_help;
	bool			_valid;	// value obsolete or not
	union
	{
		bool		_bool;
		int			_int;
		unsigned	_uInt;
		char* _str;
	}_val;
};

struct Command_t
{
	Option*				_options[MAX_OPTION_NUM +1];
	char*				_args[MAX_ARG_NUM + 1];
	const char*			_name;
	const char*			_helpMsg;
	CmdExecHandler		_execHd;		// composive
	CmdPostExecHandler	_postExecHd;
};

struct CmdMgr_t {
	Command*	_cmds[MAX_CMD_NUM];
};

CmdMgr cmdMgr;		// global var will be inited as 0

void defaultPostExecHandler(Command* this);


void removeOptions(Command* cmd);

void storeArgument(const char* arg, Command* cmd);

void cleanArguments(Command* cmd);

Command* getCommand(const char* cmd);

Option*  getOption(const char* cmd, const char* option);

// get option from buf, and store it at val
bool getBool(const char* buf, bool* val);

bool getInt(const char* buf, int* val);

bool getUint(const char* buf, unsigned* val);

bool getStr(const char* buf, char** val);

/******************************************************* user interface*******************************************************/
simpleCli_EXPORT bool addBoolOption(const char* cmdName, const char* optName, const char* help);

simpleCli_EXPORT bool addIntOption(const char* cmdName, const char* optName, const char* help);

simpleCli_EXPORT bool addUintOption(const char* cmdName, const char* optName, const char* help);

simpleCli_EXPORT bool addStrOption(const char* cmdName, const char* optName, const char* help);

// register cmd to singleton cmdMgr
simpleCli_EXPORT bool registerCmd(const char* cmdName, CmdExecHandler exec, CmdPostExecHandler postExec, const char* help);
// remove cmd from cmdMgr and free the memory
simpleCli_EXPORT bool removeCmd(const char* cmdName);
