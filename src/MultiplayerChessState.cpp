//
// Created by 24crickenbach on 5/13/2024.
//

#include "MultiplayerChessState.h"

MultiplayerChessState::MultiplayerChessState(StateMachine *p_sm, sf::RenderWindow *p_rw) : ChessState(p_sm, p_rw),
m_bSocketIsReady(false), m_bShouldSendMove(false)
{
    std::srand(std::time(nullptr));
    //m_socket.setBlocking(false);
    //m_listener.setBlocking(false);

}

MultiplayerChessState::~MultiplayerChessState()
{
    m_connectionThread.join();
}

void MultiplayerChessState::Update()
{
    ChessState::Update();
    MovePacket packet;
    if(ReceiveMove(packet))
    {
        std::cout<<"Received Move\n";
        ProcessReceivedMove(packet);
    }

}

void MultiplayerChessState::HandleKeyboardInput(sf::Keyboard::Key key)
{
    ChessState::HandleKeyboardInput(key);
    switch(key)
    {
        case sf::Keyboard::S:
            m_connectionThread = std::thread(&MultiplayerChessState::CreateServer, this);
        break;
        case sf::Keyboard::C:
            m_connectionThread = std::thread(&MultiplayerChessState::CreateClient, this);
        break;
    }
}

bool MultiplayerChessState::CheckSpot(sf::Vector2i position)
{
    if(m_bPlayerIsBlackPiece == m_bIsBlackTurn)
    {
        return ChessState::CheckSpot(position);
    }
    return ChessState::CheckSpot(sf::Vector2i(-1,-1));
}

void MultiplayerChessState::ConfirmPiece(sf::Vector2i boardCoords)
{
    ChessState::ConfirmPiece(boardCoords);
    if(!m_bShouldSendMove)
    {
        m_bShouldSendMove = true;
        return;
    }
    MovePacket move(p_activePiece->GetPieceType(), m_pieceStartingPosition, boardCoords);
    SendMove(move);
}


bool MultiplayerChessState::ProcessReceivedMove(MovePacket move)
{
    auto tempPiece = p_activePiece;
    for(const auto& piece : m_pieces)
    {
        if(piece->GetPieceType() == move.piece && piece->GetBoardCoordinates() == move.startingPosition)
        {
            p_activePiece = piece;
            m_bShouldSendMove = false;
            auto success = ChessState::CheckSpot(move.endingPosition);
            p_activePiece = tempPiece;
            return success;
        }
    }
    p_activePiece = tempPiece;
    return false;
}

void MultiplayerChessState::CreateServer()
{
    std::cout<<"Creating Server\n";


    if(m_listener.listen(60000) != sf::Socket::Done)
    {
        std::cout<<"Error listening for client\n";
    }
    if(m_listener.accept(m_socket) != sf::Socket::Done)
    {
        std::cout<<"Error accepting client\n";
    }
    std::cout<<"Connected to client\n";

    m_bPlayerIsBlackPiece = std::rand() % 2;
    m_bShouldSendMove =! m_bPlayerIsBlackPiece;
    std::cout<<"Local player is " << (m_bPlayerIsBlackPiece ? "Black" : "White") << "\n";
    SendData(std::to_string(!m_bPlayerIsBlackPiece));



    m_socket.setBlocking(false);
    m_bSocketIsReady = true;


}

void MultiplayerChessState::CreateClient()
{
    std::cout<<"Creating Client\n";
    if(m_socket.connect("127.0.0.1", 60000) != sf::Socket::Done)
    {
        std::cout<<"Error connecting to server\n";
    }
    std::cout<<"Connected to server\n";
    m_bSocketIsReady = true;
    try
    {
        m_bPlayerIsBlackPiece = std::stoi(ReceiveData());
        m_bShouldSendMove =! m_bPlayerIsBlackPiece;
        std::cout<<"Local player is " << (m_bPlayerIsBlackPiece ? "Black" : "White") << "\n";
    }catch(std::exception e)
    {
        std::cout<<"Invalid data received\n";
        exit(1);
    }
    m_socket.setBlocking(false);

}

void MultiplayerChessState::SendMove(MovePacket packet)
{
    sf::Packet networkPacket;
    networkPacket << packet.piece << packet.startingPosition.x << packet.startingPosition.y
    << packet.endingPosition.x << packet.endingPosition.y;
    sf::Socket::Status status = m_socket.send(networkPacket);
    while(status == sf::Socket::Partial)
    {
        status = m_socket.send(networkPacket);
    }
    if(status != sf::Socket::Done)
    {
        std::cout<<"Error when sending packet";
    }


}

bool MultiplayerChessState::ReceiveMove(MovePacket& packet)
{
    if(!m_bSocketIsReady)return false;
    sf::Packet networkPacket;
    auto status = m_socket.receive(networkPacket);
    if(status == sf::Socket::NotReady)
    {
        return false;
    }
    if(status != sf::Socket::Done && status != sf::Socket::Partial)
    {
        return false;
    }
    int piece;
    networkPacket >> piece >> packet.startingPosition.x >> packet.startingPosition.y
    >> packet.endingPosition.x >> packet.endingPosition.y;
    packet.piece = static_cast<PieceType>(piece);
    return true;
}

void MultiplayerChessState::SendData(std::string data)
{
    sf::Packet packet;
    packet << data;
    if(m_socket.send(packet) != sf::Socket::Done)
    {
        std::cout<<"Error when sending packet\n";
    }

}

std::string MultiplayerChessState::ReceiveData()
{
    if(!m_bSocketIsReady)
    {
        std::cout<<"ReceiveData called on an unready socket\n";
        return "";
    }
    sf::Packet packet;
    std::string data;
    sf::Socket::Status status = m_socket.receive(packet);

    if(status != sf::Socket::Done && status != sf::Socket::NotReady)
    {
        std::cout << "Error when receiving packet\n";
    }

    packet >> data;
    return data;
}
