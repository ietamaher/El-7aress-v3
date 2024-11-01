#ifndef SYSTEMERRORSTATE_H
#define SYSTEMERRORSTATE_H

#include "include/states/operationalstate.h"
#include <QObject>

class SystemErrorState : public OperationalState {
    Q_OBJECT
public:
    void enter(StateManager* manager) override;
    void exit(StateManager* mgr, OperationalMode nextMode) override;
    OperationalMode getMode() const override { return OperationalMode::SystemError; }
};

#endif // SYSTEMERRORSTATE_H
