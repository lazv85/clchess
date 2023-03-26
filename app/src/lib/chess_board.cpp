#include "chess_board.h"
#include "chess_piece.h"
#include "move_rules.h"

#include <iostream>

namespace NChess {

    TBoard::TBoard()
        : EmptyPiece(std::make_unique<TChessPiece>(EColor::EMPTY, EType::EMPTY))
        , CapturedWhite(0)
        , CapturedBlack(0)
        , MovesNumber(0)
    {
        for (auto &[rank,rankString] : RanksMap) {
            std::ignore = rankString;
            for (auto& [file, fileString]:FilesMap) {
                std::ignore = fileString;
                base[file][rank] = nullptr;
            }
        }
    }

    EColor TBoard::GetColor(TCell cell){
        if(base[cell.file][cell.rank] == nullptr){
            return EColor::EMPTY;
        } else {
            return base[cell.file][cell.rank]->Color;
        }
    }

    bool TBoard::MovePiece(TCell from, TCell to){
        if(EColor::WHITE == GetColor(to)){
            ++CapturedWhite;
        }
        if(EColor::BLACK == GetColor(to)){
            ++CapturedBlack;
        }
        ++MovesNumber;
        MoveHistory.push_back({from, to, base[to.file][to.rank]});
        base[to.file][to.rank] = base[from.file][from.rank];
        base[from.file][from.rank] = nullptr;
        return true;
    }

    bool TBoard::UndoMove(){
        if(MoveHistory.empty()) {
            return false;
        }
        auto LastMove = MoveHistory.back();
        MoveHistory.pop_back();        
        base[LastMove.from.file][LastMove.from.rank] = base[LastMove.to.file][LastMove.to.rank];
        base[LastMove.to.file][LastMove.to.rank] = LastMove.CapturedPiece;
        if(EColor::WHITE == GetColor(LastMove.to)){
            --CapturedWhite;
        }
        if(EColor::BLACK == GetColor(LastMove.to)){
            --CapturedBlack;
        }
        --MovesNumber;
        return true;
    }

    TChessPiece* TBoard::MakePiece(EColor color, EType type) {
        Pieces.emplace_back(std::make_unique<TChessPiece>(color, type));
        return Pieces.back().get();
    }

    const TChessPiece* TBoard::GetPiece(EFile file, ERank rank) const {
        if (base.at(file).at(rank) == nullptr) {
            return EmptyPiece.get();
        } else {
            return base.at(file).at(rank);
        }
    }

    const TChessPiece* TBoard::GetPiece(TCell cell) const {
        return GetPiece(cell.file, cell.rank);
    }

    void TBoard::SetPiece(EFile file, ERank rank, TChessPiece* piece) {
        base[file][rank] = piece;
    }

    void TBoard::MakeAndSetPiece(EFile file, ERank rank, EColor color, EType type) {
        TChessPiece* piece = MakePiece(color, type);
        SetPiece(file, rank, piece);
    }

    int TBoard::GetCapturedWhite() {
        return CapturedWhite;
    }

    int TBoard::GetCapturedBlack() {
        return CapturedBlack;
    }

    int TBoard::GetMovesNumber(){
        return MovesNumber;
    }

    void PrintBoard(const TBoard& board) {
        for (auto& [file, fileString]:FilesMap) {
            std::ignore = file;
            std::wcout << fileString << " ";
        }
        std::wcout << std::endl;
        for (auto &[rank,rankString] : RanksMap) {
            std::wcout << rankString << ": ";
            for (auto& [file, fileString]:FilesMap) {
                std::ignore = fileString;
                auto piece = board.GetPiece(file, rank);
                std::wcout <<"[" << ColorsMap.at(piece->Color) << ", " << TypesMap.at(piece->Type) << "] "; 
            }
            std::wcout << std::endl;
        }
    }
    

    void PrintUnicodeBoard(const TBoard& board) {
        auto printFiles = []() {
            std::wcout << "    |";
            for (auto& [file, fileString]:FilesMap) {
                std::ignore = file;
                std::wcout << fileString << "|";
            }            
            std::wcout << std::endl;    
        };
            
        printFiles();
        for (auto &[rank,rankString] : RanksMap) {
            std::wcout << rankString << ": |";
            for (auto& [file, fileString]:FilesMap) {
                std::ignore = fileString;
                auto piece = board.GetPiece(file, rank);
                if (piece->Color == EColor::WHITE) {
                    std::wcout << UnicodeWhiteTypeMap.at(piece->Type);
                } else {
                    std::wcout << UnicodeBlackTypeMap.at(piece->Type);
                }
                std::wcout << "|";              
            }
            std::wcout << std::endl;
        }
        printFiles();
    }

    void LoadStartBoard(TBoard& board) {
        for (auto& [file, strfile] : FilesMap) {
            std::ignore = strfile;
            board.MakeAndSetPiece(file, ERank::R2, EColor::WHITE, EType::PAWN);
            board.MakeAndSetPiece(file, ERank::R7, EColor::BLACK, EType::PAWN);
        }
        board.MakeAndSetPiece(EFile::A, ERank::R1, EColor::WHITE, EType::ROOK);
        board.MakeAndSetPiece(EFile::B, ERank::R1, EColor::WHITE, EType::KNIGHT);
        board.MakeAndSetPiece(EFile::C, ERank::R1, EColor::WHITE, EType::BISHOP);
        board.MakeAndSetPiece(EFile::D, ERank::R1, EColor::WHITE, EType::QUEEN);
        board.MakeAndSetPiece(EFile::E, ERank::R1, EColor::WHITE, EType::KING);
        board.MakeAndSetPiece(EFile::F, ERank::R1, EColor::WHITE, EType::BISHOP);
        board.MakeAndSetPiece(EFile::G, ERank::R1, EColor::WHITE, EType::KNIGHT);
        board.MakeAndSetPiece(EFile::H, ERank::R1, EColor::WHITE, EType::ROOK);

        board.MakeAndSetPiece(EFile::A, ERank::R8, EColor::BLACK, EType::ROOK);
        board.MakeAndSetPiece(EFile::B, ERank::R8, EColor::BLACK, EType::KNIGHT);
        board.MakeAndSetPiece(EFile::C, ERank::R8, EColor::BLACK, EType::BISHOP);
        board.MakeAndSetPiece(EFile::D, ERank::R8, EColor::BLACK, EType::KING);
        board.MakeAndSetPiece(EFile::E, ERank::R8, EColor::BLACK, EType::QUEEN);
        board.MakeAndSetPiece(EFile::F, ERank::R8, EColor::BLACK, EType::BISHOP);
        board.MakeAndSetPiece(EFile::G, ERank::R8, EColor::BLACK, EType::KNIGHT);
        board.MakeAndSetPiece(EFile::H, ERank::R8, EColor::BLACK, EType::ROOK);
    }  
}