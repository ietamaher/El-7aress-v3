#ifndef SURVEILLANCESTATE_H
#define SURVEILLANCESTATE_H

#include "operationalstate.h"
#include "include/gimbal/motionmodetype.h"
#include <QObject>

/**
 * @class SurveillanceState
 * @brief Implements the surveillance mode of the system.
 *
 * This class handles the gimbal and camera system configurations
 * required for surveillance.
 */
class SurveillanceState : public OperationalState {
    Q_OBJECT
public:
    /**
     * @brief Enters the surveillance mode.
     * @param mgr Pointer to the state manager.
     */
    void enter(StateManager* manager) override;

    /**
     * @brief Exits the surveillance mode.
     * @param mgr Pointer to the state manager.
     * @param nextMode The operational mode to transition to.
     */
    void exit(StateManager* mgr, OperationalMode nextMode) override;

    OperationalMode getMode() const override { return OperationalMode::Surveillance; } // Correct mode
    void setDetectionEnabled(bool enabled);

public slots:
    /**
     * @brief Sets the motion mode for the gimbal in surveillance state.
     * @param modeType The type of motion mode to set.
     */
    void setMotionMode(MotionModeType modeType);


private:
    StateManager* manager; // Reference to StateManager
    bool detectionEnabled = false;
 };

#endif // SURVEILLANCESTATE_H

