#include <windows.h>
#include <wchar.h>

int ExecuteWithPowerShellMonitoring() {
    WCHAR currentDir[MAX_PATH];
    WCHAR psCommand[MAX_PATH + 100]; // Buffer to hold the PowerShell command
    STARTUPINFOW si = {0};
    PROCESS_INFORMATION pi = {0};
    si.cb = sizeof(si);

    // Get the current directory where the executable is located
    if (!GetCurrentDirectoryW(MAX_PATH, currentDir)) {
        wprintf(L"Failed to get current directory.\n");
        return -1;
    }

    // Format the PowerShell command to run "helloworld.exe" from the current directory
    wsprintfW(psCommand, 
        L"powershell -Command \"& {Start-Process '%s\\\\helloworld.exe' -Wait}\"", 
        currentDir);

    // Execute the PowerShell command
    if (!CreateProcessW(NULL, psCommand, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        wprintf(L"Failed to start PowerShell process. Error: %lu\n", GetLastError());
        return -1;
    }

    // Wait for "helloworld.exe" to finish executing
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Clean up handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}

int main() {
    if (ExecuteWithPowerShellMonitoring() != 0) {
        wprintf(L"Failed to execute 'helloworld.exe' with monitoring.\n");
        return -1;
    }

    return 0;
}
