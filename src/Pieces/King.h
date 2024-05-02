//
// Created by 24crickenbach on 4/30/2024.
//

#ifndef KING_H
#define KING_H
#include "../ChessPiece.h"


class King : public ChessPiece{

public:
    King(sf::Vector2i position, bool bIsBlack);
    void CalculatePossibleMoves(const Board &board) override;


};



#endif //KING_H
