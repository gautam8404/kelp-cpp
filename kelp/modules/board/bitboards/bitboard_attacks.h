//
// Contains all code for precomputed attacks for pieces
// Only used Once at the start of the program
//

#ifndef BITBOARD_ATTACKS_H
#define BITBOARD_ATTACKS_H
#include "../../constants.h"



class BitBoardAttacks {
public:
    BitBoardAttacks();

    static U64 genPawnAttacks(PieceColor color, int square) ;
    static U64 genPawnMaskMoves(PieceColor color, int square) ;
    static U64 genKnightAttacks(int square) ;
    static U64 genKingAttacks(int square) ;

    static U64 genRookAttacks(int square, U64 block) ;
    static U64 genBishopAttacks(int square, U64 block) ;
    static U64 genRookMask(int square) ;
    static U64 genBishopMask(int square) ;


    static U64 setOccupancy(int index, int bitsCount, U64 attack_mask);
    static inline int getLSB(U64 temp);
    static inline int CountBits(U64 i);

    void SetBit(U64 &bitboard, int square);

    void ClearBit(U64 &bitboard, int square);

    bool GetBit(U64 bitboard, int square);
};


#endif //BITBOARD_ATTACKS_H
