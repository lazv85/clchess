#pragma once

#include "chess_board.h"
#include <sstream>

namespace NChess {
    class TCommand {
        private:                        
            TBoard& Board;
            EColor NextTurn;
            std::wstringstream Info;
            bool ValidateInput(const std::wstring& pos);
            bool ValidateMove(TCell from, TCell to);   
            bool ValidateNextTurn(TCell from);                     
            void ProcessMove();
            void UndoMove();
        public:
            TCommand(TBoard& board) 
                : Board(board)
                , NextTurn(EColor::WHITE)
            {
                NChess::LoadStartBoard(Board);
            }
            void Process();
    };
}
