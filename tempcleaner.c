#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void CleanTempFiles() {
    char tempPath[MAX_PATH];
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;

  
    DWORD pathLen = GetTempPath(MAX_PATH, tempPath);
    if (pathLen == 0 || pathLen > MAX_PATH) {
        printf("Couldnt read the %TEMP%.\n");
        return;
    }

    
    char searchPath[MAX_PATH];
    snprintf(searchPath, sizeof(searchPath), "%s*", tempPath);

    hFind = FindFirstFile(searchPath, &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("No files to delete.\n");
        return;
    }

    do {
      
        if (strcmp(findFileData.cFileName, ".") == 0 || strcmp(findFileData.cFileName, "..") == 0) {
            continue;
        }

        char fullFilePath[MAX_PATH];
        snprintf(fullFilePath, sizeof(fullFilePath), "%s%s", tempPath, findFileData.cFileName);

        if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (!RemoveDirectory(fullFilePath)) {
      
            }
        } else {
            if (DeleteFile(fullFilePath)) {
                printf("File deleted: %s\n", fullFilePath);
            } else {
                printf("Cant delete: %s\n", fullFilePath);
            }
        }

    } while (FindNextFile(hFind, &findFileData));

    FindClose(hFind);
}

int main() {
    printf("Cleaning temp folder..\n");
    CleanTempFiles();
    printf("done\n");
    return 0;
}
