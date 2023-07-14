//
// Created by gautam on 27/2/23.
//

#include "kelp.h"
//#include "modules/board/board.h"
//#include "modules/move_gen/move_gen.h"
//#include "modules/board/bitboards/bitboard.h"


kelp::kelp() {
    init();
}

kelp::~kelp() {
    delete bitBoard;
    delete lookupTable;
    delete board;
    delete moveGen;
    delete[] boardArray;
}

void kelp::init() {
    lookupTable = new LookupTable();
    lookupTable->populate();
    board = new Board();
    bitBoard = new BitBoard(lookupTable, board);
    moveGen = new MovGen(bitBoard, board);
    boardArray = new int[64];
}

std::vector<Move> kelp::getLegalMoves(PieceColor side) {
    moveGen->generatePseudoLegalMoves(side);
    std::vector<Move> moves = moveGen->getMoveList();

    for (int i = 0; i < moves.size(); i++) {
        board->makeMove(moves[i]);
        bitBoard->updateBitBoards();
        if (moveGen->isInCheck(side)) {
            moves.erase(moves.begin() + i);
            i--;
        }
        board->unmakeMove(moves[i]);
        bitBoard->updateBitBoards();
    }
}
