/*

First windows 10 build: 10.0 (build 10240)   July 2015

Current build I am using: Version 1809 (OS Build 17763.253)   Febuary 1, 2019



	Windows 10 OneCore - Convergence of Kernels and base platform support binaries
						 into one

-------------------------------------------------------
		Foundation Concepts and terms				  |
-------------------------------------------------------
	**Windows API:
					User-mode system programming interface
		-Prior to 64-bit versions, API was called Win32 API 
		
		-Windows API is described in the Windows SDK docs - https://developer.microsoft.com/en-us/windows/downloads/windows-10-sdk
						 
** Windows API flavors: 
						Component Object Model (COM)- API mechanism - orginally created to enable Microsoft
						office applications to communicate and exchange data between docs, ( ex, embedding and
																			excel chart inside a Word Doc or PP)
			This is called object linking and embedding (OLE) - originally implemented using
			an old windows messaging mechanism called Dynamic Data Exchange(DDE) 
			
			Component Object Model is based on two foundational principles:
				1. clients communicat with objects (COM server objects) through interfaces,
					well defined contracts with a set of logically related methods grouped
					under the virtual table dispatch mechanism, a common way for C++ compilers
					to implement virtual functions dispatch
				2. Component implementation is loaded dynamically rather than being statically linked to the client.
				
			Term COM typically refers to a Dynamic Link Library (DLL) or an executable (EXE) where 
			COM Classes are implemented.  - cross-prossesing, marshalling, threading model ....
			
			
** Windows Runtime:

					Windows 8 introduced a new API and supporting runtime called the Windows Runtime 
					- WinRT is built on top of COM, 
					
			-Windows Apps subject to new rules, 
			
			- Windows desktop applications or classic windows applications
			

			- For JavaScript, extension called WinJS for accessing WinRT, Developers must still use HTML to build 
				their app's user interface
	
	

** The .NET Framework











** Services, functions and routines:
							
		- Windows API functions - documented, callable subroutines in the Windows API,
								ex: CreateProcess, CreateFile, GetMessage
		- Native system services ( system calls) - undocumented, underlying services in the 
			OS that are callable from user mode. 
						ex: NtCreateUserProcess
						
		- Kernel support functions (or routines) - subroutines inside The Windows OS that can be called 
			only from kernel mode
						ex: ExAllocatePoolWithTag - routine that device drivers call to allocate 
													memory from the Windows system heaps (pools)
				
		- Windows Services - processes started by the Windows service control manager 		
	
		- Dynamic link libraries- callable subroutines linked together as a binary
						file that can be dynamically loaded by applications that use 
						the subroutines.
							ex: Msvcrt.dll
							Kernel32.dll
			* Applications can share DLLs, windows ensures there is only one in-memory copy of
				a DLL's code among the applications that are referencing it. 
				
	    ***************				
****		Processes		*******
		****************
	A process is a container for a set of resources used when executing the instance of 
	a program. 
	
	At the highest level of abstaction, a Windows process comprises the following:
	
		- A private virtual address space - This is a set virtual memory addresses that
		  the process can use. 
		
		- An executable program - defines initial code and data and is mapped into the process
		   virtual address space. 
		 
		- A list of open handles - map to various system resources , semaphores, synchronization
			objects, and files that are accessible to all threads in the process. 
		
		- Security context - access token that identifies the user, security groups, 
						privileges. attributes, claims, capabilities, User Access Control (UAC), 
						virtualization state, session and limited user account state associated
						with the process, as well as the AppContainer identifier
						related to sandboxing information.
		- A process ID - unique identifier, internally part of an identifier called a client ID.
		- At least one thread of execution - 
		
	- Task Manager , most widely used tool to examine process activity
	
	*Processes are identified by the name of the image of which they are an instance.
	* Unlike objects in windows, processes can't be given global names.
	
		** THREADS - shows number of threads in each process.
		
		** Handles - number of handles to kernel objects opened bu threads running within 
				     the process.
					 
		** Status - 1. Running:
		
					2. Suspended:
					
					3. Not Responding:
	
	** each process also points to its parent process,
	
	
	
	EXPERIMENT: Viewing the Process Tree
--------------------------------------------
a unique attribute about a process that most tools don't display is the parent or creator process ID
	- Can view this value with Performance Monitor or query Creating Process ID.
	- Use the Tlist.exe in the debugging tools to show the process tree by using 
	the /t switch 
	
	Tlist directory:
						C:\Program Files (x86)\Windows Kits\10\Debuggers\x86
							
							tlist.exe -t
							
			*Tlist indents each process to show its parent/child relationship.
			*Windows maintains only the creator process ID, not a link back to the creator, and so forth.
			*Number in parentheses is the process ID....
		
****				****
	Process Explorer
****			    ****
Shows many things:
					- Process Security Token, lists of group privilages, virtualization state
					-list of services inside service-hosting processes
					- list of additional process attributes, such as mitigation policies and their process
						process level.
					-A complete list of memory-mapped files(not just DLLs)
					-User-mode and kernel mode thread stacks, including the mapping of addresses to names
					 using the Dbghelp.dll that comes with the Debugging Tools for Windows
					-Memory Manager details such as peak commit charge and kernel memory paged and non-paged
					 pool limits
					 
	EXPERIMENT: Viewing Process details with Process Explorer
------------------------------------------------------------------------------
                --Configure Symbols--
	https://docs.microsoft.com/en-us/windows/desktop/DxTechArts/debugging-with-symbols	
	
		Discusses only VS.NET and PDB format symbols, they are most recent, preferred format.
		Generated by default for projects that are compiled by using Visual Studio.
		
	PDB files generated using /Zi or /ZI (produce PDB information) compiler switch together with
	the /DEBUG(Generate Debug info) linker switch.
	
	Compiler-generated PDB files are combined and written into a single PDB file that is placed
	in the same directory as the exe
	
	By default PDB files contain:
		-Public symbols(typically all functions, static and global variables)
		-A list of object files that are responsible for sections of code in exe
		-Frame pointer optimization information (FPO)
		-Name and type info for local variables and data structures
		-Source file and line number info
	Can generate stripped PDB files = /PDBSTRIPPED:filename linker option
	use tool pdbcopy to strip existing PDB files.
	
			--Using Symbols for debugging--
	
	
			--Getting the Symbols You Need--
	Understand how debuggers find and load symbols
	Debugger uses either the symbol search path that is specified by the user- _NT_SYMBOL_PATH environment variable
	
	
	    ***************				
*****	  Threads		*******
		****************
* A thread is an entity within a process that Windows schedules for execution.
*Without it the process's program can't run.

**** Thread's context are different for each architecture that Windows runs on,
**	  this structure is architecture specific.
**
**	The Windows  	GetThreadContext    function provides access to this architecture-specific info.(CONTEXT block)

URLs:
		https://docs.microsoft.com/en-us/windows/desktop/api/processthreadsapi/nf-processthreadsapi-getthreadcontext
		https://docs.microsoft.com/en-us/windows/desktop/apiindex/windows-api-list
		https://docs.microsoft.com/en-us/windows/desktop/api/processthreadsapi/
		https://docs.microsoft.com/en-us/windows/desktop/api/_base/
		https://docs.microsoft.com/en-us/windows/desktop/Services/services
		
	GetThreadContext function:
								retrieves context of specified thread
						*A 64-bit application can retrieve the context of a WOW64 thread using:
						Wow64GetThreadContext function
				Syntax:	
						BOOL GetThreadContext(
						  HANDLE	hThread,
						  LPCONTEXT lpContext
						);
		Parameters:
	hThread - a handle to the thread whose context is to be retrieved. handle must have THREAD_GET_CONTEXT access
	to the thread.    see https://msdn.microsoft.com/72709446-5c59-4fac-8dc8-7912906ecc85

	lpContext - A pointer to a CONTEXT structure that receives the appropriate context of the specified
				thread. The value of the ContextFlags member of this structure specifies which portions
				of a thread's context are retrieved. CONTEXT structure is highly processor specific.
				Refer to the WinNT.h header file for processor-specific definitions of this structures and
				any alignment requirements.
	
	** Cannot get a valid context for a running thread, use the SuspendThread function to suspend the thread
	   before calling GetThreadContext 
	   
	   
	** Use Header: processthreadsapi.h (include Windows.h)
	       library: Kernel.32.lib
		   DLL:		Kernel32.dll
		   
*************************************************************************************************************************

---		Fibers		----		https://docs.microsoft.com/en-us/windows/desktop/procthread/fibers
------------------------		https://docs.microsoft.com/en-us/windows/desktop/procthread/using-fibers
								https://docs.microsoft.com/en-us/windows/desktop/api/winbase/nf-winbase-convertthreadtofiber
- Allow an application to schedul its own threads of execution rather than rely on 
the priority based scheduling mechanism built into Windows.

- Fibers are often called lightweight threads
- To use fibers first make a call to the Windows ConvertThreadToFiber function, which converts
  the thread to a running fiber.
  
 ---Fibers are invisible to the kernel
 ---Have issues sharing thread local storage (TLS) because several fibers can be running on the same 
    thread.
		---Fiber local sharing exists (FLS), does not solve all sharing issues, and I/O bound
		  fibers will perform poorly.
		 
		 
----		User-mode scheduling threads 	----
------------------------------------------------			 https://docs.microsoft.com/en-us/windows/desktop/procthread/user-mode-scheduling


UMS threads have their own kernel thread state and are therefore visible to 
the kernel, which allows multiple UMS threads to issue blocking system calls 
and share and contend on resources.

	
	
	
		















	
			
*/