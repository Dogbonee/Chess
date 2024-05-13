//
// Created by 24crickenbach on 5/13/2024.
//

#ifndef MULTIPLAYERCHESSSTATE_H
#define MULTIPLAYERCHESSSTATE_H
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



    void HandleKeyboardInput(sf::Keyboard::Key key) override;

    bool m_bPlayerIsBlackPiece;

    void ConfirmPiece(sf::Vector2i boardCoords) override;


    //Multiplayer
    sf::TcpSocket m_socket;
    sf::TcpListener m_listener;


    void CreateServer();
    void CreateClient();
    void SendMove(MovePacket packet);
    MovePacket ReceiveMove();
    void SendData(std::string data);
    std::string ReceiveData();



public:
    MultiplayerChessState(StateMachine* p_sm, sf::RenderWindow* p_rw);

};



#endif //MULTIPLAYERCHESSSTATE_H
