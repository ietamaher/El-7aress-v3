#include "include/camera/camerasystem.h"
#include "QDebug"

CameraSystem::CameraSystem(DataModel *dataModel, QObject *parent)
    : QObject(parent),
    m_dataModel(dataModel),
    m_cameraPipelineDay(nullptr),
    //m_cameraPipelineNight(nullptr),
    m_displayWidget(nullptr),
    m_dayCameraInterface(new DayCameraInterface(this)),
    m_nightCameraInterface(new NightCameraInterface(this)),
    m_lensInterface(new LensInterface(this)),
    m_isDayCameraActive(true),
    m_processingMode(MODE_IDLE),
    m_processMode(IdleMode),
    m_isDayCameraConnected(false),
    m_isNightCameraConnected(false),
    m_isLensConnected(false)
{
    initializeCameraInterfaces();
    initializePipelines();
    qDebug() << "CameraSystem constructor called";

}

CameraSystem::~CameraSystem() {
    shutdown();

}

void CameraSystem::initializePipelines() {
    // Initialize camera pipelines based on active camera
    if (m_isDayCameraActive) {
        m_cameraPipelineDay = new CameraPipelineDay(m_dataModel, this);
        connect(m_cameraPipelineDay, &CameraPipelineDay::newFrameAvailable, this, &CameraSystem::onNewFrameAvailable);
        connect(m_cameraPipelineDay, &CameraPipelineDay::trackedTargetsUpdated, this, &CameraSystem::onTrackedIdsUpdated, Qt::QueuedConnection);
        connect(m_cameraPipelineDay, &CameraPipelineDay::selectedTrackLost, this, &CameraSystem::onSelectedTrackLost);
        connect(m_cameraPipelineDay, &CameraPipelineDay::targetPositionUpdated, this, &CameraSystem::onTargetPositionUpdated);
    }/* else {
        m_cameraPipelineNight = new CameraPipelineNight(1, this);
        connect(m_cameraPipelineNight, &CameraPipelineNight::newFrameAvailable, this, &CameraSystem::onNewFrameAvailable);
        connect(m_cameraPipelineNight, &CameraPipelineNight::trackedTargetsUpdated, this, &CameraSystem::onTrackedIdsUpdated, Qt::QueuedConnection);
        connect(m_cameraPipelineNight, &CameraPipelineNight::selectedTrackLost, this, &CameraSystem::onSelectedTrackLost);
    }*/
}

void CameraSystem::initializeCameraInterfaces() {
    // Open serial ports for camera interfaces
    if (!m_dayCameraInterface->openSerialPort("/dev/pts/35")) {
        qWarning() << "Failed to open day camera serial port.";
            // Handle failure
    }
    if (!m_nightCameraInterface->openSerialPort("/dev/pts/32")) {
        qWarning() << "Failed to open night camera serial port.";
    }
    if (!m_lensInterface->openSerialPort("/dev/pts/29")) {
        qWarning() << "Failed to open lens serial port.";
    }


    if (m_dayCameraInterface) {
        connect(m_dayCameraInterface, &DayCameraInterface::responseReceived, this, &CameraSystem::onDayInterfaceResponseReceived);
        //connect(m_dayCameraInterface, &DayCameraInterface::errorOccurred, this, &CameraSystem::onErrorOccurred);

        connect(m_dayCameraInterface, &DayCameraInterface::statusChanged, this, &CameraSystem::onDayCameraInterfaceStatusChanged);

    }
    if (m_nightCameraInterface) {
        connect(m_nightCameraInterface, &NightCameraInterface::responseReceived, this, &CameraSystem::onNightInterfaceResponseReceived);
        //connect(m_nightCameraInterface, &NightCameraInterface::errorOccurred, this, &CameraSystem::onErrorOccurred);

        connect(m_nightCameraInterface, &NightCameraInterface::statusChanged, this, &CameraSystem::onNightCameraInterfaceStatusChanged);
    }
    if (m_lensInterface) {
        connect(m_lensInterface, &LensInterface::responseReceived, this, &CameraSystem::onLensResponseReceived);
        //connect(m_lensInterface, &LensInterface::errorOccurred, this, &CameraSystem::onErrorOccurred);

        connect(m_lensInterface, &LensInterface::statusChanged, this, &CameraSystem::onLensInterfaceStatusChanged);
    }
}

void CameraSystem::onDayInterfaceResponseReceived(const QByteArray &response){
      emit dayResponseReceived(response);
}
void CameraSystem::onNightInterfaceResponseReceived(const QByteArray &response){
    emit nightResponseReceived(response);
}
void CameraSystem::onLensResponseReceived(const QString &response){
    emit lensResponseReceived(response);
}

// Slots to handle status changes
void CameraSystem::onDayCameraInterfaceStatusChanged(bool isConnected) {
    m_isDayCameraConnected = isConnected;
    emit dayCameraInterfaceStatusChanged(isConnected);

    qDebug() << "Day Camera Interface connection status changed:" << isConnected;

    // Handle reconnection logic if necessary
}

void CameraSystem::onNightCameraInterfaceStatusChanged(bool isConnected) {
    m_isNightCameraConnected = isConnected;
    emit nightCameraInterfaceStatusChanged(isConnected);

    qDebug() << "Night Camera Interface connection status changed:" << isConnected;

    // Handle reconnection logic if necessary
}

void CameraSystem::onLensInterfaceStatusChanged(bool isConnected) {
    m_isLensConnected = isConnected;
    emit lensInterfaceStatusChanged(isConnected);

    qDebug() << "Lens Interface connection status changed:" << isConnected;

    // Handle reconnection logic if necessary
}

void CameraSystem::onTargetPositionUpdated(double azimuth, double elevation) {
    emit targetPositionUpdated(azimuth, elevation);

}
void CameraSystem::start() {
    if (m_isDayCameraActive && m_cameraPipelineDay) {
        m_cameraPipelineDay->start();
    } /*else if (!m_isDayCameraActive && m_cameraPipelineNight) {
        //m_cameraPipelineNight->start();
    }*/
}

void CameraSystem::shutdown() {
    if (m_cameraPipelineDay) {
        m_cameraPipelineDay->stop();
        delete m_cameraPipelineDay;
        m_cameraPipelineDay = nullptr;

    }
    /*if (m_cameraPipelineNight) {
        delete m_cameraPipelineNight;
    }*/
    if (m_dayCameraInterface) {
        m_dayCameraInterface->shutdown();
    }
    if (m_nightCameraInterface) {
        m_nightCameraInterface->shutdown();
    }
    if (m_lensInterface) {
        m_lensInterface->shutdown();
    }

    qDebug() << "CameraSystem has been shut down.";
}

void CameraSystem::switchToDayCamera() {
    if (!m_isDayCameraActive) {
        shutdown();
        m_isDayCameraActive = true;
       // delete m_cameraPipelineNight;
        //m_cameraPipelineNight = nullptr;
        initializePipelines();
        start();
    }
}

void CameraSystem::switchToNightCamera() {
    if (m_isDayCameraActive) {
        shutdown();
        m_isDayCameraActive = false;
        delete m_cameraPipelineDay;
        m_cameraPipelineDay = nullptr;
        initializePipelines();
        start();
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



void CameraSystem::zoomIn() {
    if (m_isDayCameraActive) {
        m_dayCameraInterface->zoomIn();
    } else {
        m_nightCameraInterface->setDigitalZoom(2); // Example zoom level
    }
}

void CameraSystem::zoomOut() {
    if (m_isDayCameraActive) {
        m_dayCameraInterface->zoomOut();
    } else {
        m_nightCameraInterface->setDigitalZoom(1); // Reset zoom
    }
}

void CameraSystem::resetZoom() {
    if (m_isDayCameraActive) {
        m_dayCameraInterface->zoomStop();
    } else {
        m_nightCameraInterface->setDigitalZoom(1); // Reset zoom
    }
}

void CameraSystem::toggleDayNightMode() {
    if (m_isDayCameraActive) {
        switchToNightCamera();
    } else {
        switchToDayCamera();
    }
}


void CameraSystem::switchCameraMode() {
    // Implement switch camera mode
}

void CameraSystem::setProcessingMode(ProcessMode mode)
{
    m_processMode = mode;
    guint interval;
    switch(m_processMode) {
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
       qDebug() << "Unknown mode index selected:" << index;
        break;
    }

    // Optional: Log the current mode for debugging
    qDebug() << "Selected Processing Mode:" << m_processingMode;

    // Set the processing mode in the camera pipeline
    m_cameraPipelineDay->setProcessingMode(m_processingMode);
    m_cameraPipelineDay->setPGIEInterval(interval);
}

CameraSystem::ProcessMode CameraSystem::getProcessingMode()
{
    return m_processMode;
}

void CameraSystem::setSelectedTrackId(int trackId) {
    if (m_cameraPipelineDay) {
        m_cameraPipelineDay->setSelectedTrackId(trackId);
    }
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

void CameraSystem::onErrorOccurred(const QString &error) {
    // Optionally process the error before emitting
    qDebug() << "SensorSystem received errorOccurred:" << error;
    emit errorOccurred(error);
}
