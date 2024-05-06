//
// Created by 24crickenbach on 4/30/2024.
//

#ifndef CHESSPIECE_H
#define CHESSPIECE_H
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <algorithm>
#include "ChessBoard.h"
#include "System.h"

class ChessPiece : public sf::Sprite {



protected:
    bool m_bIsBlack;
    bool m_bHasMoved;
    PieceType m_pieceType;
    sf::Vector2i m_position;
    std::vector<sf::Vector2i> m_possibleMoves;
    sf::FloatRect m_detectionArea;
    bool m_bIsHovered;


public:
    ChessPiece(sf::Vector2i position, bool bIsBlack);
    void SetOriginToCenterOfTexture();

    virtual int AttemptMove(ChessBoard& board, sf::Vector2i position);
    void SetPiece(sf::Vector2i position);
    void SetHasMoved();
    virtual void CalculatePossibleMoves(const Board& board) = 0;
    void ReplacePossibleMoves(const std::vector<sf::Vector2i>& moves);
    int IsLegalMove(const Board& board, sf::Vector2i position, bool bIsBlack);

    void PrintPossibleMoves();

    bool ManageCollision(sf::Vector2i mousePos);
    void MovePieceVisual(sf::Vector2i mousePos);

    const std::vector<sf::Vector2i>& GetPossibleMoves();
    bool IsHovered() const;
    bool IsBlack();

    const sf::Vector2i& GetBoardCoordinates();
    PieceType GetPieceType();

};



#endif //CHESSPIECE_H
