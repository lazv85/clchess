#include "move_rules.h"

namespace NChess {

    TCell FrontMove(TCell from) {
        return {from.file, NextRankMap.at(from.rank)};
    }

    TCell BackMove(TCell from) {
        return {from.file, PrevRankMap.at(from.rank)};
    }

    TCell RightMove(TCell from) {
        return {NextFileMap.at(from.file), from.rank};
    }

    TCell LeftMove(TCell from) {
        return {PrevFileMap.at(from.file), from.rank};
    }

    TCell FrontRightMove(TCell from) {
        return {NextFileMap.at(from.file), NextRankMap.at(from.rank)};
    }

    TCell FrontLeftMove(TCell from) {
        return {PrevFileMap.at(from.file), NextRankMap.at(from.rank)};
    }

    TCell BackRightMove(TCell from) {
        return {NextFileMap.at(from.file), PrevRankMap.at(from.rank)};
    }

    TCell BackLeftMove(TCell from) {
        return {PrevFileMap.at(from.file), PrevRankMap.at(from.rank)};
    }

    bool IsEmpty(TCell cell, const TBoard& board) {
        auto piece = board.GetPiece(cell);
        return piece->Type == EType::EMPTY;
    }

    bool OutBound(TCell cell) {
        return cell.rank == ERank::END || cell.rank == ERank::BEGIN || cell.file == EFile::END || cell.file == EFile::BEGIN;
    }

    template<typename F>
    bool SweepThrough(TCell from, TCell to, F nextmove, EColor color, const TBoard& board) {
        
        TCell next = from;        
        while (next != to) {
            next = nextmove(next);
            if(OutBound(next)) {
                return false;                
            }
            if(IsEmpty(next, board) && next == to) {
                return true;
            }
            if(!IsEmpty(next, board) && next != to) {
                return false;
            } 
            if(!IsEmpty(next, board) && next == to && board.GetPiece(next)->Color != color) {
                return true;
            } 
            if(!IsEmpty(next, board) && next == to && board.GetPiece(next)->Color == color) {
                return false;
            }
        }        
        return true;
    }

    bool PawnCanMove(TCell from, TCell to, EColor color, const TBoard& board) {
        TCell next;
        auto canAttack = [&to, &board, &color](TCell next) {
            return next == to && !IsEmpty(next, board) && board.GetPiece(next)->Color != color;
        };        

        if (color == EColor::WHITE) {
            next = FrontMove(from);
            if(next == to) return IsEmpty(next, board);
            
            if(from.rank == ERank::R2 && FrontMove(next) == to) return IsEmpty(next, board);

            if(canAttack(FrontLeftMove(from))) return true;
            if(canAttack(FrontRightMove(from))) return true;
        } else {
            next = BackMove(from);
            if (next == to) return IsEmpty(next, board);

            if (from.rank == ERank::R7 && BackMove(next) == to) return IsEmpty(next, board);                               

            if (canAttack(BackLeftMove(from))) return true;
            if (canAttack(BackRightMove(from))) return true;
        }
        return false;
    } 

    bool BishopCanMove(TCell from, TCell to, EColor color, const TBoard& board) {        
        
        if(SweepThrough(from, to, FrontRightMove, color, board)) return true;

        if(SweepThrough(from, to, FrontLeftMove, color, board)) return true;

        if(SweepThrough(from, to, BackRightMove, color, board)) return true;

        if(SweepThrough(from, to, BackLeftMove, color, board)) return true;

        return false;
    }

    template<typename Func1, typename Func2>
    bool KnightStep(TCell from, TCell to, Func1 step1, Func2 step2) {
        TCell next;
        next = step1(from);
        if(OutBound(next)) return false;
        next = step1(next);
        if(OutBound(next)) return false;
        next = step2(next);
        return next == to;
    }

    bool KnightCanMove(TCell from, TCell to, EColor color, const TBoard& board) {
        auto emptyOrEnemy = [&color, &board](TCell cell) {
            return IsEmpty(cell, board) || board.GetPiece(cell)->Color != color;
        };

        if(!emptyOrEnemy(to)) return false;

        if(KnightStep(from, to, FrontMove, RightMove)) return true;
        
        if(KnightStep(from, to, FrontMove, LeftMove)) return true;

        if(KnightStep(from, to, BackMove, RightMove)) return true;
        
        if(KnightStep(from, to, BackMove, LeftMove)) return true;

        if(KnightStep(from, to, RightMove, FrontMove)) return true;

        if(KnightStep(from, to, RightMove, BackMove)) return true;

        if(KnightStep(from, to, LeftMove, FrontMove)) return true;

        if(KnightStep(from, to, LeftMove, BackMove)) return true;         

        return false;
    }

    bool RookCanMove(TCell from, TCell to, EColor color, const TBoard& board) {
        
        if(SweepThrough(from, to, FrontMove, color, board)) return true;

        if(SweepThrough(from, to, BackMove, color, board)) return true;

        if(SweepThrough(from, to, RightMove, color, board)) return true;

        if(SweepThrough(from, to, LeftMove, color, board)) return true;

        return false;
    }

    bool QueenCanMove(TCell from, TCell to, EColor color, const TBoard& board) {
        return RookCanMove(from, to, color, board) || BishopCanMove(from, to, color, board);
    }

    bool KingCanMove(TCell from, TCell to, EColor color, const TBoard& board) {    
        auto CanMakeMove = [&to, &board, &color](TCell next) {
            return next == to && ((!IsEmpty(next, board) && board.GetPiece(next)->Color != color) || IsEmpty(next, board));
        };   
        return CanMakeMove(FrontMove(from))
                || CanMakeMove(BackMove(from))
                || CanMakeMove(LeftMove(from))
                || CanMakeMove(RightMove(from))
                || CanMakeMove(FrontLeftMove(from))
                || CanMakeMove(FrontRightMove(from))
                || CanMakeMove(BackLeftMove(from))
                || CanMakeMove(BackRightMove(from));
    }

    bool PieceCanMove(TCell from, TCell to, const TBoard& board) {
        const TChessPiece* piece = board.GetPiece(from);
        if(piece->Type == EType::PAWN) {
            return PawnCanMove(from, to, piece->Color, board);
        }
        if(piece->Type == EType::BISHOP) {
            return BishopCanMove(from, to, piece->Color, board);
        }
        if(piece->Type == EType::ROOK) {
            return RookCanMove(from, to, piece->Color, board);
        }
        if(piece->Type == EType::KNIGHT) {
            return KnightCanMove(from, to, piece->Color, board);
        }
        if(piece->Type == EType::QUEEN) {
            return QueenCanMove(from, to, piece->Color, board);
        }
        if(piece->Type == EType::KING) {
            return KingCanMove(from, to, piece->Color, board);
        }
        return false;
    }

}
