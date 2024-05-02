//
// Created by 24crickenbach on 4/30/2024.
//

#ifndef QUEEN_H
#define QUEEN_H
#include "../ChessPiece.h"


class Queen : public ChessPiece{

public:
    Queen(sf::Vector2i position, bool bIsBlack);

    void CalculatePossibleMoves(const Board &board) override;

};



#endif //QUEEN_H
