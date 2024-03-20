#include <windows.h>
#include <stdio.h>

int CreateAndExecuteVBSScript() {
    WCHAR currentDir[MAX_PATH];
    
    GetCurrentDirectoryW(MAX_PATH, currentDir);

    FILE *f = fopen("uniqueHelloworld.vbs", "w");
    if (f == NULL) {
        wprintf(L"Failed to create VBS script.\n");
        return -1;
    }

    fprintf(f, "Set objWMIService = GetObject(\"winmgmts:\\\\.\\root\\cimv2\")\n");
    fprintf(f, "Set colProcesses = objWMIService.ExecQuery _\n");
    fprintf(f, "    (\"Select * from Win32_Process Where Name = 'helloworld.exe'\")\n");
    fprintf(f, "If colProcesses.Count = 0 Then\n");
    fprintf(f, "    Set WshShell = CreateObject(\"WScript.Shell\")\n");
    fprintf(f, "    WshShell.Run \"%ls\\\\helloworld.exe\"\n", currentDir);
    fprintf(f, "End If\n");

    fclose(f);

    system("cscript //Nologo uniqueHelloworld.vbs");

    // Clean up
    remove("uniqueHelloworld.vbs");

    return 0;
}

int main() {
    if (CreateAndExecuteVBSScript() != 0) {
        wprintf(L"Script execution failed.\n");
        return -1;
    }

    return 0;
}
