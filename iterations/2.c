#include <tchar.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <wchar.h>

int CopyAndExecuteFile(LPCWSTR sourceFile, LPCWSTR tempPrefix) {
    WCHAR tempDirectory[MAX_PATH], tempFile[MAX_PATH];
    DWORD tempPathLength, operationResult;

    // Retrieve the temporary directory path
    tempPathLength = GetTempPathW(MAX_PATH, tempDirectory);
    if (tempPathLength == 0 || tempPathLength > MAX_PATH) {
        wprintf(L"Error obtaining temporary directory path.\n");
        return -1;
    }

    // Create a temporary file within the temporary directory
    if (GetTempFileNameW(tempDirectory, tempPrefix, 0, tempFile) == 0) {
        wprintf(L"Error creating temporary file name.\n");
        return -1;
    }

    // Attempt to copy the source file to the temporary file location
    if (!CopyFileW(sourceFile, tempFile, FALSE)) {
        wprintf(L"Error copying file to temporary location.\n");
        return -1;
    }

    // Execute the temporary file
    STARTUPINFOW startupInfo = { sizeof(startupInfo) };
    PROCESS_INFORMATION processInfo;
    ZeroMemory(&processInfo, sizeof(PROCESS_INFORMATION));

    if (!CreateProcessW(tempFile, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo)) {
        wprintf(L"Error executing temporary file.\n");
        return -1;
    }

    // Wait for the process to exit before continuing
    WaitForSingleObject(processInfo.hProcess, INFINITE);

    // Output execution success and cleanup resources
    wprintf(L"Successfully executed temporary file.\n");
    CloseHandle(processInfo.hProcess);
    CloseHandle(processInfo.hThread);

    return 0;
}

int main() {
    LPCWSTR sourceFileName = L"helloworld.exe";
    LPCWSTR tempFilePrefix = L"EXE";

    int result = CopyAndExecuteFile(sourceFileName, tempFilePrefix);
    if (result != 0) {
        wprintf(L"Failed to copy and execute file.\n");
        return result;
    }

    return 0;
}
