//
// Created by gautam on 27/2/23.
//

#ifndef CHESS_ENGINE_KEPLER_H
#define CHESS_ENGINE_KEPLER_H

#include <vector>
#include "./modules/constants.h"
#include "./modules/move_gen/move_gen.h"
#include "./modules/board/bitboards/bitboard.h"


class kelp {
public:
    kelp();
    ~kelp();
    int* getBoard();
    void setBoard(int* board);
    void printBoard();
    void init();

    std::vector<Move> getLegalMoves(int* board, int side);

private:

    BitBoard *bitBoard;
    LookupTable *lookupTable;
    Board *board;
    MovGen *moveGen;
    int *boardArray;

    std::vector<Move> getLegalMoves(PieceColor side);
};


#endif //CHESS_ENGINE_KEPLER_H
