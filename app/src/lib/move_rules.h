#pragma once

#include "chess_board.h"
#include "chess_piece.h"

namespace NChess {
    bool PieceCanMove(TCell from, TCell to, const TBoard& board);
}
