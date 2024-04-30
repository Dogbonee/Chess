//
// Created by 24crickenbach on 4/30/2024.
//

#include "Pawn.h"

Pawn::Pawn(sf::Vector2i position, bool bIsBlack) : ChessPiece(position, bIsBlack), bIsFirstMove(true)
{
    m_pieceType = bIsBlack ? BLACK_PAWN : WHITE_PAWN;
    m_bIsBlack = bIsBlack;
}

void Pawn::CalculatePossibleMoves(const Board &board)
{
    for(int i = 1; i <= 1 + bIsFirstMove; i++){
        int colorSwitch = m_bIsBlack ? i : -i;
        sf::Vector2i attemptedMove(m_position.x, m_position.y+colorSwitch);
        if(IsLegalMove(board, attemptedMove, m_bIsBlack))
        {
            m_possibleMoves.emplace_back(attemptedMove);
        }
    }

}

