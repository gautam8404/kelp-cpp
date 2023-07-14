cmake_minimum_required(VERSION 3.24)
project(kelp)

find_package(raylib REQUIRED)
set(CMAKE_CXX_STANDARD 17)

add_executable(kelp main.cpp kelp/modules/board/board.cpp gui/gui.cpp kelp/modules/board/fen.cpp kelp/modules/board/bitboards/bitboard.cpp kelp/modules/board/bitboards/lookupTable/lookup_tables.cpp kelp/modules/board/bitboards/bitboard_attacks.cpp kelp/modules/board/bitboards/bitboard_moves.cpp kelp/modules/evaluator/evaluator.cpp kelp/modules/move_gen/move_gen.cpp kelp/kelp.cpp)
target_link_libraries(kelp raylib)




