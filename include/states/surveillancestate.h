#ifndef SURVEILLANCESTATE_H
#define SURVEILLANCESTATE_H

#include "operationalstate.h"
#include "include/gimbal/motionmodetype.h"
#include <QObject>

class SurveillanceState : public OperationalState {
    Q_OBJECT
public:
    void enter(StateManager* manager) override;
    void exit(StateManager* mgr, OperationalMode nextMode) override;
    OperationalMode getMode() const override { return OperationalMode::Surveillance; } // Correct mode
    //void onTargetSelected(int targetID);
    //void onManualTrackInitiated() ;
    void setDetectionEnabled(bool enabled);
    void setStabilizationEnabled(bool enabled);

public slots:
    void setMotionMode(MotionModeType modeType);


private:
    StateManager* manager; // Reference to StateManager
    bool detectionEnabled = false;
    bool stabilizationEnabled = false;
};

#endif // SURVEILLANCESTATE_H

