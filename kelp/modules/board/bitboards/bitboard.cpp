#include "bitboard.h"


BitBoard::BitBoard(LookupTable *lookupTable, Board *board) : BitBoardAttacks() ,BitBoardMoves(lookupTable, board) {
//    currentBitBoard = new uint64_t[3]; // 0 = white, 1 = black, 2 = all
//    currentPieceBitBoard = new uint64_t[6]; // 0 = king, 2 = pawn, 3 = knight, 4 = bishop, 5 = rook, 6 = queen
    this->board = board;
    this->lookupTable = lookupTable;
    updateBitBoards();
}

void BitBoard::SetBit(uint64_t *bitboard, int square) {
    *bitboard |= (1ULL << square);
}

void BitBoard::printBitBoard(uint64_t bitboard) {
    for (int i = 0; i < 8; i++) {
        std::cout << 8 - i << '\t' << '\t';
        for (int j = 0; j < 8; j++) {
            std::cout << getBit(bitboard, 8 * i + j) << '\t';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << '\t';
    for (int i = 0; i < 8; i++) {
        std::cout << "\t"  << char('a' + i) << ' ';
    }
    std::cout << std::endl << std::endl << "\t" << "\tBitBoard: " << bitboard << std::endl;
}


void BitBoard::setCurrentBitBoard() {
    PieceColor white = P_WHITE;
    PieceColor black = P_BLACK;

    // reset bitboards
    for (int i = 0; i < 3; i++) {
        currentBitBoard[i] = 0;
    }

    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 3; j++) {
            if (j == _white) {
                if (board->getPiece(i) != NONE && pieceColor(board->getPiece(i)) == white) {
                    SetBit(&currentBitBoard[j], i);
                }
            } else if (j == _black) {
                if (board->getPiece(i) != NONE && pieceColor(board->getPiece(i)) == black) {
                    SetBit(&currentBitBoard[j], i);
                }
            } else {
                if (board->getPiece(i) != NONE) {
                    SetBit(&currentBitBoard[j], i);
                }
            }
        }
    }
}

void BitBoard::setCurrentPieceBitBoard() {
    // reset bitboards
    for (int i = 0; i < 6; i++) {
        currentPieceBitBoard[i] = 0;
    }

    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 6; j++) {
            if (board->getPiece(i) != NONE && pieceType(board->getPiece(i)) == j + 1) {
                SetBit(&currentPieceBitBoard[j], i);
            }
        }
    }
}

U64 BitBoard::getCurrentBitBoard() {
    return currentBitBoard[2];
}

U64 BitBoard::getCurrentBitBoard(PieceColor color) {
    return color == P_WHITE ? currentBitBoard[0] : currentBitBoard[1];
}

U64 BitBoard::getCurrentBitBoard(PieceColor color, Piece pieceType) {
    int colorIndex = color == P_WHITE ? 0 : 1;
    U64 bitBoard = currentBitBoard[colorIndex] & currentPieceBitBoard[pieceType - 1];
    return bitBoard;
}

U64 BitBoard::getCurrentBitBoard(Piece pieceType) {
    return currentPieceBitBoard[pieceType - 1];
}

BitBoard::~BitBoard() {

}

void BitBoard::updateBitBoards() {
    setCurrentBitBoard();
    setCurrentPieceBitBoard();
}

