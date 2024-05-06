//
// Created by 24crickenbach on 4/30/2024.
//

#ifndef ROOK_H
#define ROOK_H
#include "../ChessPiece.h"


class Rook : public ChessPiece{



public:
    Rook(sf::Vector2i position, bool bIsBlack);
    void CalculatePossibleMoves(const Board &board) override;


    bool HasMoved();


};



#endif //ROOK_H
