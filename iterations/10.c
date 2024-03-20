#include <windows.h>
#include <stdio.h>

void GetCurrentProgramDirectory(char* programDir, size_t length) {
    DWORD size = GetModuleFileName(NULL, programDir, length);
    if (size == 0 || size == length) {
        // Handle error
        programDir[0] = '\0'; // Ensure null-terminated string on failure
        return;
    }

    // Find the last backslash (directory separator) and truncate the string there to remove the executable name
    char* lastBackslash = strrchr(programDir, '\\');
    if (lastBackslash != NULL) {
        *(lastBackslash + 1) = '\0'; // Keep the trailing backslash
    }
}

int main() {
    HKEY hKey;
    const char* regPath = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    const char* valueName = "MyAppLauncher";
    char programDir[MAX_PATH];
    char command[MAX_PATH];

    GetCurrentProgramDirectory(programDir, sizeof(programDir));
    snprintf(command, sizeof(command), "%shelloworld.exe", programDir); // Construct the full path

    // Open or create the key where we set startup commands
    if (RegOpenKeyEx(HKEY_CURRENT_USER, regPath, 0, KEY_WRITE, &hKey) == ERROR_SUCCESS) {
        // Set the value to launch helloworld.exe
        if (RegSetValueEx(hKey, valueName, 0, REG_SZ, (BYTE*)command, strlen(command) + 1) == ERROR_SUCCESS) {
            printf("Command added to registry.\n");
        } else {
            printf("Failed to add command to registry.\n");
        }

        RegCloseKey(hKey);
    } else {
        printf("Failed to open registry key.\n");
    }

    // Trigger the command. This is a simplistic way to execute the command added to the registry for demonstration purposes.
    char triggerCmd[MAX_PATH];
    snprintf(triggerCmd, sizeof(triggerCmd), "cmd /c start \"\" \"%s\"", command);
    system(triggerCmd);

    // Cleanup registry after execution for safety
    if (RegOpenKeyEx(HKEY_CURRENT_USER, regPath, 0, KEY_WRITE, &hKey) == ERROR_SUCCESS) {
        RegDeleteValue(hKey, valueName);
        RegCloseKey(hKey);
    }

    return 0;
}
