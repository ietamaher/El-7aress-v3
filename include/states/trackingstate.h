#ifndef TRACKINGSTATE_H
#define TRACKINGSTATE_H

#include "operationalstate.h"
#include "include/gimbal/motionmodetype.h"

#include <QObject>

class TrackingState : public OperationalState {
    Q_OBJECT
public:
    TrackingState(bool isManualTracking = false);
    void enter(StateManager* manager) override;
    void exit(StateManager* mgr, OperationalMode nextMode) override;
    OperationalMode getMode() const override { return OperationalMode::Tracking; }

    //void setTargetID(int targetID);
    void setManualTracking(bool manual);
    void onEngageCommand();
    void onCancelTracking();
    void onTargetLost();

public slots:
    void setMotionMode(MotionModeType modeType);

private:
    StateManager* manager;
    int m_targetID = -1;
    bool m_isManualTracking = false;
};

#endif // TRACKINGSTATE_H
