//
// Created by 24crickenbach on 5/13/2024.
//

#include "MultiplayerChessState.h"

MultiplayerChessState::MultiplayerChessState(StateMachine *p_sm, sf::RenderWindow *p_rw) : ChessState(p_sm, p_rw)
{
    std::srand(std::time(nullptr));
}

void MultiplayerChessState::HandleKeyboardInput(sf::Keyboard::Key key)
{
    ChessState::HandleKeyboardInput(key);
    switch(key)
    {
        case sf::Keyboard::S:
            CreateServer();
        break;
        case sf::Keyboard::C:
            CreateClient();
        break;
    }
}

void MultiplayerChessState::ConfirmPiece(sf::Vector2i boardCoords)
{
    ChessState::ConfirmPiece(boardCoords);
    //ChessState::ConfirmPiece switches m_bIsBlackTurn, so we have to take the opposite of its current state
    if(m_bPlayerIsBlackPiece == !m_bIsBlackTurn)
    {
        SendMove({p_activePiece->GetPieceType(), m_pieceStartingPosition, boardCoords});
    }

    MovePacket packet = ReceiveMove();
    for(const auto& piece : m_pieces)
    {
        if(piece->GetPieceType() == packet.piece && piece->GetBoardCoordinates() == m_pieceStartingPosition)
        {
            p_activePiece = piece;
            if(CheckSpot(packet.endingPosition))
            {
                std::cout<<"Moved piece\n";
            }
            break;
        }
    }

}

void MultiplayerChessState::CreateServer()
{
    std::cout<<"Creating Server\n";
    if(m_listener.listen(60000) != sf::Socket::Done)
    {
        std::cout<<"Error listening for connection\n";
    }

    if(m_listener.accept(m_socket) != sf::Socket::Done)
    {
        std::cout<<"Error accepting connection\n";
    }

    m_bPlayerIsBlackPiece = std::rand() % 2;
    std::cout<<"Local player is " << (m_bPlayerIsBlackPiece ? "Black" : "White") << '\n';
    SendData(std::to_string(!m_bPlayerIsBlackPiece));

    if(m_bPlayerIsBlackPiece)ReceiveMove();
}

void MultiplayerChessState::CreateClient()
{
    std::cout<<"Creating Client\n";
    if(m_socket.connect("127.0.0.1", 60000) != sf::Socket::Done)
    {
        std::cout<<"Could not connect to server\n";
    }
    std::string data = ReceiveData();
    try
    {
        m_bPlayerIsBlackPiece = std::stoi(data);
        std::cout<<"Local player is " << (m_bPlayerIsBlackPiece ? "Black" : "White") << '\n';
    }catch(std::exception& e)
    {
        std::cout<<"Invalid data received: " << data << std::endl;
        exit(1);
    }
    if(m_bPlayerIsBlackPiece)ReceiveMove();
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

MovePacket MultiplayerChessState::ReceiveMove()
{
    MovePacket packet;
    sf::Packet networkPacket;
    if(m_socket.receive(networkPacket) != sf::Socket::Done)
    {
        std::cout<<"Error when receiving packet\n";
    }
    int piece;
    networkPacket >> piece >> packet.startingPosition.x >> packet.startingPosition.y
    >> packet.endingPosition.x >> packet.endingPosition.y;
    packet.piece = static_cast<PieceType>(piece);
    std::cout<<"Received Move\n";
    return packet;
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
    sf::Packet packet;
    std::string data;
    sf::Socket::Status status = m_socket.receive(packet);

    if(status != sf::Socket::Done && status != sf::Socket::Partial)
    {
        std::cout << "Error when receiving packet\n";
    }

    packet >> data;
    return data;
}
