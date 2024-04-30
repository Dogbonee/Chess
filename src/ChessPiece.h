//
// Created by 24crickenbach on 4/30/2024.
//

#ifndef CHESSPIECE_H
#define CHESSPIECE_H
#include <SFML/System/Vector2.hpp>
#include <vector>

#include "ChessBoard.h"

class ChessPiece {


protected:
    bool m_bIsBlack;
    PieceType m_pieceType;
    sf::Vector2i m_position;
    std::vector<sf::Vector2i> m_possibleMoves;


public:
    ChessPiece(sf::Vector2i position, bool bIsBlack);

    virtual void CalculatePossibleMoves(const Board& board) = 0;
    bool IsLegalMove(const Board& board, sf::Vector2i position, bool bIsBlack);

    void PrintPossibleMoves();

};



#endif //CHESSPIECE_H
