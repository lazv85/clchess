#pragma once
#include <iostream>

namespace NUtil {
    void ClearScreen() {
        std::wcout<< u8"\033[2J\033[1;1H"; 
    }
}