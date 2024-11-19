#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H

#include <QObject>
#include <QThread>
#include "camerapipeline_day.h"
#include "include/gui/videoglwidget_gl.h"

#include "include/camera/dayCamerainterface.h"
#include "include/camera/nightcamerainterface.h"

//#include "include/camera/camerapipeline_night.h"
#include "include/camera/lensinterface.h"
#include "include/datamodel.h"



class CameraSystem : public QObject {
    Q_OBJECT
public:
    explicit CameraSystem(DataModel *dataModel, QObject *parent = nullptr);
    ~CameraSystem();

    enum ProcessMode {
        IdleMode = 0,
        DetectionMode = 1,
        TrackingMode = 2,
        ManualTrackingMode = 3
    };

    void start();
    void shutdown();
    void switchToDayCamera();
    void switchToNightCamera();
    void setDisplayWidget(VideoGLWidget_gl *widget);

    void zoomIn();
    void zoomOut();
    void resetZoom();
    void toggleDayNightMode();
    void switchCameraMode();

    void setProcessingMode(ProcessMode mode);
    ProcessMode getProcessingMode();
    void setSelectedTrackId(int trackId);




signals:
    void errorOccurred(const QString &error);

    //void newFrameAvailable(uchar4* frame, int width, int height);
    void newFrameAvailable(const QByteArray &frameData, int width, int height);

    void selectedTrackLost(int trackId);
    void trackedIdsUpdated(const QSet<int>& ids);

    void targetPositionUpdated(double azimuth, double elevation);

    // Signals for interface status changes
    void dayCameraInterfaceStatusChanged(bool isConnected);
    void nightCameraInterfaceStatusChanged(bool isConnected);
    void lensInterfaceStatusChanged(bool isConnected);

    void lensResponseReceived(const QString &response);
    void dayResponseReceived(const QByteArray &response);
    void nightResponseReceived(const QByteArray &response);


private slots:
    //void onNewFrameAvailable(uchar4* frame, int width, int height);
    void onNewFrameAvailable(const QByteArray &frameData, int width, int height);

    void onSelectedTrackLost(int trackId);
    void onTrackedIdsUpdated(const QSet<int>& trackIds);

    // Slots to handle status changes from interfaces
    void onDayCameraInterfaceStatusChanged(bool isConnected);
    void onNightCameraInterfaceStatusChanged(bool isConnected);
    void onLensInterfaceStatusChanged(bool isConnected);

    void onDayInterfaceResponseReceived(const QByteArray &response);
    void onNightInterfaceResponseReceived(const QByteArray &response);
    void onLensResponseReceived(const QString &response);

    void onErrorOccurred(const QString &error);
    void onTargetPositionUpdated(double azimuth, double elevation);

private:

    void initializePipelines();
    void initializeCameraInterfaces();
    void onTrackIdSelected(int index);
    void processFrame();
    DataModel *m_dataModel;

    CameraPipelineDay *m_cameraPipelineDay;
    //CameraPipelineNight *m_cameraPipelineNight;
    VideoGLWidget_gl *m_displayWidget;

    DayCameraInterface *m_dayCameraInterface;
    NightCameraInterface *m_nightCameraInterface;
    LensInterface *m_lensInterface;

    bool m_isDayCameraActive;
    ProcessingMode m_processingMode;
    ProcessMode m_processMode;

    QTimer *updateTimer;
    QSet<int> pendingTrackIds;
    bool updatePending = false;

    // Status variables
    bool m_isDayCameraConnected;
    bool m_isNightCameraConnected;
    bool m_isLensConnected;
};

#endif // CAMERASYSTEM_H
