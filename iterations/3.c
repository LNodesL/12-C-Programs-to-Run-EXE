#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wchar.h>

// Function to execute an executable file as a new process
int ExecuteProcess(LPCWSTR executablePath) {
    STARTUPINFOW si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Start the child process. 
    if (!CreateProcessW(executablePath,   // No module name (use command line)
        NULL,        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi)           // Pointer to PROCESS_INFORMATION structure
    ) {
        wprintf(L"CreateProcess failed (%d).\n", GetLastError());
        return -1;
    }

    // Wait until child process exits.
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles. 
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    wprintf(L"Executed \"%ls\" successfully.\n", executablePath);
    return 0;
}

int main() {
    LPCWSTR exePath = L"helloworld.exe";

    // Execute the specified executable
    if (ExecuteProcess(exePath) != 0) {
        wprintf(L"Failed to execute the process.\n");
        return -1;
    }

    return 0;
}
