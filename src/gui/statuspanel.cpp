#include "../../include/gui/statuspanel.h"

//#include "statuspanel.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>

StatusPanel::StatusPanel(QWidget *parent)
    : QWidget(parent),
    m_greenLed(":/assets/icons/green.png"),
    m_redLed(":/assets/icons/red.png"),
    m_mainLayout(new QVBoxLayout(this))
{
    // List of components
    QStringList components = {
        "Camera 1",
        "Camera 2",
        "Joystick",
        "LRF",
        "Radar",
        "Gyro",
        "PLC1 Communication",
        "PLC2 Communication",
        "Stepper Motor 1",
        "Stepper Motor 2",
        "Actuator",
        "Lens Control"
    };

    for (const QString &component : components) {
        QHBoxLayout *hLayout = new QHBoxLayout();
        QLabel *iconLabel = new QLabel();
        QLabel *nameLabel = new QLabel(component);

        // Set default status to red
        iconLabel->setPixmap(m_redLed);
        //iconLabel->setText("NO");

        hLayout->addWidget(iconLabel);
        hLayout->addWidget(nameLabel);
        hLayout->addStretch();

        m_mainLayout->addLayout(hLayout);

        // Store the icon label in the map
        m_componentLabels[component] = iconLabel;
    }

    m_mainLayout->addStretch();
}

void StatusPanel::setComponentStatus(const QString &componentName, bool status)
{
    if (m_componentLabels.contains(componentName)) {
        QLabel *iconLabel = m_componentLabels[componentName];
        if (status) {
            iconLabel->setPixmap(m_greenLed);
            //iconLabel->setText("OK");

        } else {
            iconLabel->setPixmap(m_redLed);
            //iconLabel->setText("NO");

        }
    }
}

