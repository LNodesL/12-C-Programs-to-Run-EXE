#include <windows.h>
#include <stdio.h>

int main() {
    WCHAR currentDir[MAX_PATH];
    WCHAR cmdLine[MAX_PATH + 50]; 

    GetCurrentDirectoryW(MAX_PATH, currentDir);
    wsprintfW(cmdLine, L"/C \"%s\\helloworld.exe\"", currentDir);

    STARTUPINFO si = {0};
    PROCESS_INFORMATION pi = {0};
    si.cb = sizeof(si);

    if (!CreateProcessW(L"C:\\Windows\\System32\\cmd.exe", cmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        wprintf(L"Failed to start process.\n");
        return -1;
    }

    // Wait for the command to complete
    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
