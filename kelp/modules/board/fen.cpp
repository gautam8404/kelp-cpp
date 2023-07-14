//
// Created by gautam on 19/2/23.
//

#include "fen.h"
#include "../constants.h"

std::map<char, Piece> PieceMap = {
        {'k', KING},
        {'p', PAWN},
        {'n', KNIGHT},
        {'b', BISHOP},
        {'r', ROOK},
        {'q', QUEEN}
};

std::map<int, char> PieceMapReverse = {
        {KING, 'k'},
        {PAWN, 'p'},
        {KNIGHT, 'n'},
        {BISHOP, 'b'},
        {ROOK, 'r'},
        {QUEEN, 'q'}
};

std::map<int, charPiece> PieceMapReverseChar = {
        {KING | P_WHITE, K},
        {PAWN | P_WHITE, P},
        {KNIGHT | P_WHITE, N},
        {BISHOP | P_WHITE, B},
        {ROOK | P_WHITE, R},
        {QUEEN | P_WHITE, Q},
        {KING | P_BLACK, k},
        {PAWN | P_BLACK, p},
        {KNIGHT | P_BLACK, n},
        {BISHOP | P_BLACK, b},
        {ROOK | P_BLACK, r},
        {QUEEN | P_BLACK, q}
};

std::map<char, int> PieceMapOR = {
        {'k', KING | P_BLACK},
        {'p', PAWN | P_BLACK},
        {'n', KNIGHT | P_BLACK},
        {'b', BISHOP | P_BLACK},
        {'r', ROOK | P_BLACK},
        {'q', QUEEN | P_BLACK},
        {'K', KING | P_WHITE},
        {'P', PAWN | P_WHITE},
        {'N', KNIGHT | P_WHITE},
        {'B', BISHOP | P_WHITE},
        {'R', ROOK | P_WHITE},
        {'Q', QUEEN | P_WHITE}
};

//std::string fen::fenString = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

fen::fen() {
    fenString = startingFenString;
}

fen::fen(std::string fenString) {
    this->fenString = fenString;
}

fen::~fen() {
}

void fen::parseFen(int *board, std::string fen) {
    int row = 0, col = 0;

    for (int i = 0; i < 64 ; i++) {
        board[i] = 0;
    }
    for (char &c: fen) {

        if (c == ' ') break;
        if (c == '/') {
            row++;
            col = 0;
            continue;
        }
        if (isdigit(c)) {
            int n = c - '0';
            col += n;
            for (int i = 0; i < n; i++) {
                board[row * 8 + i] = 0;
            }
        } else {
            board[row * 8 + col] = PieceMap[tolower(c)] | (isupper(c) ? P_WHITE : P_BLACK);
            col++;
        }
    }

}

void fen::genFen(int *board) {

}

void fen::saveGame() {

}

void fen::loadGame() {

}
