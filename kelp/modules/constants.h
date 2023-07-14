//
// Created by gautam on 19/2/23.
//

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdint>

typedef uint64_t U64;
#define getBit(bitboard, square) ((bitboard >> square) & 1ULL)
#define setBit(bitboard, square) (bitboard |= (1ULL << square))
#define clearBit(bitboard, square) (bitboard &= ~(1ULL << square))
#define popBit(bitboard) (bitboard &= (bitboard - 1))


#define pieceType(piece) ((piece) & 0x7)
#define pieceColor(piece) ((piece) & 0x18)

//enum Piece {
//    NONE, KING, PAWN, KNIGHT, BISHOP, ROOK, QUEEN
//};
enum Piece {
    NONE, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING
};


enum PieceColor {
    P_WHITE=8, P_BLACK=16
};

enum BoardState {
    ACTIVE=1, LEGAL, ILLEGAL, DEFAULT, ALL
};

enum Castle {
    W_KING_SIDE=1, W_QUEEN_SIDE=2, B_KING_SIDE=4, B_QUEEN_SIDE=8
};

enum charPiece {
    K='K', P='P', N='N', B='B', R='R', Q='Q', k='k', p='p', n='n', b='b', r='r', q='q'
};

const unsigned int screenWidth = 1200;
const unsigned int screenHeight = 800;
const unsigned int BoardMargin = 0;


enum positions {
    a8 , b8, c8, d8, e8, f8, g8, h8,
    a7 ,b7, c7, d7, e7, f7, g7, h7,
    a6 , b6, c6, d6, e6, f6, g6, h6,
    a5 , b5, c5, d5, e5, f5, g5, h5,
    a4 , b4, c4, d4, e4, f4, g4, h4,
    a3 , b3, c3, d3, e3, f3, g3, h3,
    a2 , b2, c2, d2, e2, f2, g2, h2,
    a1 , b1, c1, d1, e1, f1, g1, h1
};

struct Move {
    int source;
    int target;
    int moveScore;
    bool isCapture;
    bool isPromotion;
    int promotionPiece;
    bool isCastle;
    bool isEnPassant;
    int capturedPiece;
    int promotedPiece;
    std::string moveString;
};

struct BoardInfo {
    int enPassantSquare;
    int castleRights;
    PieceColor turn;
};

const U64 FILE_B = 0x0202020202020202ULL;
const U64 FILE_C = 0x0404040404040404ULL;
const U64 FILE_D = 0x0808080808080808ULL;
const U64 FILE_E = 0x1010101010101010ULL;
const U64 FILE_F = 0x2020202020202020ULL;
const U64 FILE_G = 0x4040404040404040ULL;

const U64 FILE_A = 0x0101010101010101ULL;
const U64 FILE_H = 0x8080808080808080ULL;
const U64 FILE_AB = 0x0303030303030303ULL;
const U64 FILE_GH = 0xC0C0C0C0C0C0C0C0ULL;
const U64 NOT_FILE_A = ~FILE_A;
const U64 NOT_FILE_H = ~FILE_H;
const U64 NOT_FILE_AB = ~FILE_AB;
const U64 NOT_FILE_GH = ~FILE_GH;

const U64 RANK_2 = 0x000000000000FF00ULL;
const U64 RANK_7 = 0x00FF000000000000ULL;

// Occupancies

const U64 white_occ = 0x000000000000FFFFULL;
const U64 black_occ = 0xFFFF000000000000ULL;
const U64 all_occ = 0xFFFFFFFFFFFFFFFFULL;

const U64 white_pawn_occ = 0x000000000000FF00ULL;
const U64 black_pawn_occ = 0x00FF000000000000ULL;
const U64 white_knight_occ = 0x0000000000000042ULL;
const U64 black_knight_occ = 0x4200000000000000ULL;
const U64 white_bishop_occ = 0x0000000000000024ULL;
const U64 black_bishop_occ = 0x2400000000000000ULL;
const U64 white_rook_occ = 0x0000000000000081ULL;
const U64 black_rook_occ = 0x8100000000000000ULL;
const U64 white_queen_occ = 0x0000000000000010ULL;
const U64 black_queen_occ = 0x1000000000000000ULL;
const U64 white_king_occ = 0x0000000000000008ULL;
const U64 black_king_occ = 0x0800000000000000ULL;

// Score values for each piece
const int pawn_score = 100;
const int knight_score = 320;
const int bishop_score = 330;
const int rook_score = 500;
const int queen_score = 900;
const int king_score = 20000;



const int rookOccupancyBits[64] = {
        12, 11, 11, 11, 11, 11, 11, 12,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        12, 11, 11, 11, 11, 11, 11, 12
};

const int bishopOccupancyBits[64] = {
        6, 5, 5, 5, 5, 5, 5, 6,
        5, 5, 5, 5, 5, 5, 5, 5,
        5, 5, 7, 7, 7, 7, 5, 5,
        5, 5, 7, 9, 9, 7, 5, 5,
        5, 5, 7, 9, 9, 7, 5, 5,
        5, 5, 7, 7, 7, 7, 5, 5,
        5, 5, 5, 5, 5, 5, 5, 5,
        6, 5, 5, 5, 5, 5, 5, 6
};

// Magic numbers for rook and bishop attacks

const U64 rookMagics[64] = {
        0x8a80104000800020ULL,
        0x140002000100040ULL,
        0x2801880a0017001ULL,
        0x100081001000420ULL,
        0x200020010080420ULL,
        0x3001c0002010008ULL,
        0x8480008002000100ULL,
        0x2080088004402900ULL,
        0x800098204000ULL,
        0x2024401000200040ULL,
        0x100802000801000ULL,
        0x120800800801000ULL,
        0x208808088000400ULL,
        0x2802200800400ULL,
        0x2200800100020080ULL,
        0x801000060821100ULL,
        0x80044006422000ULL,
        0x100808020004000ULL,
        0x12108a0010204200ULL,
        0x140848010000802ULL,
        0x481828014002800ULL,
        0x8094004002004100ULL,
        0x4010040010010802ULL,
        0x20008806104ULL,
        0x100400080208000ULL,
        0x2040002120081000ULL,
        0x21200680100081ULL,
        0x20100080080080ULL,
        0x2000a00200410ULL,
        0x20080800400ULL,
        0x80088400100102ULL,
        0x80004600042881ULL,
        0x4040008040800020ULL,
        0x440003000200801ULL,
        0x4200011004500ULL,
        0x188020010100100ULL,
        0x14800401802800ULL,
        0x2080040080800200ULL,
        0x124080204001001ULL,
        0x200046502000484ULL,
        0x480400080088020ULL,
        0x1000422010034000ULL,
        0x30200100110040ULL,
        0x100021010009ULL,
        0x2002080100110004ULL,
        0x202008004008002ULL,
        0x20020004010100ULL,
        0x2048440040820001ULL,
        0x101002200408200ULL,
        0x40802000401080ULL,
        0x4008142004410100ULL,
        0x2060820c0120200ULL,
        0x1001004080100ULL,
        0x20c020080040080ULL,
        0x2935610830022400ULL,
        0x44440041009200ULL,
        0x280001040802101ULL,
        0x2100190040002085ULL,
        0x80c0084100102001ULL,
        0x4024081001000421ULL,
        0x20030a0244872ULL,
        0x12001008414402ULL,
        0x2006104900a0804ULL,
        0x1004081002402ULL
};

const U64 bishopMagics[64] = {
        0x40040844404084ULL,
        0x2004208a004208ULL,
        0x10190041080202ULL,
        0x108060845042010ULL,
        0x581104180800210ULL,
        0x2112080446200010ULL,
        0x1080820820060210ULL,
        0x3c0808410220200ULL,
        0x4050404440404ULL,
        0x21001420088ULL,
        0x24d0080801082102ULL,
        0x1020a0a020400ULL,
        0x40308200402ULL,
        0x4011002100800ULL,
        0x401484104104005ULL,
        0x801010402020200ULL,
        0x400210c3880100ULL,
        0x404022024108200ULL,
        0x810018200204102ULL,
        0x4002801a02003ULL,
        0x85040820080400ULL,
        0x810102c808880400ULL,
        0xe900410884800ULL,
        0x8002020480840102ULL,
        0x220200865090201ULL,
        0x2010100a02021202ULL,
        0x152048408022401ULL,
        0x20080002081110ULL,
        0x4001001021004000ULL,
        0x800040400a011002ULL,
        0xe4004081011002ULL,
        0x1c004001012080ULL,
        0x8004200962a00220ULL,
        0x8422100208500202ULL,
        0x2000402200300c08ULL,
        0x8646020080080080ULL,
        0x80020a0200100808ULL,
        0x2010004880111000ULL,
        0x623000a080011400ULL,
        0x42008c0340209202ULL,
        0x209188240001000ULL,
        0x400408a884001800ULL,
        0x110400a6080400ULL,
        0x1840060a44020800ULL,
        0x90080104000041ULL,
        0x201011000808101ULL,
        0x1a2208080504f080ULL,
        0x8012020600211212ULL,
        0x500861011240000ULL,
        0x180806108200800ULL,
        0x4000020e01040044ULL,
        0x300000261044000aULL,
        0x802241102020002ULL,
        0x20906061210001ULL,
        0x5a84841004010310ULL,
        0x4010801011c04ULL,
        0xa010109502200ULL,
        0x4a02012000ULL,
        0x500201010098b028ULL,
        0x8040002811040900ULL,
        0x28000010020204ULL,
        0x6000020202d0240ULL,
        0x8918844842082200ULL,
        0x4010011029020020ULL
};



#endif //CONSTANTS_H
