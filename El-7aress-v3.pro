QT       += core gui  serialbus serialport   openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17

# Include paths for OpenCV
INCLUDEPATH += "/usr/include/opencv4"
INCLUDEPATH += /usr/include/eigen3      #sudo apt-get install libeigen3-dev if not present

INCLUDEPATH +="/usr/include/glib-2.0"
INCLUDEPATH +="/usr/include/gstreamer-1.0"
CONFIG += link_pkgconfig
PKGCONFIG += gstreamer-1.0
PKGCONFIG += gstreamer-video-1.0
# Include OpenCV
PKGCONFIG += opencv4

INCLUDEPATH += /usr/include/freetype2

CONFIG += link_pkgconfig
PKGCONFIG += gstreamer-1.0
PKGCONFIG += gstreamer-video-1.0
PKGCONFIG += gstreamer-gl-1.0

LIBS += -lfreetype

INCLUDEPATH += /usr/include/opencv4/opencv2
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_videoio #-lopencv_objdetect -lopencv_tracking

# Include the paths to VPI and OpenCV
INCLUDEPATH += /opt/nvidia/vpi2/include

# Link against the VPI library
LIBS += -L/usr/lib/aarch64-linux-gnu -lnvvpi
# for PC linux
INCLUDEPATH +="/usr/local/cuda-12.2/targets/x86_64-linux/include"
INCLUDEPATH +="/opt/nvidia/deepstream/deepstream-6.4/sources/includes"

#for jetson device
#INCLUDEPATH +="/usr/local/cuda-11.4/targets/aarch64-linux/include"
#INCLUDEPATH +="/opt/nvidia/deepstream/deepstream-6.3/sources/includes"


# Library paths and OpenCV libraries
#LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc
# for PC linux
LIBS += -L/usr/local/cuda-12.2/lib64 -lcudart
LIBS += -L/opt/nvidia/deepstream/deepstream-6.4/lib -lnvdsgst_meta -lnvds_meta
LIBS+=-L"/usr/lib/x86_64-linux-gnu/gstreamer-1.0" -lgstxvimagesink -L"/usr/lib/x86_64-linux-gnu" -lgstbase-1.0 -lgstreamer-1.0 -lglib-2.0 -lgobject-2.0
LIBS += -L/usr/lib/aarch64-linux-gnu/tegra -lnvbufsurface -lnvbufsurftransform

LIBS+=-L"/usr/lib/x86_64-linux-gnu/gstreamer-1.0" -lgstxvimagesink -L"/usr/lib/x86_64-linux-gnu" -lgstbase-1.0 -lgstreamer-1.0 -lglib-2.0 -lgobject-2.0


#for jetson device
#LIBS += -L/usr/local/cuda-11.4/lib64 -lcudart
#LIBS += -L/opt/nvidia/deepstream/deepstream-6.3/lib -lnvdsgst_meta -lnvds_meta
L#IBS += -L/usr/lib/aarch64-linux-gnu/tegra -lnvbufsurface -lnvbufsurftransform
#LIBS+=-L"/usr/lib/aarch64-linux-gnu/gstreamer-1.0" -lgstxvimagesink -L"/usr/lib/x86_64-linux-gnu" -lgstbase-1.0 -lgstreamer-1.0 -lglib-2.0 -lgobject-2.0

# Add Jetson inference and utils libraries
#LIBS += -L/usr/local/lib -ljetson-inference -ljetson-utils

# Include the necessary directories for headers
#INCLUDEPATH += /usr/local/include/jetson-inference
#INCLUDEPATH += /usr/local/include/jetson-utils


LIBS += -lmodbus # -lboson -lFSLP
# Library paths and libraries
LIBS += -L/usr/local/lib #-lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc

# GStreamer and plugins libraries
LIBS += -lgstreamer-1.0 -lgstapp-1.0 -lgstbase-1.0 -lgobject-2.0 -lglib-2.0

SOURCES += \
    $$PWD/src/camera/camerapipeline_day.cpp \
    $$PWD/src/camera/camerapipeline_night.cpp \
    $$PWD/src/camera/camerasystem.cpp \
    $$PWD/src/camera/lensinterface.cpp \
    $$PWD/src/camera/dayCamerainterface.cpp \
    $$PWD/src/camera/nightcamerainterface.cpp \
    $$PWD/src/comm/communicationsystem.cpp \
    #$$PWD/src/comm/serialportmanager.cpp \
    $$PWD/src/comm/joystickhandler.cpp \
    $$PWD/src/comm/plcstationdriver.cpp \
    $$PWD/src/comm/modbusinterface.cpp \
    $$PWD/src/gimbal/radartrackingmotionmode.cpp \
    $$PWD/src/gimbal/gimbalcontroller.cpp \
    #$$PWD/src/gimbal/gimbalmotordriver.cpp \
    $$PWD/src/gimbal/patternmotionmode.cpp \
    $$PWD/src/gimbal/manualmotionmode.cpp \
    $$PWD/src/gimbal/gyrostabilizationmotionmode.cpp \
    $$PWD/src/gimbal/targettrackingmotionmode.cpp \
    #$$PWD/src/gimbal/mduinocontroller.cpp \
    $$PWD/src/gimbal/servodriverinterface.cpp \
    $$PWD/src/gimbal/plcservointerface.cpp \
    $$PWD/src/main.cpp \
    $$PWD/src/datamodel.cpp \
    $$PWD/src/gui/mainwindow.cpp \
    $$PWD/src/gui/videoglwidget_gl.cpp \
    $$PWD/src/sensor/sensorsystem.cpp \
    $$PWD/src/sensor/radarinterface.cpp \
    $$PWD/src/sensor/gyrointerface.cpp \
    $$PWD/src/sensor/lrfinterface.cpp \
    $$PWD/src/sensor/plcstationsensorsinterface.cpp \
    $$PWD/src/sensor/plcpanelsensorsinterface.cpp \
    $$PWD/src/states/statemanager.cpp \
    $$PWD/src/states/surveillancestate.cpp \
    $$PWD/src/states/idlestate.cpp \
    $$PWD/src/states/trackingstate.cpp \
    $$PWD/src/states/emergencyoverridestate.cpp \
    $$PWD/src/states/systemerrorstate.cpp \
    $$PWD/src/states/engagementstate.cpp \
    $$PWD/src/weapon/weaponsystem.cpp \
    $$PWD/src/weapon/servoactuatorinterface.cpp \
    $$PWD/src/weapon/plcsolenoidinterface.cpp \
    $$PWD/src/gui/statuspanel.cpp \
    $$PWD/src/states/operationalmode.cpp \
    $$PWD/src/gui/custommenudialog.cpp \
    $$PWD/src/sensor/plcremotestationsensorsinterface.cpp



HEADERS += \
    $$PWD/include/camera/camerapipeline_day.h \
    $$PWD/include/camera/camerapipeline_night.h \
    $$PWD/include/camera/camerasystem.h \
    $$PWD/include/comm/communicationsystem.h \
    $$PWD/include/comm/plcstationdriver.h \
    $$PWD/include/camera/dayCamerainterface.h \
    $$PWD/include/states/emergencyoverridestate.h \
    $$PWD/include/states/systemerrorstate.h \
    $$PWD/include/states/engagementstate.h \
    $$PWD/include/gimbal/gimbalcontroller.h \
    $$PWD/include/gimbal/gimbalmotionmode.h \
    #$$PWD/include/gimbal/gimbalmotordriver.h \
    #$$PWD/include/gimbal/mduinocontroller.h \
    $$PWD/include/gimbal/servodriverinterface.h \
    $$PWD/include/gimbal/radartrackingmotionmode.h \
    $$PWD/include/gimbal/plcservointerface.h \
    $$PWD/include/sensor/gyrointerface.h \
    $$PWD/include/gimbal/gyrostabilizationmotionmode.h \
    $$PWD/include/states/idlestate.h \
    $$PWD/include/comm/joystickhandler.h \
    $$PWD/include/camera/lensinterface.h \
    $$PWD/include/sensor/lrfinterface.h \
    $$PWD/include/gui/mainwindow.h \
    $$PWD/include/gimbal/manualmotionmode.h \
    $$PWD/include/comm/modbusinterface.h \
    $$PWD/include/states/statemanager.h \
    $$PWD/include/camera/nightcamerainterface.h \
    $$PWD/include/states/operationalmode.h \
    $$PWD/include/states/operationalstate.h \
    $$PWD/include/gimbal/patternmotionmode.h \
    $$PWD/include/sensor/sensorsystem.h \
    $$PWD/include/sensor/radarinterface.h \
    $$PWD/include/sensor/plcstationsensorsinterface.h \
    $$PWD/include/sensor/plcpanelsensorsinterface.h \
    #$$PWD/include/comm/serialportmanager.h \
    $$PWD/include/states/surveillancestate.h \
    $$PWD/include/gimbal/targettrackingmotionmode.h \
    $$PWD/include/states/trackingstate.h \
    $$PWD/include/gui/videoglwidget_gl.h \
    $$PWD/include/weapon/weaponsystem.h \
    $$PWD/include/weapon/servoactuatorinterface.h \
    $$PWD/include/weapon/plcsolenoidinterface.h\
    $$PWD/include/gui/statuspanel.h \
    $$PWD/include/gimbal/motionmodetype.h\
    $$PWD/include/datamodel.h \
    $$PWD/include/gui/custommenudialog.h \
    $$PWD/include/sensor/plcremotestationsensorsinterface.h



FORMS += \
    mainwindow.ui



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    assets/icons/green.png \
    assets/icons/red.png

RESOURCES += \
    icons.qrc
