// DoubleProcessProtect.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>    //CreateToolhelp32Snapshot

BOOL FindProcessPid(LPCWSTR ProcessName, DWORD& dwPid)
{
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        return(FALSE);
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &pe32))
    {
        CloseHandle(hProcessSnap);          // clean the snapshot object
        return(FALSE);
    }

    BOOL    bRet = FALSE;
    do
    {
        if (!wcscmp(ProcessName, pe32.szExeFile))
        {
            dwPid = pe32.th32ProcessID;
            bRet = TRUE;
            break;
        }

    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return bRet;
}

int main(int argc, char** argv)
{
    
    DWORD Pid;
    while (1)
    {
        BOOL ss = FindProcessPid(L"Demo.exe", Pid);
        if (!ss)
        {
            WinExec("Demo.exe", SW_SHOW);
        }
        Sleep(1);
    }
}
