cmake_minimum_required(VERSION 3.28)
project(Chess)

set(SFML_DIR C:/StudentFiles/Student/SFML-2.6.1/lib/cmake/SFML)
set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES src/main.cpp
        src/GameState.cpp
        src/GameState.h
        src/StateMachine.cpp
        src/StateMachine.h
        src/State.cpp
        src/State.h
        src/ChessBoard.cpp
        src/ChessBoard.h
        src/ChessPiece.cpp
        src/ChessPiece.h
        src/Pieces/Pawn.cpp
        src/Pieces/Pawn.h
        src/Pieces/Knight.cpp
        src/Pieces/Knight.h
        src/Pieces/Bishop.cpp
        src/Pieces/Bishop.h
        src/Pieces/Rook.cpp
        src/Pieces/Rook.h
        src/Pieces/Queen.cpp
        src/Pieces/Queen.h
        src/Pieces/King.cpp
        src/Pieces/King.h
        src/System.cpp
        src/System.h)
set(SFML_STATIC_LIBRARIES true)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)