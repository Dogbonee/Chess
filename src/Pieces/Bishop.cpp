//
// Created by 24crickenbach on 4/30/2024.
//

#include "Bishop.h"

Bishop::Bishop(sf::Vector2i position, bool bIsBlack) : ChessPiece(position, bIsBlack)
{
    m_pieceType = bIsBlack ? BLACK_BISHOP : WHITE_BISHOP;
}

void Bishop::CalculatePossibleMoves(const Board &board)
{
    for(int i = -8; i < 8; i++)
    {
        sf::Vector2i attemptedMove(m_position.x + i, m_position.y + i);
        if(IsLegalMove(board, attemptedMove, m_bIsBlack))
        {
            m_possibleMoves.emplace_back(attemptedMove);
        }
        attemptedMove = sf::Vector2i(m_position.x + i, m_position.y - i);
        if(IsLegalMove(board, attemptedMove, m_bIsBlack))
        {
            m_possibleMoves.emplace_back(attemptedMove);
        }
    }
}
