#ifndef JOYSTICKHANDLER_H
#define JOYSTICKHANDLER_H

#include <QObject>
#include <QSocketNotifier>
#include <QMap>

class JoystickHandler : public QObject {
    Q_OBJECT
public:
    explicit JoystickHandler(const QString &devicePath, QObject *parent = nullptr);
    ~JoystickHandler();

signals:
    void axisMoved(int axis, int value);
    void buttonPressed(int button, bool pressed);

private slots:
    void readData();

private:
    int m_fd;
    QSocketNotifier *m_notifier;
};

#endif // JOYSTICKHANDLER_H
