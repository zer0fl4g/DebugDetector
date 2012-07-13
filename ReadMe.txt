Name			:	DD - DebugDetector
Version			:	0.1
Coded by		:	Zer0Flag
Coded in		:	C++ / inline asm
Date			:	08.07.2012

Notes			:	- This tool should help to test if your debugger is invisible against the targets
				  Maybe some can learn something about the anti debug techniques while browsing the source
				  Ofcourse the most things are easy to bypass but you should see what you need to fix in your debugger
					  
				- If you have some ideas, other techniques (no time related things currently) or other suggestions than
				  feel free to contact me!

Contact			:	zer0fl4g@gmail.com
				irc.rizion.net / irc.freenode.de / irc.seilen.de

Ideas &
Techniques &
collected Links		:	http://www.codeproject.com/Articles/30815/An-Anti-Reverse-Engineering-Guide
				http://www.veracode.com/images/pdf/whitepaper_antidebugging.pdf
				http://spareclockcycles.org/2012/02/14/stack-necromancy-defeating-debuggers-by-raising-the-dead/
				http://www.symantec.com/connect/articles/windows-anti-debug-reference
				http://tuts4you.com/download.php?view.3260

Legend			:	+	= done;
				*	= fix it;
				-	= not done yet;
				!	= optional;
				--  	= comment;

ToDo			:	- Add more Plugins
				- Add color incase of debug detection

Features		:	+ Plugin Interface
				+ simple to use
				+ error messages
				+ Show percentage of detection
				! x64 support (inline asm needs to be ported to C++ cause visualstudio doesn�t support inline asm in x64 mode
				  the other modules should work more or less)
				+ 16 Plugins
					+ DebugObject
						-- Using NtQueryInformationProcess to see if there are Debugging Objects for our process
					+ CheckRemoteDebuggerPresent
						-- simple api which checks if a debugger is present
					+ HardwareBreakpoint
						-- checking the current thread for breakpoints in CONTEXT.dr0 - .dr3
					+ IsDebuggerPresent
						-- simple api which checks if a debugger is present
					+ MemoryBreakpoint
						-- places a page guard and in case there is no exception we know that we are debugged
					+ OpenCSRSS (doesn�t work anymore ?)
						-- Opens a handle for csrss , should not be able to without DebuggingFlag
					+ OutputDebugString
						-- if eax == 1 we are in normal mode. else offset of string is found in eax
					+ ParentProcess
						-- normaly we run with explorer.exe as parent
					+ ProcessDebugFlags
						-- uses NtQueryInformationProcess to check if our process has debugflags
					+ Unhandled Exception
						-- raises a division by 0 exception and in case we are not debugged everything wents 
						   good since we capture the exception
						! add few more exceptions
					+ PEB.BeingDebugged
						-- Checks the Process Enviroment Block if the debugbit is set
					+ PEB.GlobalFlags
						-- checks if flag is set in PEB (FLG_HEAP_ENABLE_TAIL_CHECK && FLG_HEAP_ENABLE_FREE_CHECK &&
						   FLG_HEAP_VALIDATE_PARAMETERS)
					+ PEB.ProcHeapFlag
						-- checks if the ForceFlag is set in the PEB
					+ FindBadProcesses
						-- enums the process list and checks if given processes are running
					+ FindBadWindows
						-- enums the window list and checks if given windows are found
					+ FindBadDrivers
						-- enums the driver list and checks if given drivers are found