#ifndef MANUALMOTIONMODE_H
#define MANUALMOTIONMODE_H

#include "gimbalmotionmode.h"
#include <QObject>

#define STABILIZATION_FACTOR  0.2;

class ManualMotionMode : public QObject, public GimbalMotionMode {
    Q_OBJECT
public:
    explicit ManualMotionMode(QObject *parent = nullptr);

    void enter(GimbalController* controller) override;
    void exit(GimbalController* controller) override;
    void handleJoystickInput(GimbalController* controller, int axis, float value) override;
    void update(GimbalController* controller) override;


private:
    double m_azimuth;
    double m_elevation;

    float m_azimuthInput;
    float m_elevationInput;

    // stabilization corrections
    double m_stabilizationAzimuth;
    double m_stabilizationElevation;
};

#endif // MANUALMOTIONMODE_H

