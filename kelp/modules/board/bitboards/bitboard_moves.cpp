//
// Created by gautam on 22/2/23.
//

#include "bitboard_moves.h"


BitBoardMoves::BitBoardMoves(LookupTable *lookupTable, Board *board) {
    this->board = board;
    this->lookupTable = lookupTable;
}

U64 BitBoardMoves::getPawnMoves(PieceColor color, int square, uint64_t currentBitBoard) const {
    color == P_WHITE ? _white : _black;

    U64 pawnMoves = lookupTable->getPawnMoves(color, square);

    return pawnMoves & ~currentBitBoard;
}

U64 BitBoardMoves::getPawnAttacks(PieceColor color, int square, uint64_t currentBitBoard) const {
    color == P_WHITE ? _white : _black;

    U64 pawnAttacks = lookupTable->getPawnAttacks(color, square);

    return pawnAttacks & currentBitBoard;
}

U64 BitBoardMoves::getKnightMoves(int square, uint64_t currentBitBoard) const {
    return lookupTable->getKnightAttacks(square) & ~currentBitBoard;
}

U64 BitBoardMoves::getKingMoves(int square, uint64_t currentBitBoard) const {
    return lookupTable->getKingAttacks(square) & ~currentBitBoard;
}

U64 BitBoardMoves::getRookMoves(int square, U64 occ) const {
    occ &= lookupTable->getRookMask(square);
    occ *= rookMagics[square];
    occ >>= (64 - rookOccupancyBits[square]);
    return lookupTable->getRookAttacks(square, occ) ;
}

U64 BitBoardMoves::getQueenMoves(int square, uint64_t currentBitBoard) const {
    return getRookMoves(square, currentBitBoard) ^ getBishopMoves(square, currentBitBoard);
}

U64 BitBoardMoves::getBishopMoves(int square, U64 occ) const {
    occ &= lookupTable->getBishopMask(square);
    occ *= bishopMagics[square];
    occ >>= (64 - bishopOccupancyBits[square]);
    return lookupTable->getBishopAttacks(square, occ) ;
}


