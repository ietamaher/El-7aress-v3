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

public slots:
    //void onTargetPositionUpdated(double azimuth, double elevation);

private:
    //double m_azimuth;
    //double m_elevation;

    float m_azimuthJoystickInput;
    float m_elevationJoystickInput;

    // stabilization corrections
    double m_stabilizationAzimuth;
    double m_stabilizationElevation;
};

#endif // MANUALMOTIONMODE_H

