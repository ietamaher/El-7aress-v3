#ifndef EMERGENCYOVERRIDESTATE_H
#define EMERGENCYOVERRIDESTATE_H

#include "include/states/operationalstate.h"
#include <QObject>

class EmergencyOverrideState : public OperationalState {
    Q_OBJECT
public:
    void enter(StateManager* manager) override;
    void exit(StateManager* mgr, OperationalMode nextMode) override;
    OperationalMode getMode() const override { return OperationalMode::SystemError; }
};

#endif // EMERGENCYOVERRIDESTATE_H
