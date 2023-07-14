#ifndef BITBOARD_H
#define BITBOARD_H
#include "../../constants.h"
#include "../board.h"
#include "lookupTable/lookup_tables.h"
#include "bitboard_attacks.h"
#include "bitboard_moves.h"

//#define U64 uint64_t


class BitBoard : public BitBoardAttacks, public BitBoardMoves {
public:
    BitBoard(LookupTable *lookupTable, Board *board);
    ~BitBoard();



    void SetBit(U64 *bitboard, int square);
    void printBitBoard(U64 bitboard);
    void setCurrentBitBoard();
    void setCurrentPieceBitBoard();
    U64 getCurrentBitBoard();
    U64 getCurrentBitBoard(PieceColor color);
    U64 getCurrentBitBoard(PieceColor color, Piece pieceType);
    U64 getCurrentBitBoard(Piece pieceType);
    void updateBitBoards();



private:
    Board *board;
    LookupTable *lookupTable;
    U64 bitBoards[12];
    U64 occupancies[3];
    PieceColor turn;
    int enPassantSquare;
    int castleRights;

    U64 currentBitBoard[3]; // 0 = white, 1 = black
    U64 currentPieceBitBoard[6]; // 0 - 5 = white, 6 - 11 = black, 0 = King, 1 = Pawn, 2 = Knight, 3 = Bishop, 4 = Rook, 5 = QueenZ
};


#endif //BITBOARD_H