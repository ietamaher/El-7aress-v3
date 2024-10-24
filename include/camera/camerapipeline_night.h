#ifndef CAMERA_PIPELINE_NIGHT_H
#define CAMERA_PIPELINE_NIGHT_H

#include <QObject>
#include <QMessageBox>
#include <gst/gst.h>
#include <gst/app/gstappsink.h>
#include <gst/video/videooverlay.h>


#include <gst/gl/gstglcontext.h>
#include <gst/gl/gstgldisplay.h>
#include <gst/gl/gl.h>
#include <gst/gl/gstglcontext.h>
#include <gst/gl/gstgldisplay.h>
#include "gstnvdsmeta.h"
#include <glib.h>
#include <glib-object.h>

#include <QOpenGLWidget>
#include <QtGui/QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include "nvdsmeta.h"
#include "nvdsinfer.h"
#include "nvdsinfer_custom_impl.h"
#include "nvds_tracker_meta.h"

#include <cuda_gl_interop.h>
#include <cuda_runtime.h>

#include <QMutex>
#include <QMetaType>
#include <set>

// Declare std::set<int> as a metatype
Q_DECLARE_METATYPE(std::set<int>)

// Define constants
//#define UNTRACKED_OBJECT_ID (guint64)(-1)
#define PGIE_CLASS_ID_PERSON 0  // Adjust based on your class IDs
#define NVDS_USER_OBJ_MISC_META (nvds_get_user_meta_type("NVIDIA.NvDsUserObjMiscMeta"))

enum ProcessingMode {
    MODE_NONE1,
    MODE_DETECTION,
    MODE_TRACKING,
    MODE_MANUAL_TRACKING
};

struct ManualObject {
    int class_id;
    float confidence;
    std::string label;
    float left;
    float top;
    float width;
    float height;
};

struct TrackDSInfo
{
    int trackId;
    int framesSinceLastSeen;
};


class CameraPipelineNight : public QObject
{
    Q_OBJECT
public:
    explicit CameraPipelineNight(int cameraIndex, QObject *parent = nullptr);
    ~CameraPipelineNight();

    void start();
    void stop();
    void setPGIEInterval(guint interval);
    void setProcessingMode(ProcessingMode mode);
    void selectTarget(int trackId);
    void setTracker();
    bool setTrackState;
    QSet<int> previousTrackIds;
    int selectedTrackId = -1; // Initialize to -1 when no object is selected
    bool manualTrackingEnabled = false;
    struct {
        float left;
        float top;
        float width;
        float height;
    } manualBBox;
    QMutex mutex; // Mutex to protect shared variables

    // Modified setter for selectedTrackId
    void setSelectedTrackId(int trackId);

    // Access selectedTrackId in osd_sink_pad_buffer_probe
    int getSelectedTrackId();


signals:
    void newFrameAvailable(uchar4* frame, int width, int height);
    void trackedTargetsUpdated(const QSet<int> &trackIds);
    void trackingResult(QRect updatedBoundingBox);
    void selectedTrackLost(int trackId);
    void trackedIdsUpdated(const QSet<int>& ids);

public slots:
    //void setSelectedTrackId(int trackId);

private:
    void buildPipeline();
    static GstFlowReturn on_new_sample(GstAppSink *sink, gpointer data);
    static GstPadProbeReturn osd_sink_pad_buffer_probe(GstPad *pad, GstPadProbeInfo *info, gpointer u_data);
    //static GstPadProbeReturn nvtracker_src_pad_buffer_probe(GstPad *pad, GstPadProbeInfo *info, gpointer u_data);
    //static GstPadProbeReturn nvtracker_sink_pad_buffer_probe(GstPad *pad, GstPadProbeInfo *info, gpointer u_data);
    //static GstPadProbeReturn pgie_src_pad_buffer_probe(GstPad *pad, GstPadProbeInfo *info, gpointer u_data);
    static void clear_obj_meta_list(NvDsFrameMeta *frame_meta);
    GstElement *pipeline;
    GstElement *appsink;
    GstElement *source;
    GstElement     *sink, *transform, *streammux, *aspectratiocrop, *queue;
    GstElement *capsfilter1, *videocrop, *videoscale, *capsfilter3, *capsfilter2, *nvvidconvsrc1, *nvvidconvsrc2;
    GstElement  *pgie, *tracker, *nvvidconvsrc3, *jpegparse, *decoder, *nvvidconv_post, *nvosd;
    GstCaps *caps3, *caps1, *caps1bis, *caps2, *caps4;
    GstMessage *msg;
    GError *error = NULL;
    //guint bus_watch_id;
    // Other pipeline elements
    GstBus *bus;
    guint busWatchId;
    int cameraIndex;
    ProcessingMode currentMode;
    // Variables for GL context sharing
    GstGLDisplay *glDisplay;
    GstGLContext *glContext;

    //DcfTrackerVPI *_tracker;
    //KltTracker *_tracker;
    bool trackerInitialized;
    QRect updatedBBox;
    NvOSD_RectParams *bboxRect;

    std::map<int, TrackDSInfo> activeTracks;
    const int maxFramesToKeep = 30; // Adjust based on your requirements
    ManualObject manual_bbox;
    bool is_object_initialized = false;
    bool is_metadata_injected = false;
    int tracker_frames = 0;
};

#endif // CAMERA_PIPELINE_NIGHT_H

