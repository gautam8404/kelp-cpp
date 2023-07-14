//
// Contains all code for precomputed attacks for pieces
// Only used Once at the start of the program
//

#include "bitboard_attacks.h"


BitBoardAttacks::BitBoardAttacks() = default;

U64 BitBoardAttacks::genPawnAttacks(PieceColor color, int square) {
    U64 pawn = 1ULL << square;
    U64 attacks = 0ULL;

    if (color == P_WHITE) {
        if ((pawn >> 9) & NOT_FILE_H) attacks |= (pawn >> 9);
        if ((pawn >> 7) & NOT_FILE_A) attacks |= (pawn >> 7);
    } else {
        if ((pawn << 9) & NOT_FILE_A) attacks |= (pawn << 9);
        if ((pawn << 7) & NOT_FILE_H) attacks |= (pawn << 7);
    }
    return attacks;
}

U64 BitBoardAttacks::genPawnMaskMoves(PieceColor color, int square) {
    U64 pawn = 1ULL << square;
    U64 moves = 0ULL;

    if (square < 8 || square > 55) return moves;

    if (color == P_WHITE) {
        if (square >= 48) {
            moves |= (pawn >> 8);
            moves |= (pawn >> 16);
        } else {
            moves |= (pawn >> 8);
        }
    } else {
        if (square <= 15) {
            moves |= (pawn << 8);
            moves |= (pawn << 16);
        } else {
            moves |= (pawn << 8);
        }
    }
    return moves;
}

U64 BitBoardAttacks::genKnightAttacks(int square) {
    U64 knight = 1ULL << square;
    U64 attacks = 0ULL;

    attacks |= ((knight >> 17) & NOT_FILE_H) ? (knight >> 17) : 0ULL;
    attacks |= ((knight >> 15) & NOT_FILE_A) ? (knight >> 15) : 0ULL;
    attacks |= ((knight >> 10) & (NOT_FILE_GH & NOT_FILE_H)) ? (knight >> 10) : 0ULL;
    attacks |= ((knight >> 6) & (NOT_FILE_AB & NOT_FILE_H)) ? (knight >> 6) : 0ULL;
    attacks |= ((knight << 17) & NOT_FILE_A) ? (knight << 17) : 0ULL;
    attacks |= ((knight << 15) & NOT_FILE_H) ? (knight << 15) : 0ULL;
    attacks |= ((knight << 10) & (NOT_FILE_AB & NOT_FILE_A)) ? (knight << 10) : 0ULL;
    attacks |= ((knight << 6) & (NOT_FILE_GH & NOT_FILE_A)) ? (knight << 6) : 0ULL;

    return attacks;
}

U64 BitBoardAttacks::genKingAttacks(int square) {
    U64 king = 1ULL << square;
    U64 attacks = 0ULL;

    attacks |= ((king >> 9) & NOT_FILE_H) ? (king >> 9) : 0ULL;
    attacks |= ((king >> 8)) ? (king >> 8) : 0ULL;
    attacks |= ((king >> 7) & NOT_FILE_A) ? (king >> 7) : 0ULL;
    attacks |= ((king >> 1) & NOT_FILE_H) ? (king >> 1) : 0ULL;
    attacks |= ((king << 9) & NOT_FILE_A) ? (king << 9) : 0ULL;
    attacks |= ((king << 8)) ? (king << 8) : 0ULL;
    attacks |= ((king << 7) & NOT_FILE_H) ? (king << 7) : 0ULL;
    attacks |= ((king << 1) & NOT_FILE_A) ? (king << 1) : 0ULL;

    return attacks;
}

U64 BitBoardAttacks::genRookAttacks(int square, uint64_t block) {
    U64 attacks = 0ULL;
    int rank, file;
    int t_rank = square / 8;
    int t_file = square % 8;

    block |= (1ULL << square);

    for (rank = t_rank + 1; rank < 8; rank++) {
        attacks |= (1ULL << (rank * 8 + t_file));
        if (getBit(block, (rank * 8 + t_file))) break;
    }
    for (rank = t_rank - 1; rank >= 0; rank--) {
        attacks |= (1ULL << (rank * 8 + t_file));
        if (getBit(block, (rank * 8 + t_file))) break;
    }
    for (file = t_file + 1; file < 8; file++) {
        attacks |= (1ULL << (t_rank * 8 + file));
        if (getBit(block, (t_rank * 8 + file))) break;
    }
    for (file = t_file - 1; file >= 0; file--) {
        attacks |= (1ULL << (t_rank * 8 + file));
        if (getBit(block, (t_rank * 8 + file))) break;
    }
    return attacks;
}

U64 BitBoardAttacks::genBishopAttacks(int square, uint64_t block) {
    U64 attacks = 0ULL;
    int rank, file;
    int t_rank = square / 8;
    int t_file = square % 8;


    for (rank = t_rank + 1, file = t_file + 1; rank < 8 && file < 8; rank++, file++) {
        attacks |= (1ULL << (rank * 8 + file));
        if (getBit(block, (rank * 8 + file))) break;
    }
    for (rank = t_rank + 1, file = t_file - 1; rank < 8 && file >= 0; rank++, file--) {
        attacks |= (1ULL << (rank * 8 + file));
        if (getBit(block, (rank * 8 + file))) break;
    }
    for (rank = t_rank - 1, file = t_file + 1; rank >= 0 && file < 8; rank--, file++) {
        attacks |= (1ULL << (rank * 8 + file));
        if (getBit(block, (rank * 8 + file))) break;
    }
    for (rank = t_rank - 1, file = t_file - 1; rank >= 0 && file >= 0; rank--, file--) {
        attacks |= (1ULL << (rank * 8 + file));
        if (getBit(block, (rank * 8 + file))) break;
    }
    return attacks;
}

U64 BitBoardAttacks::genRookMask(int square) {
    U64 attacks = 0ULL;
    int rank, file;
    int t_rank = square / 8;
    int t_file = square % 8;

    for (rank = t_rank + 1; rank < 7; rank++) {
        attacks |= (1ULL << (rank * 8 + t_file));
    }
    for (rank = t_rank - 1; rank >= 1; rank--) {
        attacks |= (1ULL << (rank * 8 + t_file));
    }
    for (file = t_file + 1; file < 7; file++) {
        attacks |= (1ULL << (t_rank * 8 + file));
    }
    for (file = t_file - 1; file >= 1; file--) {
        attacks |= (1ULL << (t_rank * 8 + file));
    }
    return attacks;
}

U64 BitBoardAttacks::genBishopMask(int square) {
    U64 attacks = 0ULL;
    int rank, file;
    int t_rank = square / 8;
    int t_file = square % 8;

    for (rank = t_rank + 1, file = t_file + 1; rank < 7 && file < 7; rank++, file++) {
        attacks |= (1ULL << (rank * 8 + file));
    }
    for (rank = t_rank + 1, file = t_file - 1; rank < 7 && file >= 1; rank++, file--) {
        attacks |= (1ULL << (rank * 8 + file));
    }
    for (rank = t_rank - 1, file = t_file + 1; rank >= 1 && file < 7; rank--, file++) {
        attacks |= (1ULL << (rank * 8 + file));
    }
    for (rank = t_rank - 1, file = t_file - 1; rank >= 1 && file >= 1; rank--, file--) {
        attacks |= (1ULL << (rank * 8 + file));
    }
    return attacks;
}

U64 BitBoardAttacks::setOccupancy(int index, int bitsCount, U64 attack_mask){
    U64 occupancy = 0ULL;
    U64 temp = attack_mask;
    for (int i = 0; i < bitsCount; i++) {
        int square = getLSB(temp);
        clearBit(temp, square);
        if (index & (1 << i)) {
            setBit(occupancy, square);
        }
    }
    return occupancy;
}


inline int BitBoardAttacks::getLSB(U64 bitboard) {
        if (!bitboard) {
            return -1;
        }
        return CountBits((bitboard & -bitboard) - 1);
}

int BitBoardAttacks::CountBits(U64 bitboard) {
    int bits;
    for (bits = 0; bitboard; bits++) {
        bitboard &= bitboard - 1;
    }
    return bits;
}

inline void BitBoardAttacks::SetBit(U64 &bitboard, int square) {
    bitboard |= (1ULL << square);
}

inline void BitBoardAttacks::ClearBit(U64 &bitboard, int square) {
    bitboard &= ~(1ULL << square);
}

inline bool BitBoardAttacks::GetBit(U64 bitboard, int square) {
    return (bitboard >> square) & 1;
}






