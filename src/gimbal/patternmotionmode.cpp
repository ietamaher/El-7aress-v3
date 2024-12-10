#include "include/gimbal/patternmotionmode.h"
#include "include/gimbal/gimbalcontroller.h"

#include <QTimer>
#include <QDebug>

PatternMotionMode::PatternMotionMode(QObject* parent)
    : QObject(parent),
    m_patternTimer(nullptr),
    m_currentAzimuth(0.0),
    m_direction(1.0)
{
}

PatternMotionMode::~PatternMotionMode() {
    if (m_patternTimer) {
        m_patternTimer->stop();
        delete m_patternTimer;
    }
}

void PatternMotionMode::enter(GimbalController* controller) {
    qDebug() << "Entering Pattern Motion Mode";
    // Start pattern execution
    m_patternTimer = new QTimer(this);
    connect(m_patternTimer, &QTimer::timeout, [this, controller]() {
        executePattern(controller);
    });
    m_patternTimer->start(100); // Adjust interval as needed
}

void PatternMotionMode::exit(GimbalController* controller) {
    qDebug() << "Exiting Pattern Motion Mode";
    // Stop pattern execution
    if (m_patternTimer) {
        m_patternTimer->stop();
        delete m_patternTimer;
        m_patternTimer = nullptr;
    }
}

void PatternMotionMode::handleJoystickInput(GimbalController* controller, int axis, float value) {
    // Optionally adjust pattern parameters based on joystick input
}

void PatternMotionMode::update(GimbalController* controller) {
    // No action needed here if the pattern is driven by the timer
}

void PatternMotionMode::executePattern(GimbalController* controller) {
    // Implement the pattern logic
    const double MIN_AZIMUTH = -45.0;
    const double MAX_AZIMUTH = 45.0;
    const double STEP = 1.0; // degrees per interval

    m_currentAzimuth += m_direction * STEP;
    if (m_currentAzimuth >= MAX_AZIMUTH) {
        m_currentAzimuth = MAX_AZIMUTH;
        m_direction = -1.0;
    } else if (m_currentAzimuth <= MIN_AZIMUTH) {
        m_currentAzimuth = MIN_AZIMUTH;
        m_direction = 1.0;
    }

    // Keep elevation constant or implement similar pattern
    double targetElevation = 0.0;

    // Send position command
    controller->sendPositionCommand(m_currentAzimuth, targetElevation);
}
