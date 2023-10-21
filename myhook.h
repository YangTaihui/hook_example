#pragma once

POINT p;
HHOOK kKeyboardHook;
LRESULT CALLBACK HookProcedure(int nCode, WPARAM wParam, LPARAM lParam);
int HookCode(DWORD code);
void run_gun();
// Global var
std::atomic<bool> gun_state(false);

void run_gun()
{
    while (gun_state)
    {   
        //GetCursorPos(&p);
        //SetCursorPos(p.x+30,p.y);
        //Sleep(100);
        mouse_event(MOUSEEVENTF_MOVE, 1000, 0, 0, 0);
    }
};

BOOL HookKeyBoard()
{
    BOOL bRet = FALSE;

    kKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, //  low-level keyboard input events
                                     HookProcedure,
                                     GetModuleHandle(NULL), // A handle to the DLL containing the hook procedure
                                     NULL);

    if (!kKeyboardHook)
    {
        std::cout << "[!] Failed to get handle from SetWindowsHookEx()" << std::endl;
    }
    else
    {
        std::cout << "[*] KeyCapture handle ready" << std::endl;
        std::cout << "Press R to start/stop" << std::endl;
        MSG Msg{};
        while (GetMessage(&Msg, NULL, 0, 0) > 0)
        {
            TranslateMessage(&Msg);
            DispatchMessage(&Msg);
        }
        bRet = TRUE;
    }
    return bRet;
}

void unhookKeyboard()
{
    if (kKeyboardHook != 0)
    {
        UnhookWindowsHookEx(kKeyboardHook);
    }
    exit(0);
}

LRESULT CALLBACK HookProcedure(int nCode, WPARAM wParam, LPARAM lParam)
{
    //  LowLevelKeyboardProc Structure
    KBDLLHOOKSTRUCT *p = (KBDLLHOOKSTRUCT *)lParam;
    if (nCode == HC_ACTION)
    {
        if (wParam == WM_SYSKEYDOWN || wParam == WM_KEYDOWN)
            HookCode(p->vkCode);
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int HookCode(DWORD code)
{
    switch (code) // SWITCH ON INT
    {
    // VK_NUMPAD1 "1", VK_RETURN "[ENTER]", VK_[F1, BACK, TAB, ESCAPE, SPACE, END, HOME, DELETE]
    case 0x52: //R
        gun_state = !gun_state;
        if (gun_state)
        {
            std::thread t_gun(run_gun);
            t_gun.detach();
        }
        break;
    default:
        break;
    }
    return 0;
};
