#include "move_gen.h"
#include "../board/fen.h"

MovGen::MovGen(BitBoard *bitBoard, Board *board) {
    this->bitBoard = bitBoard;
    this->boardInfo = &board->boardInfo;
    this->board = board;
}


std::vector<Move> MovGen::getMoveList() {
    return moveList;
}

bool MovGen::isLegalMove(PieceColor turn, Move move) {
    U64 kingSquare = bitBoard->getCurrentBitBoard(turn, KING);

}

void MovGen::generateLegalMoves(int *board, PieceColor turn) {


}

void MovGen::generatePseudoLegalMoves(PieceColor turn) {
    moveList.clear();
    std::vector<Move> moves;
    moves = genPawnMoves(turn);
    moveList.insert(moveList.end(), moves.begin(), moves.end());
    moves = genKnightMoves(turn);
    moveList.insert(moveList.end(), moves.begin(), moves.end());
    moves = genBishopMoves(turn);
    moveList.insert(moveList.end(), moves.begin(), moves.end());
    moves = genRookMoves(turn);
    moveList.insert(moveList.end(), moves.begin(), moves.end());
    moves = genQueenMoves(turn);
    moveList.insert(moveList.end(), moves.begin(), moves.end());
    moves = genKingMoves(turn);
    moveList.insert(moveList.end(), moves.begin(), moves.end());
    moves = genCastleMoves(turn);
    moveList.insert(moveList.end(), moves.begin(), moves.end());
    moves = genEnPassantMoves(turn);
    moveList.insert(moveList.end(), moves.begin(), moves.end());
}



//bool MovGen::isLegalMove(PieceColor turn, Move move, int square) {
//    }

bool MovGen::isSquareAttacked(PieceColor turn, int square) {
    PieceColor enemy = turn == P_WHITE ? P_BLACK : P_WHITE;
    int turnIndex = turn == P_WHITE ? 0 : 1;
    int enemyIndex = enemy == P_WHITE ? 0 : 1;

    // pawn
    if (bitBoard->getPawnAttacks(enemy, square, bitBoard->getCurrentBitBoard()) & bitBoard->getCurrentBitBoard(turn, PAWN)) {
        return true;
    }
//     knight
    if (bitBoard->getKnightMoves(square, bitBoard->getCurrentBitBoard()) & bitBoard->getCurrentBitBoard(turn, KNIGHT)) {
        return true;
    }
    // bishop
    if (bitBoard->getBishopMoves(square, bitBoard->getCurrentBitBoard()) & bitBoard->getCurrentBitBoard(turn, BISHOP) ) {
        return true;
    }
    // rook
    if (bitBoard->getRookMoves(square, bitBoard->getCurrentBitBoard()) & bitBoard->getCurrentBitBoard(turn, ROOK)) {
        return true;
    }
    // queen
    if (bitBoard->getQueenMoves(square, bitBoard->getCurrentBitBoard()) & bitBoard->getCurrentBitBoard(turn, QUEEN)) {
        return true;
    }
    // king
    if (bitBoard->getKingMoves(square, bitBoard->getCurrentBitBoard()) & bitBoard->getCurrentBitBoard(turn, KING)) {
        return true;
    }
    return false;
}

bool MovGen::isSquareAttacked(PieceColor turn, int square, PieceColor attacker) {
    PieceColor enemy = turn == P_WHITE ? P_BLACK : P_WHITE;
    int turnIndex = turn == P_WHITE ? 0 : 1;
    int enemyIndex = enemy == P_WHITE ? 0 : 1;

    // pawn
    if (bitBoard->getPawnAttacks(enemy, square, bitBoard->getCurrentBitBoard()) & bitBoard->getCurrentBitBoard(turn, PAWN) && attacker == enemy) {
        return true;
    }
}

std::string MovGen::squareToString(int square) {
    std::string squareString;
    squareString += (char) (square % 8 + 97);
    squareString += (char) (square / 8 + 50);
    return squareString;
}

int MovGen::squareToSquare(std::string squareString) {
    int square = (squareString[0] - 97) + (squareString[1] - 50) * 8;
    return square;
}


std::string MovGen::moveToString(Move move) {
    std::string moveString = squareToString(move.source) + squareToString(move.target);
    if (move.isPromotion) {
        moveString += PieceMapReverseChar[move.promotionPiece];
    }
    return moveString;
}

Move MovGen::moveToMove(std::string moveString) {
    Move move;
    move.source = squareToSquare(moveString.substr(0, 2));
    move.target = squareToSquare(moveString.substr(2, 2));
    if (moveString.length() == 5) {
        move.isPromotion = true;
        move.promotionPiece = PieceMapOR[moveString[4]];
    }
    return move;
}

Move MovGen::formatMove(int source, int target, int moveScor = 0, bool isCapture = false, bool isPromotion = false, int promotionPiece = NONE, bool isCastle = false, bool isEnPassant = false, int capturedPiece = NONE, int promotedPiece = NONE, std::string moveString = "")
{
    Move move;
    move.source = source;
    move.target = target;
    move.moveScore = moveScor;
    move.isCapture = isCapture;
    move.isPromotion = isPromotion;
    move.promotionPiece = promotionPiece;
    move.isCastle = isCastle;
    move.isEnPassant = isEnPassant;
    move.capturedPiece = capturedPiece;
    move.promotedPiece = promotedPiece;
    move.moveString = moveString;
    return move;
}

Move MovGen::addMoveString(Move move) {
    move.moveString = squareToString(move.source) + squareToString(move.target);
    if (move.isPromotion) {
        move.moveString += PieceMapReverseChar[move.promotionPiece];
    }
    return move;
}

std::vector<Move> MovGen::genPawnMoves(PieceColor turn) {
    std::vector<Move> moves;
    int target, source, fwd;
    PieceColor enemy = turn == P_WHITE ? P_BLACK : P_WHITE;

    U64 pawns = bitBoard->getCurrentBitBoard(turn, PAWN);
    source = bitBoard->getLSB(pawns);
    fwd = ((source > 7 && source < 16) && turn == P_WHITE || (source > 47 && source < 56) && turn == P_BLACK) ? 16 : 8;
    target = source + (turn == P_WHITE ? fwd : -fwd);

    if (source == -1) {
        return moves;
    }



    // promotion
    if (board->board[target] == NONE) {
        if ((source > 55 && source < 64 && turn == P_WHITE) || (source > 7 && source < 16 && turn == P_BLACK)) {
            moves.push_back(addMoveString({source, target, 0, false, true, QUEEN | turn}));
            moves.push_back(addMoveString({source, target, 0, false, true, ROOK | turn}));
            moves.push_back(addMoveString({source, target, 0, false, true, BISHOP | turn}));
            moves.push_back(addMoveString({source, target, 0, false, true, KNIGHT | turn}));
        } else {
            // forward
            moves.push_back(addMoveString({source, target, 0, false, false, NONE}));
        }
    }

    // capture
    U64 captures = bitBoard->getPawnAttacks(turn, source, bitBoard->getCurrentBitBoard(enemy));
    while (captures) {
        target = bitBoard->getLSB(captures);
        moves.push_back(addMoveString({source, target, 0, true, false, NONE}));
        clearBit(captures, target);
    }

}

std::vector<Move> MovGen::genKnightMoves(PieceColor turn) {
    std::vector<Move> move;
    int target, source;

    U64 knights = bitBoard->getCurrentBitBoard(turn, KNIGHT);
    while (knights) {
        source = bitBoard->getLSB(knights);
        U64 moves = bitBoard->getKnightMoves(source, bitBoard->getCurrentBitBoard(turn));
        while (moves) {
            target = bitBoard->getLSB(moves);

            move.push_back(addMoveString({source, target, 0, false, false, NONE}));
            clearBit(moves, target);
        }
        clearBit(knights, source);
    }
    return move;
}

std::vector<Move> MovGen::genBishopMoves(PieceColor turn) {
    std ::vector<Move> move;
    int target, source;

    U64 bishops = bitBoard->getCurrentBitBoard(turn, BISHOP);
    while (bishops) {
        source = bitBoard->getLSB(bishops);
        U64 moves = bitBoard->getBishopMoves(source, bitBoard->getCurrentBitBoard(turn));
        while (moves) {
            target = bitBoard->getLSB(moves);

            move.push_back(addMoveString({source, target, 0, false, false, NONE}));
            clearBit(moves, target);
        }
        clearBit(bishops, source);
    }

    return move;
}

std::vector<Move> MovGen::genRookMoves(PieceColor turn) {
    std::vector<Move> move;
    int target, source;

    U64 rooks = bitBoard->getCurrentBitBoard(turn, ROOK);
    while (rooks) {
        source = bitBoard->getLSB(rooks);
        U64 moves = bitBoard->getRookMoves(source, bitBoard->getCurrentBitBoard(turn));
        while (moves) {
            target = bitBoard->getLSB(moves);

            move.push_back(addMoveString({source, target, 0, false, false, NONE}));
            clearBit(moves, target);
        }
        clearBit(rooks, source);
    }

    return move;
}

std::vector<Move> MovGen::genQueenMoves(PieceColor turn) {
    std::vector<Move> move;
    int target, source;

    U64 queens = bitBoard->getCurrentBitBoard(turn, QUEEN);
    while (queens) {
        source = bitBoard->getLSB(queens);
        U64 moves = bitBoard->getQueenMoves(source, bitBoard->getCurrentBitBoard(turn));
        while (moves) {
            target = bitBoard->getLSB(moves);

            move.push_back(addMoveString({source, target, 0, false, false, NONE}));
            clearBit(moves, target);
        }
        clearBit(queens, source);
    }

    return move;
}

std::vector<Move> MovGen::genKingMoves(PieceColor turn) {
    std::vector<Move> move;
    int target, source;

    U64 kings = bitBoard->getCurrentBitBoard(turn, KING);
    while (kings) {
        source = bitBoard->getLSB(kings);
        U64 moves = bitBoard->getKingMoves(source, bitBoard->getCurrentBitBoard(turn));
        while (moves) {
            target = bitBoard->getLSB(moves);

            move.push_back(addMoveString({source, target, 0, false, false, NONE}));
            clearBit(moves, target);
        }
        clearBit(kings, source);
    }

    return move;
}

std::vector<Move> MovGen::genCastleMoves(PieceColor turn) {
    int WROOK = ROOK | P_WHITE;
    int BROOK = ROOK | P_BLACK;
    int WKING = KING | P_WHITE;
    int BKING = KING | P_BLACK;



}

std::vector<Move> MovGen::genEnPassantMoves(PieceColor turn) {
    return std::vector<Move>();
}


bool MovGen::isInCheck(PieceColor turn) {
    int king = BitBoard::getLSB(bitBoard->getCurrentBitBoard(turn, KING));
    PieceColor enemy = turn == P_WHITE ? P_BLACK : P_WHITE;
    U64 enemyMoves = bitBoard->getAttackedSquares(bitBoard->getCurrentBitBoard(enemy));
    return enemyMoves & (1ULL << king);
}
//Move MovGen::bitToMove(PieceColor turn, U64 move) {
//    Move m;
//    int source = bitBoard->getLSB(move);
//    int target = bitBoard->getLSB(move >> 6);
//    m.source = source;
//    m.target = target;
//
//}
//U64 MovGen::getAttackedSquares(int *board, PieceColor turn) {
//    return 0;
//}
//
//U64 MovGen::getAttackedSquares(int *board, PieceColor turn, Piece pieceType) {
//    return 0;
//}
//
//U64 MovGen::getPawnAttackedSquares(int *board, PieceColor turn) {
//    return 0;
//}
