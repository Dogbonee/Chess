
#include "StateMachine.h"

int main(int argc, char* argv[])
{
    StateMachine sm;
    sm.ChangeState(MULTIPLAYER_CHESS_STATE);
    sm.StartStateMachine();
    return 0;
}
