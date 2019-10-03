#include "resource.h"

BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);
BOOL ExitInstance();
long EXPORT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
BOOL EXPORT CALLBACK About(HWND, UINT, WPARAM, LPARAM);
BOOL EXPORT CALLBACK DataExDialog(HWND, UINT, WPARAM, LPARAM);
