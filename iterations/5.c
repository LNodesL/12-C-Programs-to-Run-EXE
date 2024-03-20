#include <windows.h>
#include <stdio.h>

int ReplicateAndExecute(LPCWSTR srcFilePath, LPCWSTR dstFilePath) {
    if (!CopyFileW(srcFilePath, dstFilePath, FALSE)) {
        wprintf(L"CopyFile failed with error %lu\n", GetLastError());
        return -1;
    }

    STARTUPINFOW si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcessW(dstFilePath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        wprintf(L"CreateProcess failed with error %lu\n", GetLastError());
        DeleteFileW(dstFilePath); // Use DeleteFileW here
        return -1;
    }

    // After usage
    DeleteFileW(dstFilePath); // Use DeleteFileW here

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    wprintf(L"Successfully executed %ls\n", dstFilePath);

    return 0;
}

int main() {
    WCHAR currentDirectory[MAX_PATH];
    GetCurrentDirectoryW(MAX_PATH, currentDirectory);
    
    // Append your new directory name to the current path
    WCHAR newDirectoryPath[MAX_PATH];
    wsprintfW(newDirectoryPath, L"%s\\TempProgramDir", currentDirectory);
    
    // Ensure the directory exists
    CreateDirectoryW(newDirectoryPath, NULL);

    WCHAR srcExePath[] = L"helloworld.exe";
    
    // Construct the destination path within the new directory
    WCHAR dstExePath[MAX_PATH];
    wsprintfW(dstExePath, L"%s\\helloworld_copied.exe", newDirectoryPath);

    if (ReplicateAndExecute(srcExePath, dstExePath) != 0) {
        wprintf(L"Failed to replicate and execute the file.\n");
        // Attempt to remove the directory even if replication fails, to ensure cleanup
    }

    // Clean up: Delete the created file and remove the directory
    DeleteFileW(dstExePath);
    RemoveDirectoryW(newDirectoryPath);

    return 0;
}
