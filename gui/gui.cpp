#include "../kelp/modules/board/board.h"
#include "../kelp/modules/board/fen.h"
#include "gui.h"
#include <iostream>

GUI::GUI(Board *board) : board(board) {
    LoadAssets();
    stateBoard = new BoardState[64];
    for (int i = 0; i < 64; i++) {
        stateBoard[i] = DEFAULT;
    }
}

GUI::~GUI() {
    UnloadAssets();
    delete [] stateBoard;
}

void GUI::DrawBoard() {
    for (int i = 0; i < 64; i++) {
        int row = i / 8;
        int col = i % 8;
        Color color = (row + col) % 2 == 0 ? WHITE : BROWN;
        DrawRectangle(col * squareSize + boardX, row * squareSize + boardY, squareSize, squareSize, color);

        // overlay
        if (stateBoard[i] != DEFAULT){
            if (stateBoard[i] == ACTIVE) color = YELLOW;
            if (stateBoard[i] == LEGAL) color = RED;

            Color opacity = {color.r, color.g, color.b, 100};
            DrawRectangle(col * squareSize + boardX, row * squareSize + boardY, squareSize, squareSize, opacity);
        }
    }


    //outline
    Rectangle outline = {float (boardX), float(boardY), float (BoardSize), float (BoardSize)};
    DrawRectangleLinesEx(outline, 2, BLACK);
}

void GUI::DrawPieces() {
    for (int i = 0; i < 64; i++){
        int row = i / 8;
        int col = i % 8;

        if (board->board[i] != NONE ) {
            if (stateBoard[i] == ACTIVE) {
                continue;
            }
            char piece = PieceMapReverse[pieceType(board->board[i])];
            piece = pieceColor(board->board[i]) == P_WHITE ? toupper(piece) : tolower(piece);
            DrawTexture(pieceTextures[piece], col * squareSize + offset + boardX, row * squareSize + offset + boardY, WHITE);
        }
    }
}

void GUI::UnloadPieceTexture(char piece) {

}

void GUI::printBoard() {

}

void GUI::DragPiece(int x, int y, int piece) {
    char c = board->getPieceChar(piece);
    DrawTexture(pieceTextures[c], x - squareSize / 2, y - squareSize / 2, WHITE);
}

void GUI::Draw() {
    DrawBoard();
    DrawPieces();
}

void GUI::colorizeLegalMoves(int activePiece) {

}

void GUI::resize(int width, int height) {
    BoardSize = height - 2 ;
    squareSize = BoardSize / 8;
    boardX = (width - BoardSize) / 2;
    boardY = BoardMargin;
    offset = (squareSize - pieceSize) / 2;
}

void GUI::controls() {
    if (IsKeyPressed(KEY_F11)) {
        ToggleFullscreen();
    }

    if (IsWindowResized()) {
        resize(GetScreenWidth(), GetScreenHeight());
    }

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        int x = GetMouseX();
        int y = GetMouseY();

        if (x > boardX && x < boardX + BoardSize && y > boardY && y < boardY + BoardSize) {
            int index = getSquare(x, y);
            if (activePiece == -1 && activeSquare == -1 && board->board[index] != NONE && !isDragging) {
                activePiece = board->getPiece(index);
                activeSquare = index;
                isDragging = true;
                resetStateBoard(ACTIVE);
                stateBoard[index] = ACTIVE;
            }

            if (activePiece != -1 && activeSquare != -1 && isDragging) {
                DragPiece(x, y, activePiece);
            }
//            board->movePiece(index);
        }
    }

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        int x = GetMouseX();
        int y = GetMouseY();
        int index = getSquare(x, y);
        std::cout << index << std::endl;

        if (x > boardX && x < boardX + BoardSize && y > boardY && y < boardY + BoardSize && index != activeSquare) {

            if (activePiece != -1 && activeSquare != -1 && isDragging) {
                Move move = board->movePiece(activeSquare, index);
                if (move.isCapture) {
                    std::cout << "Capture" << std::endl;
                    PlaySound(captureSound);
                } else {
                    PlaySound(moveSound);
                }
                activePiece = -1;
                activeSquare = -1;
                isDragging = false;
                stateBoard[activeSquare] = DEFAULT;
            }
        } else {
            board->setPiece(activePiece, activeSquare);
            stateBoard[activeSquare] = DEFAULT;
            activePiece = -1;
            activeSquare = -1;
            isDragging = false;
        }

    }

}

Texture2D GUI::ResizeImageAndLoad(std::string path, int width, int height) {
    Image image = LoadImage(path.c_str());
    ImageResize(&image, width, height);
    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);
    return texture;
}

void GUI::LoadAssets() {
    std::string workingDir = GetWorkingDirectory();
    std::string imgPath = workingDir + "/gui/assets/pieces";
    std::string soundPath = workingDir + "/gui/assets/sounds/";

    moveSound = LoadSound((soundPath + "Move.ogg").c_str());
    captureSound = LoadSound((soundPath + "Capture.ogg").c_str());

    pieceTextures['k'] = ResizeImageAndLoad((imgPath + ("/Chess_kdt60.png")), pieceSize, pieceSize);
    pieceTextures['p'] = ResizeImageAndLoad((imgPath + ("/Chess_pdt60.png")), pieceSize, pieceSize);
    pieceTextures['n'] = ResizeImageAndLoad((imgPath + ("/Chess_ndt60.png")), pieceSize, pieceSize);
    pieceTextures['b'] = ResizeImageAndLoad((imgPath + ("/Chess_bdt60.png")), pieceSize, pieceSize);
    pieceTextures['r'] = ResizeImageAndLoad((imgPath + ("/Chess_rdt60.png")), pieceSize, pieceSize);
    pieceTextures['q'] = ResizeImageAndLoad((imgPath + ("/Chess_qdt60.png")), pieceSize, pieceSize);
    pieceTextures['K'] = ResizeImageAndLoad((imgPath + ("/Chess_klt60.png")), pieceSize, pieceSize);
    pieceTextures['P'] = ResizeImageAndLoad((imgPath + ("/Chess_plt60.png")), pieceSize, pieceSize);
    pieceTextures['N'] = ResizeImageAndLoad((imgPath + ("/Chess_nlt60.png")), pieceSize, pieceSize);
    pieceTextures['B'] = ResizeImageAndLoad((imgPath + ("/Chess_blt60.png")), pieceSize, pieceSize);
    pieceTextures['R'] = ResizeImageAndLoad(imgPath + ("/Chess_rlt60.png"), pieceSize, pieceSize);
    pieceTextures['Q'] = ResizeImageAndLoad((imgPath + ("/Chess_qlt60.png")), pieceSize, pieceSize);
}

void GUI::UnloadAssets() {
    for (auto &piece : pieceTextures) {
        UnloadTexture(piece.second);
    }

    UnloadSound(moveSound);
    UnloadSound(captureSound);
}

int GUI::getSquare(int x, int y) {
    int col = (x - boardX) / squareSize;
    int row = (y - boardY) / squareSize;
    return row * 8 + col;
}

void GUI::resetStateBoard(BoardState stateToReset, BoardState stateToSet) {
    for (int i = 0; i < 64; i++) {
        if (stateBoard[i] == stateToReset || stateToReset == ALL) {
            stateBoard[i] = stateToSet;
        }
    }

}
