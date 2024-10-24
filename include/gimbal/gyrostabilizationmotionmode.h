#ifndef GYROSTABILIZATIONMOTIONMODE_H
#define GYROSTABILIZATIONMOTIONMODE_H

#include "gimbalmotionmode.h"

class GyroStabilizationMotionMode : public GimbalMotionMode {
public:
    void enter(GimbalController* controller) override;
    void exit(GimbalController* controller) override;
    void handleJoystickInput(GimbalController* controller, int axis, float value) override;
    void update(GimbalController* controller) override;
};

#endif // GYROSTABILIZATIONMOTIONMODE_H
