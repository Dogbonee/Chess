//
// Created by hunde on 3/30/2024.
//

#include "GameState.h"

#include "Pieces/Bishop.h"
#include "Pieces/King.h"
#include "Pieces/Knight.h"
#include "Pieces/Queen.h"
#include "Pieces/Rook.h"


GameState::GameState(StateMachine* p_sm, sf::RenderWindow* p_rw) : State(p_sm, p_rw), m_bIsBlackTurn(false), m_bWhiteIsChecked(false), m_bBlackIsChecked(false){

    for(int y = 1; y <= 6; y+=5)
    {
        for(int i = 0; i < 8; i++)
        {
            m_pieces.emplace_back(std::make_shared<Pawn>(sf::Vector2i(i,y), y == 1));
        }
    }
    for(int y = 0; y <= 7; y+=7)
    {
        m_pieces.emplace_back(std::make_shared<Rook>(sf::Vector2i(0,y), y == 0));
        m_pieces.emplace_back(std::make_shared<Knight>(sf::Vector2i(1,y), y == 0));
        m_pieces.emplace_back(std::make_shared<Bishop>(sf::Vector2i(2,y), y == 0));
        m_pieces.emplace_back(std::make_shared<Queen>(sf::Vector2i(3,y), y == 0));
        m_pieces.emplace_back(std::make_shared<King>(sf::Vector2i(4,y), y == 0));
        m_pieces.emplace_back(std::make_shared<Bishop>(sf::Vector2i(5,y), y == 0));
        m_pieces.emplace_back(std::make_shared<Knight>(sf::Vector2i(6,y), y == 0));
        m_pieces.emplace_back(std::make_shared<Rook>(sf::Vector2i(7,y), y == 0));
    }
    for(const auto & piece : m_pieces)
    {
        piece->CalculatePossibleMoves(m_board.GetBoard());
    }

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
    p_window->draw(m_board);
    for(const auto& i : m_pieces)
    {
        p_window->draw(*i);
    }
    p_window->display();
}

void GameState::HandleEvents()
{
    for(sf::Event event{}; p_window->pollEvent(event);)
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                p_window->close();
            break;
            case sf::Event::MouseMoved:

                if(p_activePiece != nullptr)
                {
                    DragPiece(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));

                    break;
                }

                if(std::any_of( m_pieces.begin(), m_pieces.end(),
                    [event](auto& i){return i->ManageCollision(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));}))
                {
                    p_window->setMouseCursor(System::Hand_Cursor);
                }else
                {
                    p_window->setMouseCursor(System::Arrow_Cursor);
                }
            break;
            case sf::Event::MouseButtonPressed:
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    for(const auto& i : m_pieces)
                    {
                        if(i->ManageCollision(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))
                        {
                            p_activePiece = i;
                            m_lastPieceCoords = p_activePiece->getPosition();
                        }
                    }
                }
            break;
            case sf::Event::MouseButtonReleased:
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    if(p_activePiece)
                    {
                        CheckSpot(p_activePiece->getPosition());
                        p_activePiece = nullptr;
                    }
                }
            case sf::Event::KeyPressed:

                HandleKeyboardInput(event.key.code);
            break;
        }
    }
}

void GameState::DragPiece(sf::Vector2i position)
{
    if(p_activePiece)
    {
        p_activePiece->MovePieceVisual(position);
    }
}

bool GameState::CheckSpot(sf::Vector2f position)
{

    auto revertBoard = [this](auto tempBoard)
    {
        m_board = tempBoard;
        CalculateBoardMoves();
        DetermineCheckStatus();
        p_activePiece->MovePieceVisual(sf::Vector2i(m_lastPieceCoords));
        p_activePiece = nullptr;
    };

    //need to cull possible moves when in check
    sf::Vector2i screenToBoordCoordinates((position.x - System::X_CENTER_OFFSET) / System::TILE_SIZE, position.y / System::TILE_SIZE);
    ChessBoard tempBoard = m_board;
    if(p_activePiece != nullptr)
    {
        if(p_activePiece->IsBlack() == m_bIsBlackTurn)
        {

            int moveResult = p_activePiece->AttemptMove(m_board, screenToBoordCoordinates);
            if (moveResult == 2)
            {
                CapturePiece(screenToBoordCoordinates);
            }
            CalculateBoardMoves();
            DetermineCheckStatus();

            //Tries to move, and if checking is not resolved, do not move
            if((m_bWhiteIsChecked && !m_bIsBlackTurn) || (m_bBlackIsChecked && m_bIsBlackTurn))
            {
                revertBoard(tempBoard);
                return false;
            }

            if(moveResult > 0)
            {
                ConfirmPiece(screenToBoordCoordinates);
                p_activePiece = nullptr;
                return true;
            }
        }
        revertBoard(tempBoard);
    }
    return false;
}

void GameState::ConfirmPiece(sf::Vector2i boardCoords)
{
    sf::Vector2i boardToScreenCoords(boardCoords.x * System::TILE_SIZE + System::X_CENTER_OFFSET + System::TILE_SIZE/2,
        boardCoords.y * System::TILE_SIZE + System::TILE_SIZE/2);
    if(p_activePiece)
    {
        p_activePiece->MovePieceVisual(boardToScreenCoords);
    }
    CalculateBoardMoves();

    m_bIsBlackTurn = !m_bIsBlackTurn;
    DetermineCheckStatus();
    std::cout<<"White is checked: " << m_bWhiteIsChecked<<"\nBlack is checked: "<< m_bBlackIsChecked<<std::endl;
}

void GameState::CapturePiece(sf::Vector2i boordCoords)
{
    for(int i = 0; i < m_pieces.size(); i++)
    {
        if(m_pieces[i]->GetBoardCoordinates() == boordCoords && m_pieces[i] != p_activePiece)
        {
            m_pieces.erase(m_pieces.begin() + i);
        }
    }

}

void GameState::DetermineCheckStatus()
{
    for(const auto& piece : m_pieces)
    {
        for(const auto& move : piece->GetPossibleMoves())
        {
            m_bWhiteIsChecked = false;
            m_bBlackIsChecked = false;
            auto result = static_cast<PieceType>(m_board.GetBoard()[move.y][move.x]);
            if(result == WHITE_KING)
            {
                m_bWhiteIsChecked = true;
                return;
            }
            if(result == BLACK_KING)
            {
                m_bBlackIsChecked = true;
                return;
            }
        }
    }

}

void GameState::CalculateBoardMoves()
{
    for(const auto& piece : m_pieces)
    {
        piece->CalculatePossibleMoves(m_board.GetBoard());
    }
}
