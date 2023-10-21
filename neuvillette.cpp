
#include <Windows.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <thread>
#include <atomic>
#include "myhook.h"

int main()
{
    if (!HookKeyBoard())
    {
        std::cout << "Hook KeyBoard Failed!" << std::endl;
    }
    unhookKeyboard();
}
