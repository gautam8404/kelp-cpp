//
// Created by gautam on 19/2/23.
//

#ifndef FEN_H
#define FEN_H

#include <string>
#include "../constants.h"

extern std::map<char, Piece> PieceMap ;
extern std::map<int, char> PieceMapReverse;
extern std::map<int, charPiece> PieceMapReverseChar;
extern std::map<char, int> PieceMapOR;
//extern std::map<int,

static std::string startingFenString = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
class fen {


    std::string fenString;

public:
    fen();
    fen(std::string fenString);
    ~fen();
    void parseFen(int *board, std::string fenString = startingFenString);
    void genFen(int *board);
    void saveGame();
    void loadGame();
};


#endif //FEN_H
