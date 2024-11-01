#ifndef IDLESTATE_H
#define IDLESTATE_H

#include "operationalstate.h"
#include <QObject>

class IdleState : public OperationalState {
    Q_OBJECT
public:
    void enter(StateManager* manager) override;
    void exit(StateManager* mgr, OperationalMode nextMode) override;
    OperationalMode getMode() const override { return OperationalMode::Idle; }
};

#endif // IDLESTATE_H
