#ifndef OPERATIONALSTATE_H
#define OPERATIONALSTATE_H

#include "include/states/operationalmode.h"

class StateManager;

class OperationalState {
public:
    virtual void enter(StateManager* mgr) = 0;
    virtual void exit(StateManager* mgr, OperationalMode nextMode) = 0;
    virtual OperationalMode getMode() const = 0;
    virtual ~OperationalState() {}
};

#endif // OPERATIONALSTATE_H
