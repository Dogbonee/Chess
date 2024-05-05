//
// Created by 24crickenbach on 4/30/2024.
//

#ifndef KING_H
#define KING_H
#include <memory>

#include "Rook.h"
#include "../ChessPiece.h"


class King : public ChessPiece{

    bool m_bHasMoved;
    std::shared_ptr<Rook> p_leftRook;
    std::shared_ptr<Rook> p_rightRook;
public:
    King(sf::Vector2i position, bool bIsBlack, const std::shared_ptr<Rook>& LeftRook, const std::shared_ptr<Rook>& RightRook);
    void CalculatePossibleMoves(const Board &board) override;

    int AttemptMove(ChessBoard &board, sf::Vector2i position) override;
    bool CanCastle(const Board &board, bool rightCastling);

};



#endif //KING_H
