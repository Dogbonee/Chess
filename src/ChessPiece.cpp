//
// Created by 24crickenbach on 4/30/2024.
//

#include "ChessPiece.h"

#include "System.h"


ChessPiece::ChessPiece(sf::Vector2i position, bool bIsBlack) : m_bIsHovered(false)
{
    m_position = position;
    m_bIsBlack = bIsBlack;

    m_detectionArea = sf::FloatRect(position.x * System::TILE_SIZE + System::X_CENTER_OFFSET, position.y * System::TILE_SIZE,
        System::TILE_SIZE, System::TILE_SIZE);


    setPosition(m_detectionArea.left + System::TILE_SIZE/2, m_detectionArea.top + System::TILE_SIZE/2);
    setScale(sf::Vector2f(1.5,1.5));


}

void ChessPiece::SetOriginToCenterOfTexture()
{
    setOrigin(getTexture()->getSize().x/2, getTexture()->getSize().y/2);
}


//Tries to move the piece to the specified location. Note that this function does nct call CalculatePossibleMoves on success.
//returns 0 on illegal move
//returns 1 on move to empty square
//returns 2 on move to filled square
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

    return result;
}

int ChessPiece::IsLegalMove(const Board& board, sf::Vector2i position, bool bIsBlack)
{
    try
    {
        int boardPiece = board.at(position.y).at(position.x);
        if(boardPiece == EMPTY)
        {
            return 1;
        }
        if((bIsBlack && boardPiece < 7) || (!bIsBlack && boardPiece > 6))
        {
            return 2;
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

bool ChessPiece::ManageCollision(sf::Vector2i mousePos)
{
    return m_bIsHovered = m_detectionArea.contains(static_cast<sf::Vector2f>(mousePos));
}

void ChessPiece::MovePieceVisual(sf::Vector2i mousePos)
{

    sf::Vector2f castedPos = static_cast<sf::Vector2f>(mousePos);
    setPosition(castedPos);
    m_detectionArea.left = castedPos.x - m_detectionArea.width/2;
    m_detectionArea.top = castedPos.y - m_detectionArea.height/2;
}

const std::vector<sf::Vector2i> & ChessPiece::GetPossibleMoves()
{
    return m_possibleMoves;
}

bool ChessPiece::IsHovered() const
{
    return m_bIsHovered;
}

bool ChessPiece::IsBlack()
{
    return m_bIsBlack;
}

const sf::Vector2i & ChessPiece::GetBoardCoordinates()
{
    return m_position;
}

PieceType ChessPiece::GetPieceType()
{
    return m_pieceType;
}

