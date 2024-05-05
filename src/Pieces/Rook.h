//
// Created by 24crickenbach on 4/30/2024.
//

#ifndef ROOK_H
#define ROOK_H
#include "../ChessPiece.h"


class Rook : public ChessPiece{

    bool m_bHasMoved;

public:
    Rook(sf::Vector2i position, bool bIsBlack);
    void CalculatePossibleMoves(const Board &board) override;

    int AttemptMove(ChessBoard &board, sf::Vector2i position) override;

    bool HasMoved();


};



#endif //ROOK_H
