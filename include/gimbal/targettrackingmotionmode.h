#ifndef TARGETTRACKINGMOTIONMODE_H
#define TARGETTRACKINGMOTIONMODE_H

#include "gimbalmotionmode.h"
#include <QObject>

class TargetTrackingMotionMode : public QObject, public GimbalMotionMode {
    Q_OBJECT
public:
    void enter(GimbalController* controller) override;
    void exit(GimbalController* controller) override;
    void handleJoystickInput(GimbalController* controller, int axis, float value) override;
    void update(GimbalController* controller) override;

public slots:
    void onTargetPositionUpdated(double azimuth, double elevation);

private:
    double m_targetAzimuth;
    double m_targetElevation;
};

#endif // TARGETTRACKINGMOTIONMODE_H
