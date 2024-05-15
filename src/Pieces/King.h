//
// Created by 24crickenbach on 4/30/2024.
//

#ifndef KING_H
#define KING_H
#include <memory>

#include "Rook.h"
#include "../ChessPiece.h"


class King : public ChessPiece{

    std::shared_ptr<Rook> p_leftRook;
    std::shared_ptr<Rook> p_rightRook;
public:
    King(sf::Vector2i position, bool bIsBlack, const std::shared_ptr<Rook>& LeftRook, const std::shared_ptr<Rook>& RightRook);
    void CalculatePossibleMoves(const Board &board) override;

    void MovePiece(ChessBoard &board, sf::Vector2i position) override;
    bool CanCastle(const Board &board, bool rightCastling);

    std::shared_ptr<ChessPiece> clone() override;
};



#endif //KING_H
