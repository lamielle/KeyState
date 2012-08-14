// KeyState.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "KeyState.h"
#include <string>

using std::wstring;

void GetKeyStates() {
   wstring keyState;

   keyState = L"Windows Key: ";
   if (IsKeyDown(VK_LWIN)) {
      keyState += L"Down";
   } else {
      keyState += L"Up";
   }

   keyState += L"\nShift Key: ";
   if (IsKeyDown(VK_SHIFT)) {
      keyState += L"Down";
   } else {
      keyState += L"Up";
   }

   MessageBox(
        NULL,
        keyState.c_str(),
        (LPCWSTR)L"Key States",
        0
    );
}

void SendKey(int vk, bool keyUp)
{
   INPUT input;
   input.type = INPUT_KEYBOARD;
   input.ki.wScan = KEYEVENTF_SCANCODE;
   input.ki.dwExtraInfo = GetMessageExtraInfo();
   input.ki.wVk = vk;
   input.ki.dwFlags = 0;
   if (keyUp) {
      input.ki.dwFlags = KEYEVENTF_KEYUP;
   }
   input.ki.wVk = vk;
   SendInput(1, &input, sizeof(INPUT));
}

// Message handler
INT_PTR CALLBACK KeyState(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
   UNREFERENCED_PARAMETER(lParam);
   int wmId, wmEvent;
   INT_PTR res = (INT_PTR)FALSE;

   switch (message)
   {
   case WM_INITDIALOG:
      res = (INT_PTR)TRUE;
      break;
   case WM_COMMAND:
      switch(LOWORD(wParam)) {
      case IDOK:
      case IDCANCEL:
         EndDialog(hDlg, LOWORD(wParam));
         res = (INT_PTR)TRUE;
         break;
      case IDC_WINDOWN:
         SendKey(VK_LWIN, false);
         break;
      case IDC_WINUP:
         SendKey(VK_LWIN, true);
         break;
      case IDC_WINDOWNUP:
         SendKey(VK_LWIN, false);
         SendKey(VK_LWIN, true);
         break;
      case IDC_SHIFTDOWN:
         SendKey(VK_SHIFT, false);
         break;
      case IDC_SHIFTUP:
         SendKey(VK_SHIFT, true);
         break;
      case IDC_SHIFTDOWNUP:
         SendKey(VK_SHIFT, false);
         SendKey(VK_SHIFT, true);
         break;
      case IDC_GETKEYSTATES:
         GetKeyStates();
         break;
      }
      break;
   }
   return res;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
   UNREFERENCED_PARAMETER(hPrevInstance);
   UNREFERENCED_PARAMETER(lpCmdLine);
   DialogBox(hInstance, MAKEINTRESOURCE(IDD_KEYSTATE), GetDesktopWindow(), KeyState);
   return 0;
}
