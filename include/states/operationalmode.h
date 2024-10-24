#ifndef OPERATIONALMODE_H
#define OPERATIONALMODE_H

// Enumeration representing the different operational modes of the RCWS
enum class OperationalMode {
    Idle,          // System is inactive but ready to activate
    Surveillance,  // Continuous monitoring of the environment
    Detection,     // Actively searching for potential threats
    Tracking,      // Following identified targets
    Engagement     // Engaging and neutralizing threats
};

#endif // OPERATIONALMODE_H
