#include "chess_piece.h"

namespace NChess {

    std::unique_ptr<TChessPiece> MakeEmpty() {
        return std::make_unique<TChessPiece>(EColor::EMPTY, EType::EMPTY);
    }

    std::unique_ptr<TChessPiece> MakePawn(EColor color) {
        return std::make_unique<TChessPiece>(color, EType::PAWN);
    }

    std::unique_ptr<TChessPiece> MakeBishop(EColor color) {
        return std::make_unique<TChessPiece>(color, EType::BISHOP);
    }

    std::unique_ptr<TChessPiece> MakeKnight(EColor color) {
        return std::make_unique<TChessPiece>(color, EType::KNIGHT);
    }

    std::unique_ptr<TChessPiece> MakeRook(EColor color) {
        return std::make_unique<TChessPiece>(color, EType::ROOK);
    }
    std::unique_ptr<TChessPiece> MakeQueen(EColor color) {
        return std::make_unique<TChessPiece>(color, EType::QUEEN);
    }

    std::unique_ptr<TChessPiece> MakeKing(EColor color) {
        return std::make_unique<TChessPiece>(color, EType::KING);
    }

} // namespace NChess


    