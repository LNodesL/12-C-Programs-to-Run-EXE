#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wchar.h>

// Function to launch an executable file using ShellExecute
int LaunchExecutable(LPCWSTR filePath) {
    // Use ShellExecute to open the file
    HINSTANCE hInstance = ShellExecuteW(NULL, L"open", filePath, NULL, NULL, SW_SHOWNORMAL);

    // Check if ShellExecute was successful
    if ((INT_PTR)hInstance <= 32) {
        wprintf(L"Failed to launch %ls.\n", filePath);
        return -1;
    }

    wprintf(L"Successfully launched %ls.\n", filePath);
    return 0;
}

int main() {

    HWND hWnd = GetConsoleWindow();
    if (hWnd != NULL) {
        ShowWindow(hWnd, SW_HIDE);
    }
    
    LPCWSTR executablePath = L"helloworld.exe";

    // Attempt to launch the executable
    if (LaunchExecutable(executablePath) != 0) {
        wprintf(L"Launch failed.\n");
        return -1;
    }

    wprintf(L"Executable launched successfully.\n");
    return 0;
}
