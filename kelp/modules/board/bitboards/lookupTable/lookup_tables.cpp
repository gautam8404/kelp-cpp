#include "lookup_tables.h"

LookupTable::LookupTable() {
    populate();
}

void LookupTable::populate() {

    initLeaperPieces();
    initSlidingPieces();
}

void LookupTable::initLeaperPieces() {
    for (int i = 0; i < 64; i++){
        knightAttacks[i] = BitBoardAttacks::genKnightAttacks(i);
        kingAttacks[i] = BitBoardAttacks::genKingAttacks(i);
        pawnAttacks[_white][i] = BitBoardAttacks::genPawnAttacks(P_WHITE, i);
        pawnAttacks[_black][i] = BitBoardAttacks::genPawnAttacks(P_BLACK, i);
        pawnMoves[_white][i] = BitBoardAttacks::genPawnMaskMoves(P_WHITE, i);
        pawnMoves[_black][i] = BitBoardAttacks::genPawnMaskMoves(P_BLACK, i);
    }
}

void LookupTable::initSlidingPieces() {
    for (int i = 0; i < 64; i++){
        rookMask[i] = BitBoardAttacks::genRookMask(i);
        bishopMask[i] = BitBoardAttacks::genBishopMask(i);

        int rbits, occupancy_index, magic;
        U64 occupancy, attack_mask;

        // bishop
        attack_mask = bishopMask[i];
        rbits = BitBoardAttacks::CountBits(attack_mask);
        occupancy_index = (1 << rbits);

        for (int j = 0; j < occupancy_index; j++){
            occupancy =  BitBoardAttacks::setOccupancy(j, rbits, attack_mask);
            magic = (occupancy * bishopMagics[i]) >> (64 - bishopOccupancyBits[i]);
            bishopAttacks[i][magic] = BitBoardAttacks::genBishopAttacks(i, occupancy);
        }
        // rook

        attack_mask = rookMask[i];
        rbits = BitBoardAttacks::CountBits(attack_mask);
        occupancy_index = (1 << rbits);

        for (int j = 0; j < occupancy_index; j++){
            occupancy =  BitBoardAttacks::setOccupancy(j, rbits, attack_mask);
            magic = (occupancy * rookMagics[i]) >> (64 - rookOccupancyBits[i]);

            rookAttacks[i][magic] = BitBoardAttacks::genRookAttacks(i, occupancy);
        }
    }
}


const U64 &LookupTable::getPawnAttacks(PieceColor color, int square) const {
    int index = color == P_WHITE ? _white : _black;
    return pawnAttacks[index][square];
}

const U64 &LookupTable::getPawnMoves(PieceColor color, int square) const {
    int index = color == P_WHITE ? _white : _black;
    return pawnMoves[index][square];
}

const U64 &LookupTable::getKnightAttacks(int square) const {
    return knightAttacks[square];
}

const U64 &LookupTable::getKingAttacks(int square) const {
    return kingAttacks[square];
}

const U64 &LookupTable::getRookAttacks(int square, uint64_t block) const {
    return rookAttacks[square][block];
}

const U64 &LookupTable::getBishopAttacks(int square, U64 block) const {
    return bishopAttacks[square][block];
}

const U64 &LookupTable::getRookMask(int square) const {
    return rookMask[square];
}

const U64 &LookupTable::getBishopMask(int square) const {
    return bishopMask[square];
}


