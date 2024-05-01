//
// Created by hunde on 3/30/2024.
//

#include "GameState.h"

#include "Pieces/Bishop.h"
#include "Pieces/King.h"
#include "Pieces/Knight.h"
#include "Pieces/Queen.h"
#include "Pieces/Rook.h"


GameState::GameState(StateMachine* p_sm, sf::RenderWindow* p_rw) : State(p_sm, p_rw){

    for(int y = 1; y <= 6; y+=5)
    {
        for(int i = 0; i < 8; i++)
        {
            m_pieces.emplace_back(std::make_unique<Pawn>(sf::Vector2i(i,y), y == 1));
        }
    }
    for(int y = 0; y <= 7; y+=7)
    {
        m_pieces.emplace_back(std::make_unique<Rook>(sf::Vector2i(0,y), y == 0));
        m_pieces.emplace_back(std::make_unique<Knight>(sf::Vector2i(1,y), y == 0));
        m_pieces.emplace_back(std::make_unique<Bishop>(sf::Vector2i(2,y), y == 0));
        m_pieces.emplace_back(std::make_unique<Queen>(sf::Vector2i(3,y), y == 0));
        m_pieces.emplace_back(std::make_unique<King>(sf::Vector2i(4,y), y == 0));
        m_pieces.emplace_back(std::make_unique<Bishop>(sf::Vector2i(5,y), y == 0));
        m_pieces.emplace_back(std::make_unique<Knight>(sf::Vector2i(6,y), y == 0));
        m_pieces.emplace_back(std::make_unique<Rook>(sf::Vector2i(7,y), y == 0));
    }

    for(const auto & piece : m_pieces)
    {
        piece->CalculatePossibleMoves(m_board.GetBoard());
        piece->PrintPossibleMoves();
    }

    m_board.PrintBoard();


    m_pieces[0]->AttemptMove(m_board, sf::Vector2i(0,3));


    m_board.PrintBoard();
}

GameState::~GameState() = default;

void GameState::Update()
{
    HandleEvents();
    Render();
}


void GameState::Render()
{
    p_window->clear();
    p_window->display();
}
