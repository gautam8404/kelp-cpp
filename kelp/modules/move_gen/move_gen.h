#include <vector>

#include "../constants.h"
#include "../board/bitboards/bitboard.h"

class MovGen {
private:
    std::vector<Move> moveList;
    std::vector<Move> legalMoveList;
    BitBoard *bitBoard;
    BoardInfo *boardInfo;
    Board *board;


public:
    MovGen(BitBoard *bitBoard, Board *board);
    std::vector<Move> getMoveList();

    void generateLegalMoves(int *board, PieceColor turn);
    bool isLegalMove(PieceColor turn, Move move);
    bool isSquareAttacked(PieceColor turn, int square);

    std::vector<Move> genPawnMoves(PieceColor turn);
    std::vector<Move> genKnightMoves( PieceColor turn);
    std::vector<Move> genBishopMoves(PieceColor turn);
    std::vector<Move> genRookMoves(PieceColor turn);
    std::vector<Move> genQueenMoves(PieceColor turn);
    std::vector<Move> genKingMoves(PieceColor turn);
    std::vector<Move> genCastleMoves(PieceColor turn);
    std::vector<Move> genEnPassantMoves(PieceColor turn);



//    U64 getAttackedSquares(int *board, PieceColor turn);
//    U64 getAttackedSquares(int *board, PieceColor turn, Piece pieceType);


    bool isSquareAttacked(PieceColor turn, int square, PieceColor attacker);

    Move bitToMove(int *board, PieceColor turn, U64 move);

    std::string squareToString(int square);

    std::string moveToString(Move move);

    int squareToSquare(std::string squareString);

    Move moveToMove(std::string moveString);

    Move addMoveString(Move move);

    Move
    formatMove(int source, int target, int moveScor, bool isCapture, bool isPromotion, int promotionPiece,
               bool isCastle,
               bool isEnPassant, int capturedPiece, int promotedPiece, std::string moveString);

    void generatePseudoLegalMoves(PieceColor turn);

    bool isInCheck(PieceColor turn);
};