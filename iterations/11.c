#include <stdio.h>
#include <windows.h>

int ExecuteViaTemporaryBatchFile() {
    char batchFilePath[MAX_PATH];
    char executablePath[MAX_PATH];
    FILE* batchFile;

    GetCurrentDirectoryA(sizeof(executablePath), executablePath);
    snprintf(batchFilePath, sizeof(batchFilePath), "%s\\tempRun.bat", executablePath);

    batchFile = fopen(batchFilePath, "w");
    if (!batchFile) {
        printf("Failed to create temporary batch file.\n");
        return -1;
    }

    fprintf(batchFile, "@echo off\n");
    fprintf(batchFile, "\"%s\\helloworld.exe\"\n", executablePath);
    fprintf(batchFile, "del \"%s\"\n", batchFilePath);
    fclose(batchFile);

    system(batchFilePath);

    return 0;
}

int main() {
    return ExecuteViaTemporaryBatchFile();
}
