## introduction
	This is a simple cli.
	Although CPP is more suitable for cli(because of it's Polymorphism, we can easily create different commands), C is more
	light weight and more simple.
	Frankly speeking, this cli lib is neither easy to use, nor reliable. I'm a c language beginer and finished it in a few days.
	I'll appreciate it if you help to improve it.
	
	Regards
	Mark Song

## build
	mkdir -p build;
	cd build;
	cmake ..;
	cmake --build . --target install
	
## usage
	1. register command by:
		registerCmd(const char* cmdName, CmdExecHandler exec, CmdPostExecHandler postExec, const char* help);

	2.add options for a command:
		bool addBoolOption(const char* cmdName, const char* optName, const char* help);
		bool addIntOption(const char* cmdName, const char* optName, const char* help);
		bool addUintOption(const char* cmdName, const char* optName, const char* help);
		bool addStrOption(const char* cmdName, const char* optName, const char* help);
		
	3.start mainloop:
		mainLoop()

	4.quit cli:
		input "quit" in command line

## FYI: 
there are some pre-registered commands:
+ man *command_Name*				// show all registered commands, or options of a given command
+ set_prompt string					// set prompt characters with given string
	
	