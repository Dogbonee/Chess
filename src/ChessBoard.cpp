//
// Created by 24crickenbach on 4/30/2024.
//

#include "ChessBoard.h"

#include "System.h"

ChessBoard::ChessBoard()
{

    for(int y = 0; y < 8; y++)
    {
        for(int x = 0; x < 8; x++)
        {
            sf::RectangleShape rect(sf::Vector2f(System::TILE_SIZE, System::TILE_SIZE));
            rect.setPosition(x * System::TILE_SIZE + System::X_CENTER_OFFSET, y * System::TILE_SIZE);
            rect.setFillColor((x+y%2)%2 ? sf::Color(222,184,135) : sf::Color(255,248,220));
            m_visualBoard[y][x] = rect;
        }
    }



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

void ChessBoard::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for(const auto& arr : m_visualBoard)
    {
        for(const auto& i : arr)
        {
            target.draw(i);
        }
    }
}
