#include <windows.h>
#include <stdio.h>

int main() {
    WCHAR currentDir[MAX_PATH];
    FILE *f = fopen("runHelloworld.vbs", "w");
    if (f == NULL) {
        wprintf(L"Failed to create script file.\n");
        return -1;
    }

    GetCurrentDirectoryW(MAX_PATH, currentDir);
    fprintf(f, "Set WshShell = CreateObject(\"WScript.Shell\")\n");
    fprintf(f, "WshShell.Run \"\"\"%ls\\helloworld.exe\"\"\"\n", currentDir); // Attempt to ensure the path is quoted in VBS
    fclose(f);

    system("cscript //Nologo runHelloworld.vbs");

    // Clean up
    remove("runHelloworld.vbs");

    return 0;
}
