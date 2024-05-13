//
// Created by 24crickenbach on 4/30/2024.
//

#include "Pawn.h"

#include "../System.h"

Pawn::Pawn(sf::Vector2i position, bool bIsBlack) : ChessPiece(position, bIsBlack)
{
    m_pieceType = bIsBlack ? BLACK_PAWN : WHITE_PAWN;
    setTexture(bIsBlack ? System::BP_Texture : System::WP_Texture);
    SetOriginToCenterOfTexture();
}

void Pawn::CalculatePossibleMoves(const Board &board)
{
    m_possibleMoves.clear();
    for(int i = 1; i <= 1 + !m_bHasMoved; i++){
        int colorSwitch = m_bIsBlack ? i : -i;
        sf::Vector2i attemptedMove(m_position.x, m_position.y+colorSwitch);
        if(IsLegalMove(board, attemptedMove, m_bIsBlack) == 1)
        {
            m_possibleMoves.emplace_back(attemptedMove);
        }else
        {
            break;
        }

    }
    int colorSwitch = m_bIsBlack ? 1 : -1;
    sf::Vector2i attemptedMove(m_position.x, m_position.y+colorSwitch);
    attemptedMove.x--;
    if(IsLegalMove(board, attemptedMove, m_bIsBlack) == 2)
    {
        m_possibleMoves.emplace_back(attemptedMove);
    }
    attemptedMove.x += 2;
    if(IsLegalMove(board, attemptedMove, m_bIsBlack) == 2)
    {
        m_possibleMoves.emplace_back(attemptedMove);
    }

}

std::shared_ptr<ChessPiece> Pawn::clone()
{
    return std::make_shared<Pawn>(*this);
}






