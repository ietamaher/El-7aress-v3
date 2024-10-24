#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H

#include <QObject>
#include <QThread>
#include "camerapipeline_day.h"
#include "include/gui/videoglwidget_gl.h"

#include "include/camera/dayCamerainterface.h"
#include "include/camera/nightcamerainterface.h"
#include "include/camera/lensinterface.h"

class CameraSystem : public QObject {
    Q_OBJECT
public:
    explicit CameraSystem(QObject *parent = nullptr);
    ~CameraSystem();

    enum ProcessMode {
        IdleMode = 0,
        DetectionMode = 1,
        TrackingMode = 2,
        ManualTrackingMode = 3
    };

    void start();
    void stop();
    void switchToDayCamera();
    void switchToFLIRCamera();

    void zoomIn();
    void zoomOut();
    void resetZoom();
    void toggleDayNightMode();
    void switchCameraMode();
    void setDetectionMode();

    void setDisplayWidget(VideoGLWidget_gl *widget);

    void setProcessingMode(ProcessMode mode);
    void setSelectedTrackId(int trackId);

signals:
    void newFrameAvailable(uchar4* frame, int width, int height);
    void selectedTrackLost(int trackId);
    void trackedIdsUpdated(const QSet<int>& ids);

    void targetPositionUpdated(double azimuth, double elevation);

private slots:
    void onNewFrameAvailable(uchar4* frame, int width, int height);
    void onSelectedTrackLost(int trackId);
    void onTrackedIdsUpdated(const QSet<int>& trackIds);

private:
    CameraPipelineDay *m_cameraPipelineDay;
    VideoGLWidget_gl *m_displayWidget;

    DayCameraInterface *m_dayCameraInterface;
    NightCameraInterface *m_nightCameraInterface;
    LensInterface *m_lensInterface;

    QThread *m_dayCameraThread;
    QThread *m_nightCameraThread;
    QThread *m_lensThread;

    bool m_isDayCameraActive;
    QTimer *updateTimer;
    QSet<int> pendingTrackIds;
    bool updatePending = false;
    void initializePipelines();
    void initializeCameraInterfaces();


    void onTrackIdSelected(int index);
    ProcessingMode m_processingMode;
    void processFrame();


};

#endif // CAMERASYSTEM_H
