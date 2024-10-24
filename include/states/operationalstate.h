#ifndef OPERATIONALSTATE_H
#define OPERATIONALSTATE_H

#include "operationalmode.h"

class StateManager; // Forward declaration

class OperationalState {
public:
    virtual ~OperationalState() {}
    virtual void enter(StateManager* manager) = 0;
    virtual void exit(StateManager* manager) = 0;
    virtual OperationalMode getMode() const = 0;
};

#endif // OPERATIONALSTATE_H
