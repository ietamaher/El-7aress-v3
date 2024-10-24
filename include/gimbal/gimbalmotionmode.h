#ifndef GIMBALMOTIONMODE_H
#define GIMBALMOTIONMODE_H

class GimbalController;

class GimbalMotionMode {
public:
    virtual ~GimbalMotionMode() {}
    virtual void enter(GimbalController* controller) = 0;
    virtual void exit(GimbalController* controller) = 0;
    virtual void handleJoystickInput(GimbalController* controller, int axis, float value) = 0;
    virtual void update(GimbalController* controller) = 0; // Called periodically
};

#endif // GIMBALMOTIONMODE_H

