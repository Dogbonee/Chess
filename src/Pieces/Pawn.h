//
// Created by 24crickenbach on 4/30/2024.
//

#ifndef PAWN_H
#define PAWN_H
#include "../ChessPiece.h"


class Pawn : public ChessPiece{

    bool m_bHasMoved;

public:

    Pawn(sf::Vector2i position, bool bIsBlack);
    void CalculatePossibleMoves(const Board& board) override;

    int AttemptMove(ChessBoard &board, sf::Vector2i position) override;
};



#endif //PAWN_H
