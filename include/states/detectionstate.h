#ifndef DETECTIONSTATE_H
#define DETECTIONSTATE_H

#include "operationalstate.h"

class DetectionState : public OperationalState {
public:
    void enter(StateManager* manager) override;
    void exit(StateManager* manager) override;
    OperationalMode getMode() const override { return OperationalMode::Detection; }
};

#endif // DETECTIONSTATE_H
