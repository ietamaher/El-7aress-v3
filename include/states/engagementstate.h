#ifndef ENGAGEMENTSTATE_H
#define ENGAGEMENTSTATE_H

#include "operationalstate.h"
#include "include/gimbal/motionmodetype.h"

#include <QObject>


class EngagementState : public OperationalState {
    Q_OBJECT
public:
    EngagementState();
    void enter(StateManager* manager) override;
    void exit(StateManager* manager, OperationalMode nextMode) override;
    OperationalMode getMode() const override { return OperationalMode::Engagement; }

    // Override setMotionMode to prevent changing motion modes in Engagement Mode
    void setMotionMode(MotionModeType modeType) ;

private:
    StateManager* manager;
    MotionModeType m_previousMotionMode;
};

#endif // ENGAGEMENTSTATE_H
