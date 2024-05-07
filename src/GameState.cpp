//
// Created by hunde on 3/30/2024.
//

#include "GameState.h"

#include "Pieces/Bishop.h"
#include "Pieces/King.h"
#include "Pieces/Knight.h"
#include "Pieces/Queen.h"
#include "Pieces/Rook.h"


GameState::GameState(StateMachine* p_sm, sf::RenderWindow* p_rw) : State(p_sm, p_rw), m_bIsBlackTurn(false), m_bWhiteIsChecked(false), m_bBlackIsChecked(false),
m_bIsWhitePromoting(false), m_bIsBlackPromoting(false), m_whitePromotion(false), m_blackPromotion(true){

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

    if(m_bIsWhitePromoting)
    {
        p_window->draw(m_whitePromotion);
    }
    if(m_bIsBlackPromoting)
    {
        p_window->draw(m_blackPromotion);
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
            case sf::Event::MouseMoved: {
                sf::Vector2i mousePos(event.mouseMove.x, event.mouseMove.y);
                if(p_activePiece != nullptr && !(m_bIsWhitePromoting || m_bIsBlackPromoting))
                {
                    DragPiece(mousePos);
                    break;
                }

                if(std::any_of( m_pieces.begin(), m_pieces.end(),
                    [mousePos](auto& i){return i->ManageCollision(mousePos);})
                    || (m_bIsWhitePromoting && m_whitePromotion.ManageCollision(mousePos))
                    || (m_bIsBlackPromoting && m_blackPromotion.ManageCollision(mousePos)))
                {
                    p_window->setMouseCursor(System::Hand_Cursor);
                }else
                {
                    p_window->setMouseCursor(System::Arrow_Cursor);
                }
            }
            break;
            case sf::Event::MouseButtonPressed: {
                sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    if(p_activePiece)
                    {
                        if(m_bIsWhitePromoting)
                            PromotePiece(m_whitePromotion.ManageCollision(mousePos));
                        else if(m_bIsBlackPromoting)
                            PromotePiece(m_blackPromotion.ManageCollision(mousePos));
                    }
                    for(const auto& i : m_pieces)
                    {
                        if(i->ManageCollision(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))
                        {
                            p_activePiece = i;
                            m_lastPieceCoords = p_activePiece->getPosition();
                        }

                    }
                }
            }
            break;
            case sf::Event::MouseButtonReleased:
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    if(p_activePiece)
                    {
                        DoTurn();
                    }
                }
            case sf::Event::KeyPressed:

                HandleKeyboardInput(event.key.code);
            break;
            default:
                break;
        }
    }
}

bool GameState::ShouldPromote()
{
    if(p_activePiece->GetPieceType() == WHITE_PAWN && p_activePiece->GetBoardCoordinates().y == 0)
    {
        return true;
    }
    if(p_activePiece->GetPieceType() == BLACK_PAWN && p_activePiece->GetBoardCoordinates().y == 7)
    {
        return true;
    }
    return false;
}

void GameState::PromotePiece(PieceType promotionType)
{
    switch(promotionType)
    {
        case WHITE_KNIGHT:
        m_pieces[std::distance(m_pieces.begin(), std::find(m_pieces.begin(), m_pieces.end(), p_activePiece))] =
                std::make_shared<Knight>(p_activePiece->GetBoardCoordinates(), false);
        break;
        case WHITE_BISHOP:
            m_pieces[std::distance(m_pieces.begin(), std::find(m_pieces.begin(), m_pieces.end(), p_activePiece))] =
                    std::make_shared<Bishop>(p_activePiece->GetBoardCoordinates(), false);
        break;
        case WHITE_ROOK:
            m_pieces[std::distance(m_pieces.begin(), std::find(m_pieces.begin(), m_pieces.end(), p_activePiece))] =
                    std::make_shared<Rook>(p_activePiece->GetBoardCoordinates(), false);
        break;
        case WHITE_QUEEN:
            m_pieces[std::distance(m_pieces.begin(), std::find(m_pieces.begin(), m_pieces.end(), p_activePiece))] =
                    std::make_shared<Queen>(p_activePiece->GetBoardCoordinates(), false);
        break;
        case BLACK_KNIGHT:
            m_pieces[std::distance(m_pieces.begin(), std::find(m_pieces.begin(), m_pieces.end(), p_activePiece))] =
                    std::make_shared<Knight>(p_activePiece->GetBoardCoordinates(), true);
        break;
        case BLACK_BISHOP:
            m_pieces[std::distance(m_pieces.begin(), std::find(m_pieces.begin(), m_pieces.end(), p_activePiece))] =
                    std::make_shared<Bishop>(p_activePiece->GetBoardCoordinates(), true);
        break;
        case BLACK_ROOK:
            m_pieces[std::distance(m_pieces.begin(), std::find(m_pieces.begin(), m_pieces.end(), p_activePiece))] =
                    std::make_shared<Rook>(p_activePiece->GetBoardCoordinates(), true);
        break;
        case BLACK_QUEEN:
            m_pieces[std::distance(m_pieces.begin(), std::find(m_pieces.begin(), m_pieces.end(), p_activePiece))] =
                    std::make_shared<Queen>(p_activePiece->GetBoardCoordinates(), true);
        break;

        default:
            break;


    }
    p_activePiece = nullptr;
    m_bIsWhitePromoting = false;
    m_bIsBlackPromoting = false;
}

void GameState::DoTurn()
{

    if(!(m_bIsWhitePromoting || m_bIsBlackPromoting))
    {
        CheckSpot(p_activePiece->getPosition());
    }
    if(ShouldPromote())
    {
        !m_bIsBlackTurn ? m_bIsBlackPromoting = true : m_bIsWhitePromoting = true;
        if(m_bIsBlackPromoting)
        {
            m_blackPromotion.SetUIPosition(sf::Vector2f(p_activePiece->GetBoardCoordinates().x * System::TILE_SIZE + System::X_CENTER_OFFSET - System::TILE_SIZE/4, System::SCREEN_HEIGHT-System::TILE_SIZE*3/2));
        }
        if(m_bIsWhitePromoting)
        {
            m_whitePromotion.SetUIPosition(sf::Vector2f(p_activePiece->GetBoardCoordinates().x * System::TILE_SIZE + System::X_CENTER_OFFSET - System::TILE_SIZE/4, 0));
        }
    }else
    {
        p_activePiece = nullptr;
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

    auto revert = [this](auto tempBoard, auto tempPos)
    {
        m_board = tempBoard;
        p_activePiece->SetPiece(tempPos);
        CalculateBoardMoves();
        DetermineCheckStatus();
    };

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
                if((m_bWhiteIsChecked && !m_bIsBlackTurn) || (m_bBlackIsChecked && m_bIsBlackTurn))
                {
                    revert(tempBoard, tempPos);
                    continue;
                }
                p_activePiece->AttemptMove(m_board, sf::Vector2i(p_activePiece->GetBoardCoordinates().x + kingMove/2, p_activePiece->GetBoardCoordinates().y));
                CalculateBoardMoves();
                DetermineCheckStatus();
                if((m_bWhiteIsChecked && !m_bIsBlackTurn) || (m_bBlackIsChecked && m_bIsBlackTurn))
                {
                    revert(tempBoard, tempPos);
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
        revert(tempBoard, tempPos);
    }
    return culledMoves;


}



void GameState::ConfirmPiece(sf::Vector2i boardCoords)
{
    p_activePiece->SetHasMoved();

    SyncVisualsWithBoard(); //TODO: Only move active piece and castling piece
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
    auto tempActivePiecePtr = p_activePiece;
    bool checkmate = true;
    for(const auto& piece : m_pieces)
    {
        if(piece->IsBlack() != m_bIsBlackTurn)
        {
            continue;
        }
        p_activePiece = piece;
        if(!CullMoves().empty())
        {
            checkmate = false;
        }
    }
    if(checkmate)
    {
        Checkmate();
    }
    p_activePiece = tempActivePiecePtr;
}

void GameState::Checkmate()
{
    std::cout<< (m_bIsBlackTurn ? "White" : "Black") << " has won the game!\n";
}
