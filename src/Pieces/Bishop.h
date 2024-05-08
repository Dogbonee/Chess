//
// Created by 24crickenbach on 4/30/2024.
//

#ifndef BISHOP_H
#define BISHOP_H
#include "../ChessPiece.h"


class Bishop : public ChessPiece{



public:
    Bishop(sf::Vector2i position, bool bIsBlack);

    void CalculatePossibleMoves(const Board &board) override;

    std::shared_ptr<ChessPiece> clone() override;
};



#endif //BISHOP_H
