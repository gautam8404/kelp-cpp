#include <iostream>
#include <chrono>
#include "kelp/modules/board/board.h"
#include "gui/gui.h"
#include "kelp/modules/constants.h"
#include "kelp/modules/board/bitboards/bitboard.h"
#include "kelp/modules/move_gen/move_gen.h"


//// debug only remove befor commit
#define empty_board "8/8/8/8/8/8/8/8 w - - "
#define start_position "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 "
#define tricky_position "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1 "
#define killer_position "rnbqkb1r/pp1p1pPp/8/2p1pP2/1P1P4/3P3P/P1P1P3/RNBQKBNR w KQkq e6 0 1"
#define cmk_position "r2q1rk1/ppp2ppp/2n1bn2/2b1p3/3pP3/3P1NPP/PPP1NPB1/R1BQ1RK1 b - - 0 9 "

int main() {
//    InitWindow(screenWidth, screenHeight, "Chess AI");
//    InitAudioDevice();
//    SetTargetFPS(60);
//    SetWindowMinSize(screenWidth, screenHeight);
//    SetWindowState(FLAG_WINDOW_RESIZABLE);

    Board board;
////    GUI gui(&board);
//    BitBoard bitboard;
//    U64 blocko = 0ULL;
//    blocko |= (1ULL << f7);
//    blocko |= (1ULL << g2);
//    U64 pawnBoard = bitboard.genPawnMaskMoves(P_BLACK, h6);
//    bitboard.printBitBoard(pawnBoard);
    LookupTable lookupTable;
    std::cout << "Populating lookup table" << std::endl;
    auto s = std::chrono::high_resolution_clock::now();
    lookupTable.populate();
    auto e = std::chrono::high_resolution_clock::now() ;
    std::cout << "Lookup table populated" << std::endl;
    auto t = std::chrono::duration_cast<std::chrono::milliseconds>(e - s);
    std::cout << "Time taken: " << t.count() << std::endl;
    BitBoard bitBoard(&lookupTable, &board);

    U64 block = 0ULL;
    block |= (1ULL << e5);
    block |= (1ULL << h3);
    bitBoard.setCurrentBitBoard();
    U64 occ = 0ULL;
    bitBoard.printBitBoard(bitBoard.genBishopMask(d5));
    U64 rookBoard = bitBoard.getBishopMoves(d5, 0ULL);
//    std::cout << rookBoard << std::endl;

//    bitBoard.printBitBoard(bitBoard.setOccupancy(4095, bitBoard.CountBits(bitBoard.genRookMaskAttacks(a1)), bitBoard.genRookMaskAttacks(a1)));
    bitBoard.printBitBoard(rookBoard);
    bitBoard.printBitBoard(bitBoard.getQueenMoves(d5, 0ULL));

    board.loadFen(tricky_position);
    board.printBoard();
    board.printBoardUnicode();
//    MovGen movGen(&bitBoard);
    bitBoard.updateBitBoards();
//    bitBoard.printBitBoard(bitBoard.getCurrentBitBoard(P_WHITE, PAWN));
//    bitBoard.printBitBoard(bitBoard.getCurrentBitBoard(P_BLACK, PAWN));
//    bitBoard.printBitBoard(bitBoard.getCurrentBitBoard(P_WHITE,KNIGHT));
//    bitBoard.printBitBoard(bitBoard.getCurrentBitBoard(P_BLACK, KNIGHT));
//    bitBoard.printBitBoard(bitBoard.getCurrentBitBoard(P_WHITE, BISHOP));
//    bitBoard.printBitBoard(bitBoard.getCurrentBitBoard(P_BLACK, BISHOP));
//    bitBoard.printBitBoard(bitBoard.getCurrentBitBoard(P_WHITE, ROOK));
//    bitBoard.printBitBoard(bitBoard.getCurrentBitBoard(P_BLACK, ROOK));
//    bitBoard.printBitBoard(bitBoard.getCurrentBitBoard(P_WHITE, QUEEN));
//    bitBoard.printBitBoard(bitBoard.getCurrentBitBoard(P_BLACK, QUEEN));
//    bitBoard.printBitBoard(bitBoard.getCurrentBitBoard(P_WHITE, KING));
//    bitBoard.printBitBoard(bitBoard.getCurrentBitBoard(P_BLACK, KING));
//    bitBoard.printBitBoard(bitBoard.getCurrentBitBoard());
//    bitBoard.printBitBoard(bitBoard.getCurrentBitBoard(P_WHITE));
//    bitBoard.printBitBoard(bitBoard.getCurrentBitBoard(P_BLACK));
//    bitBoard.printBitBoard(bitBoard.getQueenMoves());
    bitBoard.printBitBoard(bitBoard.getCurrentBitBoard(P_BLACK));
    board.setPiece(ROOK | P_WHITE, b4);
    bitBoard.printBitBoard(bitBoard.getKnightMoves(d5, bitBoard.getCurrentBitBoard(P_WHITE)));
    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0) {
            std::cout << 8 - (i / 8) << '\t' << '\t';
        }
//        std::cout << movGen.isSquareAttacked(P_WHITE, i) << "\t";
        if (i % 8 == 7) {
            std::cout << std::endl;
        }
    }
//    std::cout << std::endl;
//    std::cout << '\t';
//    for (int i = 0; i < 8; i++) {
//        std::cout << "\t"  << char('a' + i) << ' ';
//    }

    MovGen movGen(&bitBoard, &board);
    auto a = movGen.genBishopMoves(P_WHITE);
    std::cout << a.size() << std::endl;

    for (auto &move : a) {
        std::cout << move.moveString << std::endl;
    }



    std::cout << movGen.squareToString(d5) << std::endl;
    exit(0);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(LIGHTGRAY);
//        gui.Draw();
//        gui.controls();
        EndDrawing();
    }
//    gui.UnloadAssets();
    board.printBoard();
    CloseWindow();

}

