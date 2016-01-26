/* ***************************************************************************

   Copyright (c): 2008 - 2013 Hericus Software, LLC.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

//  Service.cpp : Defines the entry point for the console application.
//

#pragma once


#include <process.h>
#include <iostream>
#include <tchar.h>
#include <stdio.h>
#include <windows.h>
#include <winbase.h>
#include <winsvc.h>
#include <Shlwapi.h>

#define		MAX_NUM_OF_PROCESS		1
/** Window Service **/
VOID ServiceMainProc();
VOID Install(char* pPath, char* pName);
VOID UnInstall(char* pName);
VOID WriteLog(char* pFile, char* pMsg);
BOOL KillService(char* pName);
BOOL RunService(char* pName);
VOID ExecuteSubProcess();
VOID ProcMonitorThread(VOID *);
BOOL StartProcess(int ProcessIndex);
VOID EndProcess(int ProcessIndex);
VOID AttachProcessNames();
VOID CopyFromStaging(void);

VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv);
VOID WINAPI ServiceHandler(DWORD fdwControl);


/** Window Service **/
const int nBufferSize = 500;
CHAR pServiceName[nBufferSize+1];
CHAR pExeFile[nBufferSize+1];
CHAR lpCmdLineData[nBufferSize+1];
CHAR pLogFile[nBufferSize+1];
CHAR pWorkDir[nBufferSize+1];
BOOL ProcessStarted = TRUE;

CRITICAL_SECTION		myCS;
SERVICE_TABLE_ENTRY		lpServiceStartTable[] = 
{
	{pServiceName, ServiceMain},
	{NULL, NULL}
};

/*LPTSTR ProcessNames[] = { "C:\\n.exe",
						 "C:\\a.exe",
						 "C:\\b.exe",
						 "C:\\c.exe" };*/
LPTSTR ProcessNames[MAX_NUM_OF_PROCESS];

SERVICE_STATUS_HANDLE   hServiceStatusHandle; 
SERVICE_STATUS          ServiceStatus; 
PROCESS_INFORMATION	pProcInfo[MAX_NUM_OF_PROCESS];

int _tmain(int argc, _TCHAR* argv[])
{
	if(argc >= 2)
		strcpy_s(lpCmdLineData, argv[1]);
	ServiceMainProc();
	return 0;
}

VOID ServiceMainProc()
{
	::InitializeCriticalSection(&myCS);
	// initialize variables for .exe and .log file names
	char pModuleFile[nBufferSize+1];
	DWORD dwSize = GetModuleFileName(NULL, pModuleFile, nBufferSize);
	pModuleFile[dwSize] = 0;
	if(dwSize>4 && pModuleFile[dwSize-4] == '.')
	{
		sprintf_s(pExeFile,"%s",pModuleFile);
		pModuleFile[dwSize-4] = 0;
		sprintf_s(pLogFile,"%s.log",pModuleFile);

		sprintf_s(pWorkDir,"%s",pModuleFile);
		PathRemoveFileSpec(pWorkDir);
	}

	strcpy_s(pServiceName,"Helix");

	if(_stricmp("-i",lpCmdLineData) == 0 || _stricmp("-I",lpCmdLineData) == 0)
		Install(pExeFile, pServiceName);
	else if(_stricmp("-k",lpCmdLineData) == 0 || _stricmp("-K",lpCmdLineData) == 0)
		KillService(pServiceName);
	else if(_stricmp("-u",lpCmdLineData) == 0 || _stricmp("-U",lpCmdLineData) == 0)
		UnInstall(pServiceName);
	else if(_stricmp("-s",lpCmdLineData) == 0 || _stricmp("-S",lpCmdLineData) == 0)
		RunService(pServiceName);
	else
		ExecuteSubProcess();
}

VOID Install(char* pPath, char* pName)
{  
	SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_CREATE_SERVICE); 
	if (schSCManager==0) 
	{
		long nError = GetLastError();
		char pTemp[121];
		sprintf_s(pTemp, "OpenSCManager failed, error code = %d\n", nError);
		WriteLog(pLogFile, pTemp);
	}
	else
	{
		SC_HANDLE schService = CreateService
		( 
			schSCManager,	/* SCManager database      */ 
			pName,			/* name of service         */ 
			pName,			/* service name to display */ 
			SERVICE_ALL_ACCESS,        /* desired access          */ 
			SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS , /* service type            */ 
			SERVICE_AUTO_START,      /* start type              */ 
			SERVICE_ERROR_NORMAL,      /* error control type      */ 
			pPath,			/* service's binary        */ 
			NULL,                      /* no load ordering group  */ 
			NULL,                      /* no tag identifier       */ 
			NULL,                      /* no dependencies         */ 
			NULL,                      /* LocalSystem account     */ 
			NULL
		);                     /* no password             */ 
		if (schService==0) 
		{
			long nError =  GetLastError();
			char pTemp[121];
			sprintf_s(pTemp, "Failed to create service %s, error code = %d\n", pName, nError);
			WriteLog(pLogFile, pTemp);
		}
		else
		{
			char pTemp[121];
			sprintf_s(pTemp, "Service %s installed\n", pName);
			WriteLog(pLogFile, pTemp);
			CloseServiceHandle(schService); 
		}
		CloseServiceHandle(schSCManager);
	}	
}

VOID UnInstall(char* pName)
{
	SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
	if (schSCManager==0) 
	{
		long nError = GetLastError();
		char pTemp[121];
		sprintf_s(pTemp, "OpenSCManager failed, error code = %d\n", nError);
		WriteLog(pLogFile, pTemp);
	}
	else
	{
		SC_HANDLE schService = OpenService( schSCManager, pName, SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			long nError = GetLastError();
			char pTemp[121];
			sprintf_s(pTemp, "OpenService failed, error code = %d\n", nError);
			WriteLog(pLogFile, pTemp);
		}
		else
		{
			if(!DeleteService(schService)) 
			{
				char pTemp[121];
				sprintf_s(pTemp, "Failed to delete service %s\n", pName);
				WriteLog(pLogFile, pTemp);
			}
			else 
			{
				char pTemp[121];
				sprintf_s(pTemp, "Service %s removed\n",pName);
				WriteLog(pLogFile, pTemp);
			}
			CloseServiceHandle(schService); 
		}
		CloseServiceHandle(schSCManager);	
	}
	DeleteFile(pLogFile);
}

VOID WriteLog(char* pFile, char* pMsg)
{
	// write error or other information into log file
	::EnterCriticalSection(&myCS);
	try
	{
		SYSTEMTIME oT;
		::GetLocalTime(&oT);
		FILE* pLog = fopen(pFile,"a");
		fprintf(pLog,"%02d/%02d/%04d, %02d:%02d:%02d\n    %s",oT.wMonth,oT.wDay,oT.wYear,oT.wHour,oT.wMinute,oT.wSecond,pMsg); 
		fclose(pLog);
	} catch(...) {}
	::LeaveCriticalSection(&myCS);
}

BOOL KillService(char* pName) 
{ 
	// kill service with given name
	SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
	if (schSCManager==0) 
	{
		long nError = GetLastError();
		char pTemp[121];
		sprintf_s(pTemp, "OpenSCManager failed, error code = %d\n", nError);
		WriteLog(pLogFile, pTemp);
	}
	else
	{
		// open the service
		SC_HANDLE schService = OpenService( schSCManager, pName, SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			long nError = GetLastError();
			char pTemp[121];
			sprintf_s(pTemp, "OpenService failed, error code = %d\n", nError);
			WriteLog(pLogFile, pTemp);
		}
		else
		{
			// call ControlService to kill the given service
			SERVICE_STATUS status;
			if(ControlService(schService,SERVICE_CONTROL_STOP,&status))
			{
				CloseServiceHandle(schService); 
				CloseServiceHandle(schSCManager); 
				return TRUE;
			}
			else
			{
				long nError = GetLastError();
				char pTemp[121];
				sprintf_s(pTemp, "ControlService failed, error code = %d\n", nError);
				WriteLog(pLogFile, pTemp);
			}
			CloseServiceHandle(schService); 
		}
		CloseServiceHandle(schSCManager); 
	}
	return FALSE;
}

BOOL RunService(char* pName) 
{ 
	// run service with given name
	SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
	if (schSCManager==0) 
	{
		long nError = GetLastError();
		char pTemp[121];
		sprintf_s(pTemp, "OpenSCManager failed, error code = %d\n", nError);
		WriteLog(pLogFile, pTemp);
	}
	else
	{
		// open the service
		SC_HANDLE schService = OpenService( schSCManager, pName, SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			long nError = GetLastError();
			char pTemp[121];
			sprintf_s(pTemp, "OpenService failed, error code = %d\n", nError);
			WriteLog(pLogFile, pTemp);
		}
		else
		{
			// call StartService to run the service
			if(StartService(schService, 0, (const char**)NULL))
			{
				CloseServiceHandle(schService); 
				CloseServiceHandle(schSCManager); 
				return TRUE;
			}
			else
			{
				long nError = GetLastError();
				char pTemp[121];
				sprintf_s(pTemp, "StartService failed, error code = %d\n", nError);
				WriteLog(pLogFile, pTemp);
			}
			CloseServiceHandle(schService); 
		}
		CloseServiceHandle(schSCManager); 
	}
	return FALSE;
}


VOID ExecuteSubProcess()
{
	if(_beginthread(ProcMonitorThread, 0, NULL) == -1)
	{
		long nError = GetLastError();
		char pTemp[121];
		sprintf_s(pTemp, "StartService failed, error code = %d\n", nError);
		WriteLog(pLogFile, pTemp);
	}
	if(!StartServiceCtrlDispatcher(lpServiceStartTable))
	{
		long nError = GetLastError();
		char pTemp[121];
		sprintf_s(pTemp, "StartServiceCtrlDispatcher failed, error code = %d\n", nError);
		WriteLog(pLogFile, pTemp);
	}
	::DeleteCriticalSection(&myCS);
}

VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv)
{
	DWORD   status = 0; 
	DWORD   specificError = 0xfffffff; 
 
	ServiceStatus.dwServiceType        = SERVICE_WIN32; 
	ServiceStatus.dwCurrentState       = SERVICE_START_PENDING; 
	ServiceStatus.dwControlsAccepted   = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN | SERVICE_ACCEPT_PAUSE_CONTINUE; 
	ServiceStatus.dwWin32ExitCode      = 0; 
	ServiceStatus.dwServiceSpecificExitCode = 0; 
	ServiceStatus.dwCheckPoint         = 0; 
	ServiceStatus.dwWaitHint           = 0; 
 
	hServiceStatusHandle = RegisterServiceCtrlHandler(pServiceName, ServiceHandler); 
	if (hServiceStatusHandle==0) 
	{
		long nError = GetLastError();
		char pTemp[121];
		sprintf_s(pTemp, "RegisterServiceCtrlHandler failed, error code = %d\n", nError);
		WriteLog(pLogFile, pTemp);
		return; 
	} 
 
	// Initialization complete - report running status 
	ServiceStatus.dwCurrentState       = SERVICE_RUNNING; 
	ServiceStatus.dwCheckPoint         = 0; 
	ServiceStatus.dwWaitHint           = 0;  
	if(!SetServiceStatus(hServiceStatusHandle, &ServiceStatus)) 
	{ 
		long nError = GetLastError();
		char pTemp[121];
		sprintf_s(pTemp, "SetServiceStatus failed, error code = %d\n", nError);
		WriteLog(pLogFile, pTemp);
	} 

	AttachProcessNames();
	for(int iLoop = 0; iLoop < MAX_NUM_OF_PROCESS; iLoop++)
	{
		pProcInfo[iLoop].hProcess = 0;
		StartProcess(iLoop);
	}
}

VOID AttachProcessNames()
{
	LPTSTR lpszpath;
	lpszpath = new char[nBufferSize];
	memset(lpszpath,0x00,sizeof(lpszpath));
	DWORD dwSize = GetModuleFileName(NULL, lpszpath, nBufferSize);
	lpszpath[dwSize] = 0;
	while(lpszpath[dwSize] != '\\' && dwSize != 0)
	{
		lpszpath[dwSize] = 0; dwSize--;
	}
	for(int iLoop = 0; iLoop < MAX_NUM_OF_PROCESS; iLoop++)
	{
		ProcessNames[iLoop] = (char*) malloc(nBufferSize);
		memset(ProcessNames[iLoop], 0x00, nBufferSize);
		strcpy(ProcessNames[iLoop],lpszpath); 
	}
	strcat(ProcessNames[0], "helixmain.exe");
	//strcat(ProcessNames[1], "2.exe");
	//strcat(ProcessNames[2], "3.exe");
	//strcat(ProcessNames[3], "4.exe");
}

VOID WINAPI ServiceHandler(DWORD fdwControl)
{
	switch(fdwControl) 
	{
		case SERVICE_CONTROL_STOP:
		case SERVICE_CONTROL_SHUTDOWN:
			ProcessStarted = FALSE;
			ServiceStatus.dwWin32ExitCode = 0; 
			ServiceStatus.dwCurrentState  = SERVICE_STOPPED; 
			ServiceStatus.dwCheckPoint    = 0; 
			ServiceStatus.dwWaitHint      = 0;
			// terminate all processes started by this service before shutdown
			{
				for(int i = MAX_NUM_OF_PROCESS - 1 ; i >= 0; i--)
				{
					EndProcess(i);
					delete ProcessNames[i];
				}			
			}
			break; 
		case SERVICE_CONTROL_PAUSE:
			ServiceStatus.dwCurrentState = SERVICE_PAUSED; 
			break;
		case SERVICE_CONTROL_CONTINUE:
			ServiceStatus.dwCurrentState = SERVICE_RUNNING; 
			break;
		case SERVICE_CONTROL_INTERROGATE:
			break;
		default:
			if(fdwControl>=128&&fdwControl<256)
			{
				int nIndex = fdwControl&0x7F;
				// bounce a single process
				if(nIndex >= 0 && nIndex < MAX_NUM_OF_PROCESS)
				{
					EndProcess(nIndex);
					StartProcess(nIndex);
				}
				// bounce all processes
				else if(nIndex==127)
				{
					for(int i = MAX_NUM_OF_PROCESS-1; i >= 0; i--)
					{
						EndProcess(i);
					}
					for(int i = 0; i < MAX_NUM_OF_PROCESS; i++)
					{
						StartProcess(i);
					}
				}
			}
			else
			{
				char pTemp[121];
				sprintf_s(pTemp,  "Unrecognized opcode %d\n", fdwControl);
				WriteLog(pLogFile, pTemp);
			}
	};
    if (!SetServiceStatus(hServiceStatusHandle,  &ServiceStatus)) 
	{ 
		long nError = GetLastError();
		char pTemp[121];
		sprintf_s(pTemp, "SetServiceStatus failed, error code = %d\n", nError);
		WriteLog(pLogFile, pTemp);
    } 
}
BOOL StartProcess(int ProcessIndex)
{
	CopyFromStaging();

	STARTUPINFO startUpInfo = { sizeof(STARTUPINFO),NULL,"",NULL,0,0,0,0,0,0,0,STARTF_USESHOWWINDOW,0,0,NULL,0,0,0};  
	startUpInfo.wShowWindow = SW_HIDE;
	startUpInfo.lpDesktop = NULL;
	if(CreateProcess(NULL,				//application name 
			ProcessNames[ProcessIndex],	//command line
			NULL,				//process attributes 
			NULL,				//thread attributes 
			FALSE,				//inherit handles
			NORMAL_PRIORITY_CLASS,		//creation flags
			NULL,				//environment
			pWorkDir,			//current directory
			//"c:\\dev\\v\\client\\hub\\bin",	//current directory
			&startUpInfo,			//startup info
			&pProcInfo[ProcessIndex]	//process info
		))
	{
		Sleep(1000);
		char pTemp[256];
		sprintf_s(pTemp,"'%s' started\n", ProcessNames[ProcessIndex]); 
		WriteLog(pLogFile, pTemp);
		return TRUE;
	}
	else
	{
		long nError = GetLastError();
		char pTemp[256];
		sprintf_s(pTemp,"Failed to start program '%s', error code = %d\n", ProcessNames[ProcessIndex], nError); 
		WriteLog(pLogFile, pTemp);
		return FALSE;
	}
}


VOID EndProcess(int ProcessIndex)
{
	if(ProcessIndex >=0 && ProcessIndex <= MAX_NUM_OF_PROCESS)
	{
		if(pProcInfo[ProcessIndex].hProcess)
		{
			// post a WM_QUIT message first
			PostThreadMessage(pProcInfo[ProcessIndex].dwThreadId, WM_QUIT, 0, 0);
			Sleep(1000);
			// terminate the process by force
			TerminateProcess(pProcInfo[ProcessIndex].hProcess, 0);
		}
	}
}
VOID ProcMonitorThread(VOID *)
{
	while(ProcessStarted == TRUE)
	{
		Sleep(1000);
		DWORD dwCode;
		for(int iLoop = 0; iLoop < MAX_NUM_OF_PROCESS; iLoop++)
		{
			if(::GetExitCodeProcess(pProcInfo[iLoop].hProcess, &dwCode) && pProcInfo[iLoop].hProcess != NULL)
			{
				if(dwCode != STILL_ACTIVE)
				{
					if(StartProcess(iLoop))
					{
						char pTemp[121];
						sprintf_s(pTemp, "Restarted process %d\n", iLoop);
						WriteLog(pLogFile, pTemp);
					}
				}
			}
		}
	}
}

/** Our job is to move everything that we find in the staging directory up
  * to our current working directory.  This allows for a smooth upgrade scenario
  * where new files are downloaded and placed into staging by the active server.
  * The server then shuts itself down, relying on us to move everything from staging
  * into the main working directory and then re-activating the server with the
  * new components.
  */
VOID CopyFromStaging(void)
{
	char stagingFileName[512];
	char workFileName[512];
	char stagingDirWildcard[512];
	char pTemp[1024];
	sprintf(stagingDirWildcard, "%s\\staging\\*", pWorkDir );

	// Find all of the files in our staging directory:
	WIN32_FIND_DATA ffd;
	HANDLE hFind = FindFirstFile(stagingDirWildcard, &ffd);
	if(INVALID_HANDLE_VALUE == hFind){
		// nothing found to copy.  bail out.
		return;
	}
	do {
		if(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
			// this is a directory, skip it.
		} else {
			// This is a file, move it to our work directory
			sprintf(stagingFileName, "%s\\staging\\%s", pWorkDir, ffd.cFileName );
			sprintf(workFileName, "%s\\%s", pWorkDir, ffd.cFileName );

			// Delete the file first:
			_unlink( workFileName );

			// Then move the file over from staging
			BOOL ret = MoveFile( stagingFileName, workFileName );
			if(!ret){
				sprintf_s(pTemp, "Failed to move file (%s) from staging to bin.\n", ffd.cFileName);
				WriteLog(pLogFile, pTemp );
			} else {
				sprintf_s(pTemp, "Moved file (%s) from staging to bin.\n", ffd.cFileName);
				WriteLog(pLogFile, pTemp );
			}
		}
	} while(FindNextFile(hFind, &ffd) != 0);
	FindClose( hFind );
}
