//
// Created by 24crickenbach on 4/30/2024.
//

#include "ChessBoard.h"

ChessBoard::ChessBoard()
{

}

void ChessBoard::PrintBoard()
{
    for(const auto& i : m_board)
    {
        for(const auto& j : i)
        {
            std::cout<<j<<' ';
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

void ChessBoard::ModifyBoard(sf::Vector2i position, PieceType value)
{
    m_board[position.y][position.x] = value;
}

const Board & ChessBoard::GetBoard() const
{
    return m_board;
}
