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
        auto leftRook = std::make_shared<Rook>(sf::Vector2i(0,y), y == 0);
        auto rightRook = std::make_shared<Rook>(sf::Vector2i(7,y), y == 0);
        m_pieces.emplace_back(std::make_shared<Knight>(sf::Vector2i(1,y), y == 0));
        m_pieces.emplace_back(std::make_shared<Bishop>(sf::Vector2i(2,y), y == 0));
        m_pieces.emplace_back(std::make_shared<Queen>(sf::Vector2i(3,y), y == 0));

        m_pieces.emplace_back(std::make_shared<Bishop>(sf::Vector2i(5,y), y == 0));
        m_pieces.emplace_back(std::make_shared<Knight>(sf::Vector2i(6,y), y == 0));
        m_pieces.emplace_back(leftRook);
        m_pieces.emplace_back(rightRook);
        m_pieces.emplace_back(std::make_shared<King>(sf::Vector2i(4,y), y == 0, leftRook, rightRook));
    }

    HandlePieceMovement();
    m_bIsBlackTurn = false;

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
        if(p_activePiece != i)
        {
            p_window->draw(*i);
        }
    }
    if(p_activePiece)
    {
        p_window->draw(*p_activePiece);
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

    sf::Vector2i screenToBoordCoordinates((position.x - System::X_CENTER_OFFSET) / System::TILE_SIZE, position.y / System::TILE_SIZE);
    auto moves = CullMoves();
    p_activePiece->ReplacePossibleMoves(moves);
    if(std::find(moves.begin(), moves.end(), screenToBoordCoordinates) != moves.end())
    {

        if(p_activePiece->AttemptMove(m_board, screenToBoordCoordinates) == 2)
        {
            CapturePiece(screenToBoordCoordinates);
        }
        ConfirmPiece(screenToBoordCoordinates);
        return true;
    }
    p_activePiece->MovePieceVisual(sf::Vector2i(m_lastPieceCoords));
    return false;
}

std::vector<sf::Vector2i> GameState::CullMoves()
{
    HandlePieceMovement();
    std::vector<sf::Vector2i> culledMoves;
    auto tempBoard = m_board;
    auto tempPos = p_activePiece->GetBoardCoordinates();
    auto moves = p_activePiece->GetPossibleMoves();

    if(p_activePiece->IsBlack() != m_bIsBlackTurn)
    {
        return {};
    }
    for(auto move : moves)
    {
        if(p_activePiece->GetPieceType() == BLACK_KING || p_activePiece->GetPieceType() == WHITE_KING)
        {
            auto kingMove = move.x - p_activePiece->GetBoardCoordinates().x;
            if(abs(kingMove) == 2)
            {
                p_activePiece->AttemptMove(m_board, sf::Vector2i(p_activePiece->GetBoardCoordinates().x + kingMove/2, p_activePiece->GetBoardCoordinates().y));
                CalculateBoardMoves();
                DetermineCheckStatus();
                if((m_bWhiteIsChecked && !m_bIsBlackTurn) || (m_bBlackIsChecked && m_bIsBlackTurn))
                {
                    m_board = tempBoard;
                    p_activePiece->SetPiece(tempPos);
                    CalculateBoardMoves();
                    DetermineCheckStatus();
                    continue;
                }
            }
        }
        if(p_activePiece->AttemptMove(m_board, move) == 2)
        {
            CalculateBoardMoves();
            DetermineCheckStatus(move);
        }else
        {
            CalculateBoardMoves();
            DetermineCheckStatus();
        }
        if(!(m_bWhiteIsChecked && !m_bIsBlackTurn) && !(m_bBlackIsChecked && m_bIsBlackTurn))
        {
            culledMoves.emplace_back(move);
        }
        m_board = tempBoard;
        p_activePiece->SetPiece(tempPos);
        CalculateBoardMoves();
        DetermineCheckStatus();
    }
    return culledMoves;


}



void GameState::ConfirmPiece(sf::Vector2i boardCoords)
{
    p_activePiece->SetHasMoved();

    SyncVisualsWithBoard(); //TODO: Only move active piece and castling piece
    /*
    sf::Vector2i boardToScreenCoords(boardCoords.x * System::TILE_SIZE + System::X_CENTER_OFFSET + System::TILE_SIZE/2,
        boardCoords.y * System::TILE_SIZE + System::TILE_SIZE/2);
    if(p_activePiece)
    {
        p_activePiece->MovePieceVisual(boardToScreenCoords);
    }
    */
    HandlePieceMovement();
    m_bIsBlackTurn = !m_bIsBlackTurn;
    CheckWinCondition();
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

void GameState::DetermineCheckStatus(sf::Vector2i exceptionBoardCoords)
{
    for(const auto& piece : m_pieces)
    {
        if(piece->GetBoardCoordinates() == exceptionBoardCoords && piece != p_activePiece)
        {
            continue;
        }
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

void GameState::HandlePieceMovement()
{
    CalculateBoardMoves();
    DetermineCheckStatus();
}

void GameState::SyncVisualsWithBoard()
{
    //This function was implemented to solve the problem of the rook visual not moving when castling. This is bad, as it unnecessarily
    //refreshes all pieces and must be called every turn to be effective. FIX ASAP
    for(const auto& piece : m_pieces)
    {
        sf::Vector2i boardToScreenCoords(piece->GetBoardCoordinates().x * System::TILE_SIZE + System::X_CENTER_OFFSET + System::TILE_SIZE/2,
        piece->GetBoardCoordinates().y * System::TILE_SIZE + System::TILE_SIZE/2);
        piece->MovePieceVisual(boardToScreenCoords);
    }
}

void GameState::CheckWinCondition()
{
    bool checkmate = true;
    for(const auto& piece : m_pieces)
    {
        if(piece->IsBlack() != m_bIsBlackTurn)continue;
        p_activePiece = piece;
        if(!CullMoves().empty())
        {
            checkmate = false;
        }
    }
    if(checkmate) Checkmate();
    p_activePiece = nullptr;
}

void GameState::Checkmate()
{
    std::cout<< (m_bIsBlackTurn ? "White" : "Black") << " has won the game!\n";
}
