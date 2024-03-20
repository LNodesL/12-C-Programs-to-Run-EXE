#include <windows.h>
#include <stdio.h>

// Function to launch an executable and wait for its completion using ShellExecuteEx and WaitForSingleObject
int LaunchAndWait(LPCWSTR executablePath) {
    SHELLEXECUTEINFOW sei = {0};

    sei.cbSize = sizeof(SHELLEXECUTEINFOW);
    sei.fMask = SEE_MASK_NOCLOSEPROCESS;
    sei.lpVerb = L"open";
    sei.lpFile = executablePath;
    sei.nShow = SW_SHOW;
    sei.hwnd = NULL;

    // Launch the executable
    if (!ShellExecuteExW(&sei)) {
        wprintf(L"ShellExecuteEx failed with error %lu\n", GetLastError());
        return -1;
    }

    // Wait for the launched application to finish
    WaitForSingleObject(sei.hProcess, INFINITE);

    // Close the process handle
    CloseHandle(sei.hProcess);

    wprintf(L"\"%ls\" executed and completed.\n", executablePath);
    return 0;
}

int main() {
    LPCWSTR exePath = L"helloworld.exe";

    // Launch the executable and wait for it to finish
    if (LaunchAndWait(exePath) != 0) {
        wprintf(L"Failed to launch \"%ls\".\n", exePath);
        return -1;
    }

    return 0;
}
