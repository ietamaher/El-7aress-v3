#ifndef SURVEILLANCESTATE_H
#define SURVEILLANCESTATE_H

#include "operationalstate.h"

class SurveillanceState : public OperationalState {
public:
    void enter(StateManager* manager) override;
    void exit(StateManager* manager) override;
    OperationalMode getMode() const override { return OperationalMode::Surveillance; }
};

#endif // SURVEILLANCESTATE_H
