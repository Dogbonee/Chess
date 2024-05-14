//
// Created by 24crickenbach on 5/13/2024.
//

#ifndef MULTIPLAYERCHESSSTATE_H
#define MULTIPLAYERCHESSSTATE_H
#include <thread>

#include "ChessState.h"

struct MovePacket {
    PieceType piece;
    sf::Vector2i startingPosition;
    sf::Vector2i endingPosition;
    MovePacket() = default;
    MovePacket(PieceType piece, sf::Vector2i startingPos, sf::Vector2i endingPos)
    {
        this->piece = piece;
        startingPosition = startingPos;
        endingPosition = endingPos;
    }
};


class MultiplayerChessState : public ChessState{


    void Update() override;
    void HandleKeyboardInput(sf::Keyboard::Key key) override;
    bool CheckSpot(sf::Vector2i position) override;
    void ConfirmPiece(sf::Vector2i boardCoords) override;

    bool m_bPlayerIsBlackPiece;
    bool m_bShouldSendMove;

    bool ProcessReceivedMove(MovePacket move);


    //Multiplayer
    sf::TcpSocket m_socket;
    sf::TcpListener m_listener;

    std::thread m_connectionThread;
    bool m_bSocketIsReady;


    void CreateServer();
    void CreateClient();
    void SendMove(MovePacket packet);
    bool ReceiveMove(MovePacket& packet);
    void SendData(std::string data);
    std::string ReceiveData();



public:
    MultiplayerChessState(StateMachine* p_sm, sf::RenderWindow* p_rw);
    ~MultiplayerChessState() override;

protected:

};



#endif //MULTIPLAYERCHESSSTATE_H
