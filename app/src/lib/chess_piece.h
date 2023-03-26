#pragma once
#include <unordered_map>
#include <string>
#include <memory>

namespace NChess {

    enum class EType {
        EMPTY,
        PAWN, 
        BISHOP,
        KNIGHT,
        ROOK,
        QUEEN,
        KING
    };
 
    const std::unordered_map<EType, std::wstring> TypesMap {
        {EType::EMPTY, L"empty"},
        {EType::PAWN, L"Pawn"},
        {EType::BISHOP, L"Bishop"},
        {EType::KNIGHT, L"Knight"},
        {EType::ROOK, L"Root"},
        {EType::QUEEN, L"Queen"},
        {EType::KING, L"King"},
    };

    const std::unordered_map<EType, wchar_t> UnicodeWhiteTypeMap {
        {EType::EMPTY, L' '},
        {EType::PAWN,  L'\u2659'},
        {EType::BISHOP,L'\u2657'},
        {EType::KNIGHT,L'\u2658'},
        {EType::ROOK,  L'\u2656'},
        {EType::QUEEN, L'\u2655'},
        {EType::KING,  L'\u2654'},
    };

    const std::unordered_map<EType, wchar_t> UnicodeBlackTypeMap {
        {EType::EMPTY, L' '},
        {EType::PAWN,  L'\u265F'},
        {EType::BISHOP,L'\u265D'},
        {EType::KNIGHT,L'\u265E'},
        {EType::ROOK,  L'\u265C'},
        {EType::QUEEN, L'\u265B'},
        {EType::KING,  L'\u265A'},
    };

    enum class EColor {
        EMPTY,
        WHITE,
        BLACK
    };
    const std::unordered_map<EColor, std::wstring> ColorsMap {
        {EColor::EMPTY, L"     "},
        {EColor::WHITE, L"White"},
        {EColor::BLACK, L"Black"}
    };

    struct TChessPiece {        
        const EColor Color;
        const EType Type;
        TChessPiece(const EColor color, const EType type) 
        : Color(color)
        , Type(type)
        {            
        }
    };

    std::unique_ptr<TChessPiece> MakeEmpty();
    std::unique_ptr<TChessPiece> MakePawn(EColor color);
    std::unique_ptr<TChessPiece> MakeBishop(EColor color);
    std::unique_ptr<TChessPiece> MakeKnight(EColor color);
    std::unique_ptr<TChessPiece> MakeRook(EColor color);
    std::unique_ptr<TChessPiece> MakeQueen(EColor color);
    std::unique_ptr<TChessPiece> MakeKing(EColor color);

}
