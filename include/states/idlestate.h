#ifndef IDLESTATE_H
#define IDLESTATE_H

#include "operationalstate.h"

class IdleState : public OperationalState {
public:
    void enter(StateManager* manager) override;
    void exit(StateManager* manager) override;
    OperationalMode getMode() const override { return OperationalMode::Idle; }
};

#endif // IDLESTATE_H
