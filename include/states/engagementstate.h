#ifndef ENGAGEMENTSTATE_H
#define ENGAGEMENTSTATE_H

#include "operationalstate.h"
#include <QObject>


class EngagementState : public OperationalState {
    Q_OBJECT
public:
    void enter(StateManager* manager) override;
    void exit(StateManager* mgr, OperationalMode nextMode) override;
    OperationalMode getMode() const override { return OperationalMode::Engagement; }
};

#endif // ENGAGEMENTSTATE_H
