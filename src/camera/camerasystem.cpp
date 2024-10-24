#include "include/camera/camerasystem.h"
#include "QDebug"

CameraSystem::CameraSystem(QObject *parent)
    : QObject(parent),
      m_cameraPipelineDay(nullptr),
      m_displayWidget(nullptr),
      m_isDayCameraActive(true),
      m_processingMode(MODE_IDLE)
{
    initializePipelines();
}

CameraSystem::~CameraSystem() {
    if (m_cameraPipelineDay) {
        m_cameraPipelineDay->stop();
        delete m_cameraPipelineDay;
    }
}

void CameraSystem::initializePipelines() {
    int cameraIndex = m_isDayCameraActive ? 0 : 1;
    m_cameraPipelineDay = new CameraPipelineDay(0, this);

    connect(m_cameraPipelineDay, &CameraPipelineDay::newFrameAvailable, this, &CameraSystem::onNewFrameAvailable);
    connect(m_cameraPipelineDay, &CameraPipelineDay::trackedTargetsUpdated, this, &CameraSystem::onTrackedIdsUpdated, Qt::QueuedConnection);
    connect(m_cameraPipelineDay, &CameraPipelineDay::selectedTrackLost, this, &CameraSystem::onSelectedTrackLost);
    //m_cameraPipelineDay->start();
}

void CameraSystem::initializeCameraInterfaces() {
    // Initialize day camera interface
   /* m_dayCameraInterface = new DayCameraInterface();
    m_dayCameraThread = new QThread(this);
    m_dayCameraInterface->moveToThread(m_dayCameraThread);
    m_dayCameraThread->start();

    // Initialize night camera interface
    m_nightCameraInterface = new NightCameraInterface();
    m_nightCameraThread = new QThread(this);
    m_nightCameraInterface->moveToThread(m_nightCameraThread);
    m_nightCameraThread->start();*/

    // Initialize lens interface
    m_lensInterface = new LensInterface();
    m_lensThread = new QThread(this);
    m_lensInterface->moveToThread(m_lensThread);
    m_lensThread->start();

    // Connect signals and slots
    // Handle responses and errors
}

void CameraSystem::start() {
    if (m_cameraPipelineDay) {
        m_cameraPipelineDay->start();
    }
}

void CameraSystem::stop() {
    if (m_cameraPipelineDay) {
        m_cameraPipelineDay->stop();
    }
}

void CameraSystem::switchToDayCamera() {
    if (!m_isDayCameraActive) {
        m_isDayCameraActive = true;
        if (m_cameraPipelineDay) {
            m_cameraPipelineDay->stop();
            delete m_cameraPipelineDay;
            m_cameraPipelineDay = nullptr;
        }
        initializePipelines();
    }
}

void CameraSystem::switchToFLIRCamera() {
    if (m_isDayCameraActive) {
        m_isDayCameraActive = false;
        if (m_cameraPipelineDay) {
            m_cameraPipelineDay->stop();
            delete m_cameraPipelineDay;
            m_cameraPipelineDay = nullptr;
        }
        initializePipelines();
    }
}

void CameraSystem::setDisplayWidget(VideoGLWidget_gl *widget) {
    m_displayWidget = widget;
}

void CameraSystem::onNewFrameAvailable(uchar4* frame, int width, int height) {
    if (m_displayWidget) {
        m_displayWidget->pushFrame(frame, width, height);
    }
}

void CameraSystem::setSelectedTrackId(int trackId) {
    if (m_cameraPipelineDay) {
        m_cameraPipelineDay->setSelectedTrackId(trackId);
    }
}

void CameraSystem::zoomIn() {
    // Implement zoom in command to camera
}

void CameraSystem::zoomOut() {
    // Implement zoom out command to camera
}

void CameraSystem::resetZoom() {
    // Implement reset zoom
}

void CameraSystem::toggleDayNightMode() {
    if (m_isDayCameraActive) {
        switchToFLIRCamera();
    } else {
        switchToDayCamera();
    }
}

void CameraSystem::switchCameraMode() {
    // Implement switch camera mode
}

void CameraSystem::setDetectionMode() {
    m_cameraPipelineDay->setProcessingMode(MODE_DETECTION);
}

void CameraSystem::setProcessingMode(ProcessMode mode)
{

    guint interval;
    switch(mode) {
    case IdleMode:
        m_processingMode = MODE_IDLE;
        interval = 1000;
        break;
    case DetectionMode:
        m_processingMode = MODE_DETECTION;
        interval = 0;
        break;
    case TrackingMode:
        m_processingMode = MODE_TRACKING;
        interval = 0;
        break;
    case ManualTrackingMode:
        m_processingMode = MODE_MANUAL_TRACKING;
        interval = 1000;
        break;
    default:
        // Handle unexpected indices
        m_processingMode = MODE_IDLE;
        interval = 1000;
        qWarning() << "Unknown mode index selected:" << index;
        break;
    }

    // Optional: Log the current mode for debugging
    qDebug() << "Selected Processing Mode:" << m_processingMode;

    // Set the processing mode in the camera pipeline
    m_cameraPipelineDay->setProcessingMode(m_processingMode);
    m_cameraPipelineDay->setPGIEInterval(interval);
}


void CameraSystem::onSelectedTrackLost(int trackId)
{
    emit selectedTrackLost(trackId);
}

void CameraSystem::onTrackedIdsUpdated(const QSet<int> &trackIds)
{
    emit trackedIdsUpdated(trackIds);
}

void CameraSystem::processFrame()
{
    // Capture and process a frame

    // Detect and track targets

    // Calculate target azimuth and elevation based on detection

    double azimuth = 0.0;   // Replace with calculated value
    double elevation = 0.0; // Replace with calculated value

    emit targetPositionUpdated(azimuth, elevation);
}
