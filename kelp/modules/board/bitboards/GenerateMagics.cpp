// This file does not belong to this project. it a separate file only used to generate magic numbers
// reference/credit: https://www.chessprogramming.org/Looking_for_Magics

#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <cstdint>

typedef uint64_t U64;

#define getBit(bitboard, square) ((bitboard >> square) & 1ULL)
#define setBit(bitboard, square) (bitboard |= (1ULL << square))
#define clearBit(bitboard, square) (bitboard &= ~(1ULL << square))

//#include "bitboard_attacks.h"

using namespace std;

const int BitTable[64] = {
        63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
        51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
        26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
        58, 20, 37, 17, 36, 8
};

int rookOccupancyBits[64] = {
        12, 11, 11, 11, 11, 11, 11, 12,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        12, 11, 11, 11, 11, 11, 11, 12
};

int bishopOccupancyBits[64] = {
        6, 5, 5, 5, 5, 5, 5, 6,
        5, 5, 5, 5, 5, 5, 5, 5,
        5, 5, 7, 7, 7, 7, 5, 5,
        5, 5, 7, 9, 9, 7, 5, 5,
        5, 5, 7, 9, 9, 7, 5, 5,
        5, 5, 7, 7, 7, 7, 5, 5,
        5, 5, 5, 5, 5, 5, 5, 5,
        6, 5, 5, 5, 5, 5, 5, 6
};


U64 get_random_number() {
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<U64> dis(0, UINT64_MAX);
    return dis(gen);
}

U64 get_random_fewBits() {
    return get_random_number() & get_random_number() & get_random_number();
}


int CountBits(U64 i) {
    int count = 0;
    for (count = 0; i; count++){
        i &= i - 1;
    }
    return count;
}

int getLSB(U64 bitboard) {
    if (!bitboard) {
        return -1;
    }
    return CountBits((bitboard & -bitboard) - 1);
}

U64 genBishopMask(int square) {
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

U64 genRookMask(int square) {
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

U64 genBishopAttacks(int square, uint64_t block) {
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


U64 genRookAttacks(int square, uint64_t block) {
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


int pop_1st_bit(U64 *bb) {
    U64 b = *bb ^ (*bb - 1);
    unsigned int fold = (unsigned) ((b & 0xffffffff) ^ (b >> 32));
    *bb &= (*bb - 1);
    return BitTable[(fold * 0x783a9b23) >> 26];
}

U64 index_to_uint64(int index, int bits, U64 m) {
    int i, j;
    U64 result = 0ULL;
    for(i = 0; i < bits; i++) {
        j = pop_1st_bit(&m);
        if(index & (1 << i)) result |= (1ULL << j);
    }
    return result;
}

U64 setOccupancy(int index, int bitsCount, U64 attack_mask){
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

// magics are stored as constants this functions is only used to generate them
U64 GenerateMagicNumbers(int square, int bits, int bishop) {
    U64 occupancies[4096] , attacks[4096], used[4096];
    U64 attack_mask, magic, occupancy, attack;
    bool fail;

    attack_mask = bishop ? genBishopMask(square) : genRookMask(square);
    int occupancy_count = 1 << bits;

    for (int i = 0; i < occupancy_count; i++) {
        occupancies[i] = setOccupancy(i, bits, attack_mask);
        attacks[i] = bishop ? genBishopAttacks(square, occupancies[i]) : genRookAttacks(square, occupancies[i]);
    }

    for (int i = 0; i < 1000000000; i++){
        magic = get_random_fewBits();

        if (CountBits((attack_mask * magic) & 0xFF00000000000000) < 6) continue;
        for (int j = 0; j < 4096; j++) used[j] = 0ULL;

        for (int j = 0, fail = false; !fail && j < occupancy_count; j++) {
            int index = (int) (occupancies[j] * magic) >> (64 - bits);
            attack = attacks[j];

            if (used[index] == 0ULL) used[index] = attack;
            else if (used[index] != attack) fail = true;
        }
        if (!fail) return magic;
    }
    return 0ULL;
}


int main() {
    int sq;

    cout << "const U64 rookMagics[64] = {" << endl;
    for (sq = 0; sq < 64; sq++) {
        cout << "0x" << hex << GenerateMagicNumbers(sq, rookOccupancyBits[sq], 0) << "ULL, " << endl;
    }
    cout << "};" << endl << endl;

    cout << "const U64 bishopMagics[64] = {" << endl;
    for (sq = 0; sq < 64; sq++) {
        cout << "0x" << hex << GenerateMagicNumbers(sq, bishopOccupancyBits[sq], 1) << "ULL, " << endl;
    }
    cout << "};" << endl << endl;

}
