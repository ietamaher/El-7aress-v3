#ifndef RADARTRACKINGMOTIONMODE_H
#define RADARTRACKINGMOTIONMODE_H

#include "gimbalmotionmode.h"
#include "include/sensor/radarinterface.h"
#include <QObject>

class RadarTrackingMotionMode : public QObject, public GimbalMotionMode {
    Q_OBJECT
public:
    void enter(GimbalController* controller) override;
    void exit(GimbalController* controller) override;
    void handleJoystickInput(GimbalController* controller, int axis, float value) override;
    void update(GimbalController* controller) override;

private slots:
    void onRadarTargetUpdated(const RadarTarget &target);

private:
    double m_targetAzimuth;
    double m_targetElevation;
};

#endif // RADARTRACKINGMOTIONMODE_H
