#ifndef PATTERNMOTIONMODE_H
#define PATTERNMOTIONMODE_H

#include <QObject>
#include "gimbalmotionmode.h"
#include <QTimer>

class PatternMotionMode : public QObject, public GimbalMotionMode {
    Q_OBJECT
public:
    explicit PatternMotionMode(QObject* parent = nullptr);
    ~PatternMotionMode();

    void enter(GimbalController* controller) override;
    void exit(GimbalController* controller) override;
    void handleJoystickInput(GimbalController* controller, int axis, float value) override;
    void update(GimbalController* controller) override;

private:
    void executePattern(GimbalController* controller);

    QTimer* m_patternTimer;
    // Variables to manage the pattern
    double m_currentAzimuth;
    double m_direction;
};

#endif // PATTERNMOTIONMODE_H
