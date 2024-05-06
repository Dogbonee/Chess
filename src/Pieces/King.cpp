//
// Created by 24crickenbach on 4/30/2024.
//

#include "King.h"

King::King(sf::Vector2i position, bool bIsBlack, const std::shared_ptr<Rook>& LeftRook, const std::shared_ptr<Rook>& RightRook) : ChessPiece(position, bIsBlack)
{
    m_pieceType = bIsBlack ? BLACK_KING : WHITE_KING;
    setTexture(bIsBlack ? System::BK_Texture : System::WK_Texture);
    SetOriginToCenterOfTexture();

    p_leftRook = LeftRook;
    p_rightRook = RightRook;

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

    if(CanCastle(board, true))
    {
        m_possibleMoves.emplace_back(m_position.x + 2, m_position.y);
    }
    if(CanCastle(board, false))
    {
        m_possibleMoves.emplace_back(m_position.x - 2, m_position.y);
    }

}

int King::AttemptMove(ChessBoard &board, sf::Vector2i position)
{
    auto lastPosition = m_position;
    int result = ChessPiece::AttemptMove(board, position);

    //Castling
    if(result == 1 && lastPosition.x + 2 == position.x)
    {
        p_rightRook->AttemptMove(board, sf::Vector2i(position.x-1, position.y));
    }
    if(result == 1 && lastPosition.x - 2 == position.x)
    {
        p_leftRook->AttemptMove(board, sf::Vector2i(position.x+1, position.y));
    }


    return result;
}

bool King::CanCastle(const Board &board, bool rightCastling)
{
    if(m_bHasMoved)return false;
    if(rightCastling && p_rightRook->HasMoved())return false;
    if(!rightCastling && p_leftRook->HasMoved())return false;

    if(rightCastling && (board[m_position.y][m_position.x + 1] | board[m_position.y][m_position.x + 2]) != EMPTY)
    {
        return false;
    }
    if(!rightCastling && (board[m_position.y][m_position.x - 1] | board[m_position.y][m_position.x - 2]) != EMPTY)
    {
        return false;
    }

    return true;
}


