//
// Created by 24crickenbach on 4/30/2024.
//

#include "ChessPiece.h"

ChessPiece::ChessPiece(sf::Vector2i position, bool bIsBlack)
{
    m_position = position;
    m_bIsBlack = bIsBlack;
}

bool ChessPiece::IsLegalMove(const Board& board, sf::Vector2i position, bool bIsBlack)
{
    try
    {
        int boardPiece = board.at(position.y).at(position.x);
        if(boardPiece == EMPTY || (bIsBlack && boardPiece < 7) || (!bIsBlack && boardPiece > 6))
        {
            return true;
        }
    }catch(const std::out_of_range& e)
    {
        return false;
    }
    return false;
}

void ChessPiece::PrintPossibleMoves()
{
    std::cout<<"Total possible moves: " << m_possibleMoves.size() << '\n';
    for(const auto& pos : m_possibleMoves)
    {
        printf("(%d, %d)\n", pos.x, pos.y);
    }
    std::cout<<std::flush;
}
