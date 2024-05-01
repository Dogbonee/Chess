//
// Created by 24crickenbach on 4/30/2024.
//

#include "King.h"

King::King(sf::Vector2i position, bool bIsBlack) : ChessPiece(position, bIsBlack)
{
    m_pieceType = bIsBlack ? BLACK_KING : WHITE_KING;
    setTexture(bIsBlack ? System::BK_Texture : System::WK_Texture);
    SetOriginToCenterOfTexture();
}

void King::CalculatePossibleMoves(const Board &board)
{
    m_possibleMoves.clear();
    for(int y = -1; y <= 1; y++)
    {
        for(int x = -1; x <= 1; x++)
        {
            if(x == 0 && y == 0)continue;
            sf::Vector2i attemptedMove(m_position.x + x, m_position.y + y);
            if(IsLegalMove(board, attemptedMove, m_bIsBlack))
            {
                m_possibleMoves.emplace_back(attemptedMove);
            }
        }
    }
}

