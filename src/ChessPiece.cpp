//
// Created by 24crickenbach on 4/30/2024.
//

#include "ChessPiece.h"

ChessPiece::ChessPiece(sf::Vector2i position, bool bIsBlack)
{
    m_position = position;
    m_bIsBlack = bIsBlack;
}

//Tries to move the piece to the specified location. Note that this function does nct call CalculatePossibleMoves on success.
int ChessPiece::AttemptMove(ChessBoard& board, sf::Vector2i position)
{
    int result = 0;
    if(std::find(m_possibleMoves.begin(), m_possibleMoves.end(), position) != m_possibleMoves.end())
    {
        result++;
        result += board.GetBoard()[position.y][position.x] != EMPTY;
        board.ModifyBoard(position, m_pieceType);
        board.ModifyBoard(m_position, EMPTY);
        m_position = position;
        return result;
    }
    std::cout<<"Attempt to move to an illegal square\n";
    return result;
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
