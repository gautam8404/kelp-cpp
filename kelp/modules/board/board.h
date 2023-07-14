#ifndef BOARD_H
#define BOARD_H

#include "../constants.h"







extern Move NULL_MOVE ;



class Board {
public:
    int *board;
    BoardInfo boardInfo;
    std::string unicodePieces[12] = {"♙", "♘", "♗", "♖", "♕", "♔", "♟︎", "♞", "♝", "♜", "♛", "♚"};

    Board();
    ~Board();

    void setPiece(int piece, int square);
    int getPiece(int square);
    std::string getPieceUnicode(int piece);
    char getPieceChar(int square);
    int getPieceInt(char piece);
    Move movePiece(int from, int to);
    void removePiece(int square);
    void printBoard();
    void makeMove(Move move);
    void unmakeMove(Move move);
    void printBoardUnicode();

    void loadFen(std::string fenString);

    void printBoard(int b[]);

    std::string squareToString(int square);

    int squareToSquare(std::string squareString);

    std::string moveToString(Move move);

    Move moveToMove(std::string moveString);

    Move
    formatMove(int source, int target, int moveScor, bool isCapture, bool isPromotion, int promotionPiece,
               bool isCastle,
               bool isEnPassant, int capturedPiece, int promotedPiece, std::string moveString);

    Move addMoveString(Move move);
};

#endif