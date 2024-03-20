#include <windows.h>
#include <stdio.h>

// Function to launch an executable in suspended mode and then resume it
int LaunchAndWait(LPCWSTR executablePath) {
    STARTUPINFOW si = {0};
    PROCESS_INFORMATION pi = {0};

    si.cb = sizeof(STARTUPINFOW);

    // Create the process in suspended state
    if (!CreateProcessW(executablePath,   // Application name
                        NULL,             // Command line
                        NULL,             // Process handle not inheritable
                        NULL,             // Thread handle not inheritable
                        FALSE,            // Set handle inheritance to FALSE
                        CREATE_SUSPENDED, // Create suspended
                        NULL,             // Use parent's environment block
                        NULL,             // Use parent's starting directory 
                        &si,              // Pointer to STARTUPINFO structure
                        &pi))             // Pointer to PROCESS_INFORMATION structure
    {
        wprintf(L"CreateProcess failed with error %lu\n", GetLastError());
        return -1;
    }

    // Process has been created suspended, now resume it
    ResumeThread(pi.hThread);

    // Wait for the launched application to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    wprintf(L"\"%ls\" executed and completed.\n", executablePath);
    return 0;
}

int main() {
    LPCWSTR exePath = L"helloworld.exe";

    // Launch the executable in a suspended state and wait for it to finish
    if (LaunchAndWait(exePath) != 0) {
        wprintf(L"Failed to launch \"%ls\".\n", exePath);
        return -1;
    }

    return 0;
}
