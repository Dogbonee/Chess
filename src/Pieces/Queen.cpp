//
// Created by 24crickenbach on 4/30/2024.
//

#include "Queen.h"

#include <memory>

Queen::Queen(sf::Vector2i position, bool bIsBlack) : ChessPiece(position, bIsBlack)
{
    m_pieceType = bIsBlack ? BLACK_QUEEN : WHITE_QUEEN;
    setTexture(bIsBlack ? System::BQ_Texture : System::WQ_Texture);
    SetOriginToCenterOfTexture();
}

void Queen::CalculatePossibleMoves(const Board &board)
{
    m_possibleMoves.clear();

    //Rook moves
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

    //Bishop moves
    for(int i = 1; i < 8; i++)
    {
        sf::Vector2i attemptedMove(m_position.x + i, m_position.y + i);
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
        sf::Vector2i attemptedMove(m_position.x - i, m_position.y - i);
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
        sf::Vector2i attemptedMove(m_position.x + i, m_position.y - i);
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
        sf::Vector2i attemptedMove(m_position.x - i, m_position.y + i);
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

std::shared_ptr<ChessPiece> Queen::clone()
{
    return std::make_shared<Queen>(*this);
}

