#include "board.h"
#include "fen.h"
#include <iostream>

Move NULL_MOVE = {-1, -1, 0, false, false, false, false, 0, 0};


Board::Board() {
    board = new int[64];
    for (int i = 0; i < 64; i++) {
        board[i] = NONE;
    }
    fen *f = new fen(); f->parseFen(board);
    delete f;
}

Board::~Board() {
    delete[] board;
}

void Board::setPiece(int piece, int square) {
    board[square] = piece;
}

int Board::getPiece(int square) {
    return board[square];
}


char Board::getPieceChar(int piece) {
    int type =  pieceType(piece);
    int color = pieceColor(piece);

    return color == P_WHITE ? toupper(PieceMapReverse[type]) : tolower(PieceMapReverse[type]);
}

std::string Board::getPieceUnicode(int piece) {
    int type =  pieceType(piece);
    int color = pieceColor(piece);
    if (type == NONE) {
        return ".";
    }
    type = type - 1;
    return color == P_BLACK ? unicodePieces[type] : unicodePieces[type + 6];
}

int Board::getPieceInt(char piece) {
    int color = isupper(piece) ? P_WHITE : P_BLACK;
    int type = PieceMap[tolower(piece)];
    return type | color;
}

Move Board::movePiece(int from, int to) {
    Move move{from, to, 0, false};

    if (pieceType(board[from]) == NONE) {
        return NULL_MOVE;
    }
    if (from == to) {
        return NULL_MOVE;
    }
    if (pieceType(board[to]) != NONE) {
        move.isCapture = true;
        move.capturedPiece = board[to];
    }

    int piece = board[from];
    board[from] = NONE;
    board[to] = piece;

    return move;
}

void Board::removePiece(int square) {
    board[square] = NONE;
}

void Board::printBoard() {
    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0) {
            std::cout << 8 - (i / 8) << '\t' << '\t';
        }
        std::cout << getPieceChar(board[i]) << "\t";
        if ((i + 1) % 8 == 0) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
    std::cout << '\t';
    for (int i = 0; i < 8; i++) {
        std::cout << "\t"  << char('a' + i) << ' ';
    }
    std::cout << std::endl << std::endl;
}
void Board::printBoard(int b[]) {
    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0) {
            std::cout << 8 - (i / 8) << '\t' << '\t';
        }
        std::cout << getPieceChar(b[i]) << " ";
        if ((i + 1) % 8 == 0) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
    std::cout << '\t';
    for (int i = 0; i < 8; i++) {
        std::cout << "\t"  << char('a' + i) << ' ';
    }
    std::cout << std::endl << std::endl;
}



void Board::printBoardUnicode() {
#ifdef WIN64
    std::cout << "Unicode printing is not supported on Windows" << std::endl;
    printBoard();
    return;
#endif
    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0) {
            std::cout << 8 - (i / 8) << '\t' << '\t';
        }
        std::cout << getPieceUnicode(board[i]) << "\t";
        if ((i + 1) % 8 == 0) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
    std::cout << '\t';
    for (int i = 0; i < 8; i++) {
        std::cout << "\t"  << char('a' + i) << ' ';
    }
    std::cout << std::endl << std::endl;
}

void Board::loadFen(std::string fenString) {
    fen *f = new fen();
    f->parseFen(board, fenString);
    delete f;
}

std::string Board::squareToString(int square) {
    std::string squareString;
    squareString += (char) (square % 8 + 97);
    squareString += (char) (square / 8 + 50);
    return squareString;
}

int Board::squareToSquare(std::string squareString) {
    int square = (squareString[0] - 97) + (squareString[1] - 50) * 8;
    return square;
}


std::string Board::moveToString(Move move) {
    std::string moveString = squareToString(move.source) + squareToString(move.target);
    if (move.isPromotion) {
        moveString += PieceMapReverseChar[move.promotionPiece];
    }
    return moveString;
}

Move Board::moveToMove(std::string moveString) {
    Move move;
    move.source = squareToSquare(moveString.substr(0, 2));
    move.target = squareToSquare(moveString.substr(2, 2));
    if (moveString.length() == 5) {
        move.isPromotion = true;
        move.promotionPiece = PieceMapOR[moveString[4]];
    }
    return move;
}

Move Board::formatMove(int source, int target, int moveScor = 0, bool isCapture = false, bool isPromotion = false, int promotionPiece = NONE, bool isCastle = false, bool isEnPassant = false, int capturedPiece = NONE, int promotedPiece = NONE, std::string moveString = "")
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

Move Board::addMoveString(Move move) {
    move.moveString = squareToString(move.source) + squareToString(move.target);
    if (move.isPromotion) {
        move.moveString += PieceMapReverseChar[move.promotionPiece];
    }
    return move;
}

void Board::makeMove(Move move) {
    if (move.isCastle) {
        if (move.target == 62) {
            movePiece(63, 61);
        } else if (move.target == 58) {
            movePiece(56, 59);
        } else if (move.target == 6) {
            movePiece(7, 5);
        } else if (move.target == 2) {
            movePiece(0, 3);
        }
    }
    if (move.isEnPassant) {
        if (move.target == 33) {
            removePiece(41);
        } else if (move.target == 31) {
            removePiece(39);
        } else if (move.target == 24) {
            removePiece(32);
        } else if (move.target == 22) {
            removePiece(30);
        }
    }
    if (move.isPromotion) {
        board[move.target] = move.promotionPiece;
    } if (move.isCapture) {
        removePiece(move.target);
        movePiece(move.source, move.target);
    } else {
        movePiece(move.source, move.target);
    }

}

void Board::unmakeMove(Move move) {
    if (move.isCastle) {
        if (move.target == 62) {
            movePiece(61, 63);
        } else if (move.target == 58) {
            movePiece(59, 56);
        } else if (move.target == 6) {
            movePiece(5, 7);
        } else if (move.target == 2) {
            movePiece(3, 0);
        }
    }
    if (move.isEnPassant) {
        if (move.target == 33) {
            addPiece(41, PAWN, BLACK);
        } else if (move.target == 31) {
            addPiece(39, PAWN, BLACK);
        } else if (move.target == 24) {
            addPiece(32, PAWN, WHITE);
        } else if (move.target == 22) {
            addPiece(30, PAWN, WHITE);
        }
    }
    if (move.isPromotion) {
        board[move.target] = PAWN;
    } if (move.isCapture) {
        setPiece(move.capturedPiece, move.target);
        movePiece(move.target, move.source);
    } else {
        movePiece(move.target, move.source);
    }
}

//Move Board::makeMove(Move move) {
//
//    return Move();
//}
//
//void Board::unmakeMove(Move move) {
//
//}

