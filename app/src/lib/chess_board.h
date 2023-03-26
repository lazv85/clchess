#pragma once

#include <map>
#include <vector>
#include <memory>
#include <utility>
#include <vector>

#include "chess_piece.h"

namespace NChess {
    enum class ERank {
        BEGIN, R1, R2, R3, R4, R5, R6, R7, R8, END
    };
    const std::map<ERank, std::wstring> RanksMap {
        {ERank::R1, L"R1"},
        {ERank::R2, L"R2"},
        {ERank::R3, L"R3"},
        {ERank::R4, L"R4"},
        {ERank::R5, L"R5"},
        {ERank::R6, L"R6"},
        {ERank::R7, L"R7"},
        {ERank::R8, L"R8"}
    };

    const std::map<wchar_t, ERank> CharRanksMap {
        {'1', ERank::R1},
        {'2', ERank::R2},
        {'3', ERank::R3},
        {'4', ERank::R4},
        {'5', ERank::R5},
        {'6', ERank::R6},
        {'7', ERank::R7},
        {'8', ERank::R8}        
    };

    const std::map<ERank, ERank> NextRankMap {
        {ERank::R1, ERank::R2},
        {ERank::R2, ERank::R3},
        {ERank::R3, ERank::R4},
        {ERank::R4, ERank::R5},
        {ERank::R5, ERank::R6},
        {ERank::R6, ERank::R7},
        {ERank::R7, ERank::R8},
        {ERank::R8, ERank::END}
    };

    const std::map<ERank, ERank> PrevRankMap {
        {ERank::R1, ERank::BEGIN},
        {ERank::R2, ERank::R1},
        {ERank::R3, ERank::R2},
        {ERank::R4, ERank::R3},
        {ERank::R5, ERank::R4},
        {ERank::R6, ERank::R5},
        {ERank::R7, ERank::R6},
        {ERank::R8, ERank::R7}
    };    
    
    enum class EFile {
        BEGIN, A, B, C, D, E, F, G, H, END
    };
    const std::map<EFile, std::wstring> FilesMap {
        {EFile::A, L"A"},
        {EFile::B, L"B"},
        {EFile::C, L"C"},
        {EFile::D, L"D"},
        {EFile::E, L"E"},
        {EFile::F, L"F"},
        {EFile::G, L"G"},
        {EFile::H, L"H"},
    };

    const std::map<wchar_t, EFile> CharFilesMap {
        {'a', EFile::A},
        {'b', EFile::B},
        {'c', EFile::C},
        {'d', EFile::D},
        {'e', EFile::E},
        {'f', EFile::F},
        {'g', EFile::G},
        {'h', EFile::H}
    };

    const std::map<EFile, EFile> NextFileMap {
        {EFile::A, EFile::B},
        {EFile::B, EFile::C},
        {EFile::C, EFile::D},
        {EFile::D, EFile::E},
        {EFile::E, EFile::F},
        {EFile::F, EFile::G},
        {EFile::G, EFile::H},
        {EFile::H, EFile::END}
    };

    const std::map<EFile, EFile> PrevFileMap {     
        {EFile::A, EFile::BEGIN},   
        {EFile::B, EFile::A},
        {EFile::C, EFile::B},
        {EFile::D, EFile::C},
        {EFile::E, EFile::D},
        {EFile::F, EFile::E},
        {EFile::G, EFile::F},
        {EFile::H, EFile::G}
    };
    
    struct TCell {
        EFile file;
        ERank rank;
        bool operator ==(TCell cell) {
            return cell.file == file && cell.rank == rank;
        }

        bool operator !=(TCell cell) {
            return !(cell.file == file && cell.rank == rank);
        }
    };

    struct TMove {
        TCell from;
        TCell to;
        TChessPiece* CapturedPiece;
    };

    class TBoard {    
        private:
            EColor GetColor(TCell cell);
            using TBaseBoard=std::unordered_map<EFile, std::unordered_map<ERank, TChessPiece*>>;
            TBaseBoard base;
            std::unique_ptr<TChessPiece> EmptyPiece;
            std::vector<std::unique_ptr<TChessPiece>> Pieces;
            std::vector<TMove> MoveHistory;
            int CapturedWhite;
            int CapturedBlack;
            int MovesNumber;
        public:
            TBoard();            
            const TChessPiece* GetPiece(EFile file, ERank rank) const;
            const TChessPiece* GetPiece(TCell cell) const;
            TChessPiece* MakePiece(EColor color, EType type);
            void SetPiece(EFile file, ERank rank, TChessPiece* piece);
            void MakeAndSetPiece(EFile file, ERank rank, EColor color, EType type);
            bool MovePiece(TCell from, TCell to);
            bool UndoMove();
            int GetCapturedWhite();
            int GetCapturedBlack();
            int GetMovesNumber();
    };

    void PrintBoard(const TBoard& board);

    void PrintUnicodeBoard(const TBoard& board);

    void LoadStartBoard(TBoard& board); 

}
