#ifndef OPERATIONALSTATE_H
#define OPERATIONALSTATE_H

#include <QObject>
#include "operationalmode.h"

class StateManager;

class OperationalState : public QObject {
    Q_OBJECT

public:
    OperationalState(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~OperationalState() {}

    virtual void enter(StateManager* manager) = 0;
    virtual void exit(StateManager* mgr, OperationalMode nextMode) = 0;
    virtual OperationalMode getMode() const = 0;
};

#endif // OPERATIONALSTATE_H

