
#include "StateMachine.h"

int main(int argc, char* argv[])
{
    StateMachine sm;
    sm.ChangeState(DEFAULT_STATE);
    sm.StartStateMachine();
    return 0;
}
