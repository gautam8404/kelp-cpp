//
// Created by gautam on 22/2/23.
//

#ifndef BITBOARD_MOVES_H
#define BITBOARD_MOVES_H
#include "lookupTable/lookup_tables.h"
#include "../board.h"

class BitBoardMoves {
protected:
    Board *board;
    LookupTable *lookupTable;
public:
    BitBoardMoves(LookupTable *lookupTable, Board *board);

    U64 getPawnMoves(PieceColor color, int square, U64 currentBitBoard) const;
    U64 getKnightMoves(int square, U64 currentBitBoard) const;
    U64 getKingMoves(int square, U64 currentBitBoard) const;
    U64 getRookMoves(int square,  U64 occ) const;
    U64 getBishopMoves(int square, U64 occ) const;
    U64 getQueenMoves(int square, U64 currentBitBoard) const;
    U64 getPawnAttacks(PieceColor color, int square, uint64_t currentBitBoard) const;
};

#endif //BITBOARD_MOVES_H
