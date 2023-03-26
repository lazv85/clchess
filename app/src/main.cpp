#include <iostream>
#include <clocale>
#include <cstdlib>

#include "lib/chess_board.h"
#include "lib/command.h"


int main(int argc, char *argv[]) {

    std::locale::global(std::locale("en_US.UTF-8"));
    std::wcout.imbue(std::locale());

    NChess::TBoard board;    
    NChess::TCommand command(board);
    command.Process();
    return 0;
}
