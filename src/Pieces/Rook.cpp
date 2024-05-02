//
// Created by 24crickenbach on 4/30/2024.
//

#include "Rook.h"

Rook::Rook(sf::Vector2i position, bool bIsBlack) : ChessPiece(position, bIsBlack)
{
    m_pieceType = bIsBlack ? BLACK_ROOK : WHITE_ROOK;
    setTexture(bIsBlack ? System::BR_Texture : System::WR_Texture);
    SetOriginToCenterOfTexture();
}

void Rook::CalculatePossibleMoves(const Board &board)
{
    m_possibleMoves.clear();
    for(int i = 1; i < 8; i++)
    {
        sf::Vector2i attemptedMove(m_position.x, m_position.y + i);
        int result = IsLegalMove(board, attemptedMove, m_bIsBlack);
        if(result == 1)
        {
            m_possibleMoves.emplace_back(attemptedMove);
        }else if(result == 2)
        {
            m_possibleMoves.emplace_back(attemptedMove);
            break;
        }else break;
    }
    for(int i = 1; i < 8; i++)
    {
        sf::Vector2i attemptedMove = sf::Vector2i(m_position.x + i, m_position.y);
        int result = IsLegalMove(board, attemptedMove, m_bIsBlack);
        if(result == 1)
        {
            m_possibleMoves.emplace_back(attemptedMove);
        }else if(result == 2)
        {
            m_possibleMoves.emplace_back(attemptedMove);
            break;
        }else break;
    }
    for(int i = 1; i < 8; i++)
    {
        sf::Vector2i attemptedMove = sf::Vector2i(m_position.x - i, m_position.y);
        int result = IsLegalMove(board, attemptedMove, m_bIsBlack);
        if(result == 1)
        {
            m_possibleMoves.emplace_back(attemptedMove);
        }else if(result == 2)
        {
            m_possibleMoves.emplace_back(attemptedMove);
            break;
        }else break;
    }
    for(int i = 1; i < 8; i++)
    {
        sf::Vector2i attemptedMove = sf::Vector2i(m_position.x, m_position.y - i);
        int result = IsLegalMove(board, attemptedMove, m_bIsBlack);
        if(result == 1)
        {
            m_possibleMoves.emplace_back(attemptedMove);
        }else if(result == 2)
        {
            m_possibleMoves.emplace_back(attemptedMove);
            break;
        }else break;
    }
}


