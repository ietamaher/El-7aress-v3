#ifndef TRACKINGSTATE_H
#define TRACKINGSTATE_H

#include "operationalstate.h"

class TrackingState : public OperationalState {
public:
    void enter(StateManager* manager) override;
    void exit(StateManager* manager) override;
    OperationalMode getMode() const override { return OperationalMode::Tracking; }
};

#endif // TRACKINGSTATE_H
