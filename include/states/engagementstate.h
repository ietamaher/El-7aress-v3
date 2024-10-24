#ifndef ENGAGEMENTSTATE_H
#define ENGAGEMENTSTATE_H

#include "operationalstate.h"

class EngagementState : public OperationalState {
public:
    void enter(StateManager* manager) override;
    void exit(StateManager* manager) override;
    OperationalMode getMode() const override { return OperationalMode::Engagement; }
};

#endif // ENGAGEMENTSTATE_H
