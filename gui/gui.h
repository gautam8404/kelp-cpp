#ifndef GUI_H
#define GUI_H

#include "raylib.h"
#include "../kelp/modules/constants.h"


class GUI {
private:
    std::map<char, Texture2D> pieceTextures;
    int activePiece = -1;
    int activeSquare = -1;
    bool isDragging = false;
public:
    int BoardSize = screenHeight - 2 * BoardMargin;
    int boardX = (screenWidth - BoardSize) / 2;
    int boardY = BoardMargin;
    int squareSize = BoardSize / 8;
    int pieceSize = 60;
    int offset = (squareSize - pieceSize) / 2;


    Board *board;
    BoardState *stateBoard;
    Sound moveSound;
    Sound captureSound;
    
    GUI(Board *board);
    ~GUI();

    void DrawBoard();
    void DrawPieces();
    void UnloadPieceTexture(char piece);
    void printBoard();
    void DragPiece(int x, int y, int piece);
    void Draw();
    void colorizeLegalMoves(int activePiece);
    void resize(int width, int height);
    void controls();


    Texture2D ResizeImageAndLoad(std::string path, int width, int height);
    void LoadAssets();
    void UnloadAssets();
    int getSquare(int x, int y);
    void resetStateBoard(BoardState stateToReset=ALL, BoardState stateToSet=DEFAULT);
};




#endif //GUI_H