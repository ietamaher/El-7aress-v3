#ifndef COMMUNICATIONSYSTEM_H
#define COMMUNICATIONSYSTEM_H

#include <QObject>

class CommunicationSystem : public QObject {
    Q_OBJECT
public:
    explicit CommunicationSystem(QObject *parent = nullptr);

    void increaseVolume();
    void decreaseVolume();
    void toggleMute();
    void selectChannel(int channel);
    void openCommunicationPanel();

private:
    int m_volumeLevel;
    bool m_muted;
    int m_currentChannel;
};

#endif // COMMUNICATIONSYSTEM_H
