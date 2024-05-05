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
    void HandleEvents() override;



    ChessBoard m_board;
    std::vector<std::shared_ptr<ChessPiece>> m_pieces;

    std::shared_ptr<ChessPiece> p_activePiece;
    sf::Vector2f m_lastPieceCoords;

    bool m_bIsBlackTurn;

    bool m_bWhiteIsChecked;
    bool m_bBlackIsChecked;

    void DragPiece(sf::Vector2i position);
    bool CheckSpot(sf::Vector2f position);
    void ConfirmPiece(sf::Vector2i boardCoords);
    void CapturePiece(sf::Vector2i boordCoords);
    void DetermineCheckStatus();
    void CalculateBoardMoves();

    void SyncVisualsWithBoard();

    void Checkmate();

public:
    GameState(StateMachine* p_sm, sf::RenderWindow* p_rw);
    ~GameState();


};



#endif //PROGRAM_H
