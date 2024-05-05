//
// Created by hunde on 3/30/2024.
//

#include "StateMachine.h"

#include "GameState.h"
#include "System.h"


StateMachine::StateMachine() : m_window(sf::VideoMode(System::SCREEN_WIDTH, System::SCREEN_HEIGHT), "Default Name", sf::Style::Fullscreen)
{
    System::LoadResources();
    m_states.emplace_back(new GameState(this, &m_window));
    m_window.setFramerateLimit(60);
    //m_window.setVisible(false);
}

StateMachine::~StateMachine()
{

}

void StateMachine::UpdateCurrentState()
{
    p_currentState->Update();
}

void StateMachine::ChangeState(STATES state)
{
    try
    {
        p_currentState = m_states.at(state);
    }catch (std::exception& e)
    {
        std::cout << "State does not exist\n";
        exit(1);
    }
}

void StateMachine::StartStateMachine()
{
    if(p_currentState == nullptr)
    {
        std::cout << "A state must be set before starting the state machine\n";
        exit(1);
    }
    while(m_window.isOpen())
    {
        UpdateCurrentState();
    }
}


