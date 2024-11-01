#ifndef OPERATIONALMODE_H
#define OPERATIONALMODE_H

enum class OperationalMode {
    Idle,           // System is inactive but ready to activate
    Surveillance,   // Continuous monitoring of the environment
    Tracking,       // Following identified targets
    Engagement,     // Engaging and neutralizing threats
    EmergencyOverride, // Added for additional safety
    SystemError         // Added for error handling
};

#endif // OPERATIONALMODE_H

