//
// Created by hunde on 3/30/2024.
//

#ifndef PROGRAM_H
#define PROGRAM_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "ChessBoard.h"
#include "ChessPiece.h"
#include "Pieces/Pawn.h"
#include "State.h"

class GameState : public State{

    void Update() override;
    void Render() override;


    ChessBoard m_board;
    std::vector<std::unique_ptr<ChessPiece>> m_pieces;

public:
    GameState(StateMachine* p_sm, sf::RenderWindow* p_rw);
    ~GameState();


};



#endif //PROGRAM_H
