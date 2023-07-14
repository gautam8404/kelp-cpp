#ifndef LOOKUP_TABLES_H
#define LOOKUP_TABLES_H

#include <cstdint>
#include "../../../constants.h"
#include "../bitboard_attacks.h"


#define _white 0
#define _black 1


class LookupTable {
public:
    LookupTable();

    void populate();
    void initLeaperPieces();
    void initSlidingPieces();

    const U64 &getPawnAttacks(PieceColor color, int square) const;
    const U64 &getPawnMoves(PieceColor color, int square) const;
    const U64 &getKnightAttacks(int square) const;
    const U64 &getKingAttacks(int square) const;
    const U64 &getRookAttacks(int square, U64 block) const;
    const U64 &getBishopAttacks(int square, U64 block) const;
    const U64 &getRookMask(int square) const;
    const U64 &getBishopMask(int square) const;



private:
    U64 pawnAttacks[2][64];
    U64 pawnMoves[2][64];
    U64 knightAttacks[64];
    U64 kingAttacks[64];

    U64 rookMask[64];
    U64 bishopMask[64];
    U64 rookAttacks[64][4096];
    U64 bishopAttacks[64][1024];



};

#endif //LOOKUP_TABLES_H