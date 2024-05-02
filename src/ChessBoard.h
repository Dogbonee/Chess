//
// Created by 24crickenbach on 4/30/2024.
//

#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <array>
#include <iostream>
#include <SFML/Graphics.hpp>

using Board = std::array<std::array<int, 8>, 8>;
using VisualBoard = std::array<std::array<sf::RectangleShape, 8>, 8>;

enum PieceType{
    EMPTY = 0,
    WHITE_PAWN,
    WHITE_KNIGHT,
    WHITE_BISHOP,
    WHITE_ROOK,
    WHITE_QUEEN,
    WHITE_KING,

    BLACK_PAWN,
    BLACK_KNIGHT,
    BLACK_BISHOP,
    BLACK_ROOK,
    BLACK_QUEEN,
    BLACK_KING
};



class ChessBoard : public sf::Drawable{
    Board m_board=
        {{
        {10,8,9,11,12,9,8,10},
          {7,7,7,7,7,7,7,7},
          {0,0,0,0,0,0,0,0},
          {0,0,0,0,0,0,0,0},
          {0,0,0,0,0,0,0,0},
          {0,0,0,0,0,0,0,0},
          {1,1,1,1,1,1,1,1},
          {4,2,3,5,6,3,2,4}
        }};

    VisualBoard m_visualBoard;

public:
    ChessBoard();

    void PrintBoard();

    void ModifyBoard(sf::Vector2i position, PieceType value);
    const Board& GetBoard() const;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};



#endif //CHESSBOARD_H
