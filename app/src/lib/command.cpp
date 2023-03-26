#include "command.h"
#include "utils.h"
#include "move_rules.h"

#include <iostream>

namespace NChess {

    bool TCommand::ValidateInput(const std::wstring& pos){
        if (pos.size() != 2) {
            std::wcout << "invalid argument: " << pos << std::endl;
            return false;
        }

        if (pos[0] < 'a' || pos[0] > 'h') {
            std::wcout << "invalid argument: " << pos << std::endl;
            return false;
        }

        if (pos[1] < '1' || pos[1] > '8') {
            std::wcout << "invalid argument: " << pos << std::endl;
            return false;
        }
        return true;
    }

    bool TCommand::ValidateNextTurn(TCell from) {
        return Board.GetPiece(from)->Color == NextTurn;
    }

    bool TCommand::ValidateMove(TCell from, TCell to){        
        return PieceCanMove(from, to, Board);                
    }

    void TCommand::UndoMove() {
        if(!Board.UndoMove()){
            Info << "No moves to undo";
        } else {
            NextTurn = (NextTurn == EColor::WHITE) ? EColor::BLACK : EColor::WHITE;
            Info << "Move has been undone";
        }
    }

    void TCommand::ProcessMove() {        
        std::wstring from, to;
        
        bool valid = false;
        while(!valid) {
            std::wcout << "Enter 'from' position(e2): ";        
            std::wcin >> from;
            std::wcout << "Enter 'to' position(e2): ";
            std::wcin >> to;
            valid = ValidateInput(from) && ValidateInput(to);
        }
        TCell fromCell{CharFilesMap.at(from[0]), CharRanksMap.at(from[1])};
        TCell toCell{CharFilesMap.at(to[0]), CharRanksMap.at(to[1])};
        if (!ValidateNextTurn(fromCell)) {
            const std::wstring& chessColor = NChess::ColorsMap.at(NextTurn);
            Info << "Can not move. It is turn of " << chessColor << " to move";
        } else if (!ValidateMove(fromCell, toCell)) {
            const std::wstring& chessPiece = NChess::TypesMap.at(Board.GetPiece(fromCell)->Type);
            const std::wstring& chessColor = NChess::ColorsMap.at(Board.GetPiece(fromCell)->Color);
            Info << "Cannot move " << chessColor << " '" << chessPiece << "' from " << from << " to " << to;            
        } else {
            Board.MovePiece(fromCell, toCell);
            NextTurn = (NextTurn == EColor::WHITE) ? EColor::BLACK : EColor::WHITE;
        }
    }

    void TCommand::Process() {
        std::wstring command;
        while (true) {
            NUtil::ClearScreen();
            NChess::PrintUnicodeBoard(Board);
            std::wcout << "score: white: [" << Board.GetCapturedBlack() 
                    << "], black: [" <<  Board.GetCapturedWhite() << "], " 
                    << "moves: [" << Board.GetMovesNumber() << "] "
                    << std::endl;
            std::wcout << "status: " << Info.str() << std::endl;
            std::wcout << "Enter command (move[m], undo[u], quit[q]): ";
            std::wcin >> command;
            Info.str(L"");
            if (command == L"q" || command == L"quit") {
                break;
            } else if (command == L"u" || command == L"undo") {
                UndoMove();
            } else {
                std::wcout << "Turn of " << NChess::ColorsMap.at(NextTurn) << " to move" << std::endl;
                ProcessMove();
            }      
        }
    }
}
