#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    WCHAR currentDirectory[MAX_PATH];
    GetCurrentDirectoryW(MAX_PATH, currentDirectory);

    WCHAR executablePath[MAX_PATH];
    // Append the executable name to the current directory path
    swprintf(executablePath, MAX_PATH, L"%s\\helloworld.exe", currentDirectory);

    // Convert the path to a short path format to avoid issues with spaces in command line
    WCHAR shortPath[MAX_PATH];
    GetShortPathNameW(executablePath, shortPath, MAX_PATH);

    char commandCreate[MAX_PATH + 100];
    char commandRun[MAX_PATH + 100];
    char commandDelete[MAX_PATH + 100];

    // Assuming the system's default code page is sufficient for the path's characters
    sprintf(commandCreate, "schtasks /Create /SC ONCE /TN HelloworldTask /TR \"%ls\" /ST 20:40", shortPath);
    // sprintf(commandRun, "schtasks /Run /TN HelloworldTask");
    // sprintf(commandDelete, "schtasks /Delete /TN HelloworldTask /F");

    system(commandCreate);
    // system(commandRun);
    // system(commandDelete);

    return 0;
}
