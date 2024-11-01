#ifndef STATUSPANEL_H
#define STATUSPANEL_H

#include <QWidget>
#include <QMap>

class QLabel;
class QVBoxLayout;
class QHBoxLayout;

class StatusPanel : public QWidget {
    Q_OBJECT
public:
    explicit StatusPanel(QWidget *parent = nullptr);

    // Method to set the status of a component
    void setComponentStatus(const QString &componentName, bool status);

private:
    // Map to hold labels for each component
    QMap<QString, QLabel*> m_componentLabels;

    // Icons for statuses
    QPixmap m_greenLed;
    QPixmap m_redLed;

    // Layouts
    QVBoxLayout *m_mainLayout;
};

#endif // STATUSPANEL_H

