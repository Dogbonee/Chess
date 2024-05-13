//
// Created by 24crickenbach on 4/30/2024.
//

#ifndef KNIGHT_H
#define KNIGHT_H
#include "../ChessPiece.h"


class Knight : public ChessPiece{
public:
    Knight(sf::Vector2i position, bool bIsBlack);
    void CalculatePossibleMoves(const Board &board) override;

    std::shared_ptr<ChessPiece> clone() override;
};



#endif //KNIGHT_H
