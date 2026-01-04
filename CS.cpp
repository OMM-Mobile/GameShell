#include <windows.h>
#include <string>
#include <vector>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    wchar_t exePath[MAX_PATH];
    GetModuleFileNameW(NULL, exePath, MAX_PATH);

    std::wstring appDir = exePath;
    appDir = appDir.substr(0, appDir.find_last_of(L"\\/"));

    std::wstring javaExe = appDir + L"\\java\\bin\\javaw.exe";

    // Build the command line string
    std::wstring cmd =
        L"\"" + javaExe + L"\""
        L" -Djava.library.path=\"" + appDir + L"\\lib\""
        L" -cp \"" + appDir + L"\\lib\\*;" + appDir + L"\""
        L" GameShell";

    // --- FIX: Make a writable copy for CreateProcessW ---
    std::vector<wchar_t> cmdBuffer(cmd.begin(), cmd.end());
    cmdBuffer.push_back(0); // Add null terminator

    STARTUPINFOW si{};
    PROCESS_INFORMATION pi{};
    si.cb = sizeof(si);

    if (!CreateProcessW(
        NULL,
        cmdBuffer.data(), // Pass the writable buffer
        NULL,
        NULL,
        FALSE,
        CREATE_NO_WINDOW,
        NULL,
        appDir.c_str(),
        &si,
        &pi
    )) {
        // This function requires linking User32.lib
        MessageBoxW(NULL, L"Failed to start GameShell", L"GameShell", MB_ICONERROR);
        return 1;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}
