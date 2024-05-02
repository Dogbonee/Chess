//
// Created by 24crickenbach on 4/30/2024.
//

#include "Knight.h"

Knight::Knight(sf::Vector2i position, bool bIsBlack) : ChessPiece(position, bIsBlack)
{
    m_pieceType = bIsBlack ? BLACK_KNIGHT : WHITE_KNIGHT;
    setTexture(bIsBlack ? System::BN_Texture : System::WN_Texture);
    SetOriginToCenterOfTexture();
}

void Knight::CalculatePossibleMoves(const Board &board)
{
    m_possibleMoves.clear();
    for(int i = -1; i <= 1; i+=2)
    {
        sf::Vector2i query;

        query = sf::Vector2i(m_position.x+i, m_position.y+2);
        if(IsLegalMove(board, query, m_bIsBlack)) m_possibleMoves.emplace_back(query);
        query = sf::Vector2i(m_position.x+i, m_position.y-2);
        if(IsLegalMove(board, query, m_bIsBlack)) m_possibleMoves.emplace_back(query);
        query = sf::Vector2i(m_position.x+2, m_position.y+i);
        if(IsLegalMove(board, query, m_bIsBlack)) m_possibleMoves.emplace_back(query);
        query = sf::Vector2i(m_position.x-2, m_position.y+i);
        if(IsLegalMove(board, query, m_bIsBlack)) m_possibleMoves.emplace_back(query);
    }
}


