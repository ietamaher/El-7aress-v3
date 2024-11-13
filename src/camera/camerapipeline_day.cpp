#include "include/camera/camerapipeline_day.h"
#include <QDebug>
#include <gst/gl/gl.h>
#include <chrono>
#include <iostream>

CameraPipelineDay::CameraPipelineDay(DataModel *dataModel, QObject *parent)
    : QObject(parent),
    m_dataModel(dataModel),
    pipeline(nullptr),
    appsink(nullptr),
    source(nullptr),
    bus(nullptr),
    busWatchId(0),
    cameraIndex(cameraIndex),
    currentMode(MODE_TRACKING),
    updatedBBox(0,0,0,0),
    glDisplay(nullptr),
    glContext(nullptr),
    trackerInitialized(false),
    setTrackState(false)
    //_tracker(nullptr)
{
    gst_init(nullptr, nullptr);
    //VPIBackend backend = VPI_BACKEND_CUDA; // or VPI_BACKEND_PVA based on your requirements
    int maxTargets = 1;
     //_tracker = new DcfTrackerVPI(backend, maxTargets);
    ManualObject manual_bbox;
    manual_bbox.left = 430;
    manual_bbox.top = 320;
    manual_bbox.width = 100;
    manual_bbox.height = 100;

    connect(m_dataModel, &DataModel::reticleStyleChanged, this, &CameraPipelineDay::onReticleStyleChanged);
    qDebug() << "CameraSystem instance created:" << this;

 }

CameraPipelineDay::~CameraPipelineDay()
{
    stop();
}

void CameraPipelineDay::start()
{

     buildPipeline();
}

void CameraPipelineDay::stop()
{
    if (!pipeline)
        return;
    gst_object_unref (GST_OBJECT (pipeline));
    // Disconnect signal handlers and remove probes
    if (appsink) {
        g_signal_handlers_disconnect_by_func(appsink, (gpointer)on_new_sample, this);
        gst_element_set_state(appsink, GST_STATE_NULL);
        gst_object_unref(appsink);
        appsink = nullptr;
    }

    if (osd_sink_pad && osd_probe_id > 0) {
        gst_pad_remove_probe(osd_sink_pad, osd_probe_id);
        gst_object_unref(osd_sink_pad);
        osd_sink_pad = nullptr;
    }

    // Set the pipeline to NULL state
    gst_element_set_state(pipeline, GST_STATE_NULL);

    // Remove bus watch before unref'ing the bus
    if (bus && bus_watch_id > 0) {
        g_source_remove(bus_watch_id);
        bus_watch_id = 0;
    }

    // Unref the bus
    if (bus) {
        gst_object_unref(bus);
        bus = nullptr;
    }

    // Unref the pipeline
    gst_object_unref(pipeline);
    pipeline = nullptr;
}

void CameraPipelineDay::onReticleStyleChanged(const QString &style)
{
    // Update the reticle rendering parameters based on the new style
    m_currentReticleStyle = style;
    // Trigger a re-render if necessary
}

void CameraPipelineDay::renderReticle(NvDsDisplayMeta *display_meta)
{
    // Use m_currentReticleStyle to determine which reticle to draw
    if (m_currentReticleStyle == "Crosshair") {
        // Draw crosshair reticle
    } else if (m_currentReticleStyle == "Dot") {
        // Draw dot reticle
    } else if (m_currentReticleStyle == "Circle") {
        // Draw circle reticle
    } else {
        // Draw default reticle
    }
}

void CameraPipelineDay::setTracker()
{

    trackerInitialized = false;
    setTrackState = true;
    // Adjust pipeline elements based on mode
}
void CameraPipelineDay::setProcessingMode(ProcessingMode mode)
{
    currentMode = mode;
    // Adjust pipeline elements based on mode
}

void CameraPipelineDay::selectTarget(int trackId)
{
    // Implement logic to focus on the selected target
}

void CameraPipelineDay::buildPipeline()
{

    // Create the elements
    source = gst_element_factory_make("v4l2src", "source");
    g_object_set(G_OBJECT(source), "device", "/dev/video0", NULL);
    //g_object_set(G_OBJECT(source), "device", currentCameraIndex == 0 ? "/dev/video0" : "/dev/video1", NULL);

    sink = gst_element_factory_make ("glimagesink", "src_glimagesink");

    capsfilter1 = gst_element_factory_make ("capsfilter", "caps-filter1");
    caps1 = gst_caps_new_simple("image/jpeg",
                                "format", G_TYPE_STRING, "MJPG",
                                "width", G_TYPE_INT, 1280,
                                "height", G_TYPE_INT, 720,
                                "framerate", GST_TYPE_FRACTION, 30, 1,
                                NULL);
    g_object_set (G_OBJECT (capsfilter1), "caps", caps1, NULL);
    gst_caps_unref (caps1);
    jpegparse = gst_element_factory_make("jpegparse", "jpegparse");
    decoder = gst_element_factory_make ("jpegdec", "jpegdec-decoder");

    aspectratiocrop = gst_element_factory_make("aspectratiocrop", "aspect-ratio-crop");
    g_assert(aspectratiocrop != NULL);

    // Create a GstFraction value for the aspect ratio (4/3)
    GstStructure *s;
    GValue fraction = G_VALUE_INIT;
    g_value_init(&fraction, GST_TYPE_FRACTION);
    gst_value_set_fraction(&fraction, 4, 3);
    g_object_set_property(G_OBJECT(aspectratiocrop), "aspect-ratio", &fraction);

    capsfilter2 = gst_element_factory_make ("capsfilter", "caps-filter2");
    caps2 = gst_caps_from_string ("video/x-raw(memory:NVMM), format=(string)NV12");
    g_object_set (G_OBJECT (capsfilter2), "caps", caps2, NULL);
    gst_caps_unref (caps2);

    // Create the second capsfilter to specify the desired resolution
    capsfilter3 = gst_element_factory_make("capsfilter", "capsfilter1bis");
    caps3 = gst_caps_from_string("video/x-raw, format=(string)RGBA");
    g_object_set(G_OBJECT(capsfilter3), "caps", caps3, NULL);
    gst_caps_unref(caps3);

    nvvidconvsrc1 = gst_element_factory_make("nvvideoconvert", "convertor_src1");

    streammux = gst_element_factory_make ("nvstreammux", "stream-muxer");
    g_object_set (G_OBJECT (streammux), "batch-size", 1, NULL);
    g_object_set (G_OBJECT (streammux), "width", 960, "height", 720, "batched-push-timeout", 1000, NULL);
    g_object_set(G_OBJECT(streammux), "num-surfaces-per-frame", 1, NULL);
    g_object_set(G_OBJECT(streammux), "live-source", TRUE, NULL);

    // Primary GIE (Detector)
    pgie = gst_element_factory_make("nvinfer", "primary-nvinference-engine");
    g_object_set(G_OBJECT(pgie), "config-file-path", "/home/rapit/Desktop/Jetson-Xavier/DeepStream-Yolo/config_infer_primary_yoloV8.txt",NULL);// /opt/nvidia/deepstream/deepstream-6.4/sources/apps/sample_apps/deepstream-test2/dstest2_pgie_config.txt", NULL);

    // Tracker
    tracker = gst_element_factory_make("nvtracker", "tracker");
    g_object_set(G_OBJECT(tracker), "ll-lib-file", "/opt/nvidia/deepstream/deepstream/lib/libnvds_nvmultiobjecttracker.so", NULL);
    g_object_set(G_OBJECT(tracker), "ll-config-file", "/opt/nvidia/deepstream/deepstream-6.4/sources/apps/sample_apps/deepstream-test2/dstest2_tracker_config.txt", NULL);

    nvvidconvsrc2 = gst_element_factory_make("nvvideoconvert", "convertor_src2");

    nvosd = gst_element_factory_make("nvdsosd", "nvosd");

    g_object_set(G_OBJECT(nvosd),
                 "gpu-id", 0,                        // Use GPU 0
                 "process-mode", 1,                   // GPU mode
                 "display-clock", TRUE,               // Enable system clock
                 "display-text", TRUE,                // Enable text display
                 "clock-font", "Arial",               // Set clock font
                 "clock-font-size", 13,               // Set clock font size
                 "x-clock-offset", 30,               // X offset for clock
                 "y-clock-offset", 30,                // Y offset for clock
                 "clock-color", 0xff0000ff,           // Clock color (red with full alpha)
                 "display-bbox", TRUE,                // Enable bounding box display
                 "display-mask", TRUE,                // Enable mask display
                 NULL);
    nvvidconvsrc3 = gst_element_factory_make("nvvideoconvert", "convertor_src3");



    // For appsink, set caps to request GLMemory
    appsink = gst_element_factory_make("appsink", "appsink");
    /*GstCaps *caps = gst_caps_from_string("video/x-raw(memory:GLMemory), format=(string)RGBA");
    gst_app_sink_set_caps(GST_APP_SINK(appsink), caps);
    gst_caps_unref(caps);*/

    g_object_set(G_OBJECT(appsink), "emit-signals", TRUE, "sync", FALSE, NULL);
    g_signal_connect(appsink, "new-sample", G_CALLBACK(on_new_sample), this);

    // Create the empty pipeline
    pipeline = gst_pipeline_new("camera-pipeline");
    if (!pipeline) {
        qWarning("Pipeline could not be created. Exiting.");
        return;
    }

    g_object_set(G_OBJECT(sink), "sync", FALSE, NULL);

    // Add all elements to the pipeline
    gst_bin_add_many(GST_BIN(pipeline), source, capsfilter1, jpegparse, decoder, aspectratiocrop, nvvidconvsrc1, capsfilter2, streammux, pgie, tracker, nvvidconvsrc2, nvosd, nvvidconvsrc3, capsfilter3, appsink, NULL);

    // Add elements up to capsfilter2
    if (!gst_element_link_many(source, capsfilter1, jpegparse, decoder, aspectratiocrop, nvvidconvsrc1, capsfilter2, NULL)) {
        qWarning("Failed to link elements up to capsfilter2. Exiting.");
        gst_object_unref(pipeline);
        pipeline = nullptr;
        return;
    }

    // Manually link capsfilter2 to streammux's sink_0
    GstPad *sinkpad = gst_element_get_request_pad(streammux, "sink_0");
    if (!sinkpad) {
        qWarning("Failed to get sink pad from streammux. Exiting.");
        gst_object_unref(pipeline);
        pipeline = nullptr;
        return;
    }

    GstPad *srcpad = gst_element_get_static_pad(capsfilter2, "src");
    if (!srcpad) {
        qWarning("Failed to get src pad from capsfilter2. Exiting.");
        gst_element_release_request_pad(streammux, sinkpad);
        gst_object_unref(sinkpad);
        gst_object_unref(pipeline);
        pipeline = nullptr;
        return;
    }

    if (gst_pad_link(srcpad, sinkpad) != GST_PAD_LINK_OK) {
        qWarning("Failed to link capsfilter2 to streammux. Exiting.");
        gst_object_unref(srcpad);
        gst_object_unref(sinkpad);
        gst_object_unref(pipeline);
        pipeline = nullptr;
        return;
    }

    gst_object_unref(srcpad);
    gst_object_unref(sinkpad);

    // Link the rest of the pipeline from streammux onwards
    if (!gst_element_link_many(streammux, pgie, tracker, nvvidconvsrc2, nvosd, nvvidconvsrc3, capsfilter3, appsink, NULL)) {
        qWarning("Failed to link elements from streammux onwards. Exiting.");
        gst_object_unref(pipeline);
        pipeline = nullptr;
        return;
    }




    //gst_bin_add_many (GST_BIN (pipeline), source, capsfilter1, jpegparse, decoder, aspectratiocrop, nvvidconvsrc1,  capsfilter2, streammux,  pgie, tracker, nvvidconvsrc2, nvosd, nvvidconvsrc3, capsfilter3,  appsink, NULL);

    /*if(!gst_element_link_many  (source, capsfilter1, jpegparse, decoder, aspectratiocrop,  nvvidconvsrc1, capsfilter2, streammux, pgie, tracker, nvvidconvsrc2,  nvosd,  nvvidconvsrc3, capsfilter3, appsink, NULL)){
        qWarning("Elements could not be linked. Exiting.");
        return;
    }*/
    /* =========================================================================================
            visual representation of the pipeline with probes and sinks:
        [source] → [capsfilter1] → [decoder] → [aspectratiocrop] → [nvvidconvsrc1]
        → [capsfilter2] → [streammux] → [pgie] → [tracker] → [nvvidconvsrc2] → [nvosd] → [nvvidconvsrc3] → [capsfilter3] → [appsink]
                                              └── [pgie_src_probe]             └── [osd_sink_probe]

        Probes:
        pgie_src_probe: Attached to pgie's source pad.
        osd_sink_probe: Attached to nvosd's sink pad.
        Sink:
        appsink: Final sink where processed frames are retrieved by the application.
    ============================================================================================= */

    /*GstPad *pgie_src_pad = gst_element_get_static_pad(pgie, "src");
    if (!pgie_src_pad) {
        g_printerr("Unable to get pgie src pad\n");
    } else {
        gst_pad_add_probe(pgie_src_pad, GST_PAD_PROBE_TYPE_BUFFER,
                          pgie_src_pad_buffer_probe, this, NULL);
        gst_object_unref(pgie_src_pad);
    }*/

    /*GstPad *tracker_sink_pad = gst_element_get_static_pad(tracker, "sink");
    if (!tracker_sink_pad) {
        g_printerr("Unable to get tracker sink pad\n");
    } else {
        gst_pad_add_probe(tracker_sink_pad, GST_PAD_PROBE_TYPE_BUFFER,
                          nvtracker_sink_pad_buffer_probe, this, NULL);
        gst_object_unref(tracker_sink_pad);
    }

    // Attach the pad probe to the tracker sink pad
    GstPad *tracker_src_pad = gst_element_get_static_pad(tracker, "src");
    if (!tracker_src_pad) {
        g_printerr("Unable to get tracker sink pad\n");
    } else {
        gst_pad_add_probe(tracker_src_pad, GST_PAD_PROBE_TYPE_BUFFER,
                          nvtracker_src_pad_buffer_probe, this, NULL);
        gst_object_unref(tracker_src_pad);
    }*/


    osd_sink_pad = gst_element_get_static_pad(nvosd, "sink");
    if (!osd_sink_pad) {
        g_print("Unable to get sink pad\n");
    } else {
        osd_probe_id = gst_pad_add_probe(osd_sink_pad, GST_PAD_PROBE_TYPE_BUFFER,
                                         osd_sink_pad_buffer_probe, this, NULL);
    }
     osd_sink_pad = gst_element_get_static_pad (nvosd, "sink");

    gst_object_unref (osd_sink_pad);
     // Add bus watcher
    // Add bus watcher
    bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
    bus_watch_id = gst_bus_add_watch(bus, bus_call, this);
    gst_object_unref(bus);

    qInfo("Elements are linked...");

    // Set pipeline to PLAYING and check for success
    GstStateChangeReturn ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        qWarning("Failed to set pipeline to PLAYING state.");
        gst_object_unref(pipeline);
        pipeline = nullptr;
        return;
    }

    // Debugging
    gst_debug_set_active(true);
    gst_debug_set_default_threshold(GST_LEVEL_WARNING);


}

GstFlowReturn CameraPipelineDay::on_new_sample(GstAppSink *sink, gpointer data)
{
    CameraPipelineDay *self = static_cast<CameraPipelineDay *>(data);
    GstSample *sample = gst_app_sink_pull_sample(sink);
    if (!sample) {
       qDebug() << "Failed to pull sample from appsink";
        return GST_FLOW_ERROR;
    }

    GstCaps *caps = gst_sample_get_caps(sample);
    if (!caps) {
       qDebug() << "Failed to get caps from sample";
        gst_sample_unref(sample);
        return GST_FLOW_ERROR;
    }

    GstStructure *structure = gst_caps_get_structure(caps, 0);
    int width, height;
    if (!gst_structure_get_int(structure, "width", &width) ||
        !gst_structure_get_int(structure, "height", &height)) {
       qDebug() << "Failed to get width and height from caps";
        gst_sample_unref(sample);
        return GST_FLOW_ERROR;
    }

    GstBuffer *buffer = gst_sample_get_buffer(sample);
    if (!buffer) {
       qDebug() << "Failed to get buffer from sample";
        gst_sample_unref(sample);
        return GST_FLOW_ERROR;
    }

    GstMapInfo map;
    if (!gst_buffer_map(buffer, &map, GST_MAP_READ)) {
       qDebug() << "Failed to map buffer";
        gst_sample_unref(sample);
        return GST_FLOW_ERROR;
    }

    // Assuming RGB format
    const guint8 *dataRGBA = map.data;
    if (!dataRGBA) {
       qDebug() << "Failed to access RGB data";
        gst_buffer_unmap(buffer, &map);
        gst_sample_unref(sample);
        return GST_FLOW_ERROR;
    }

    // Push frame to OpenGL widget
    emit self->newFrameAvailable(reinterpret_cast<uchar4 *>(const_cast<guint8 *>(dataRGBA)), width, height);

    // Update Tracker
    QRect updatedBoundingBox;
    if (self->setTrackState)
    {
        if (!self->trackerInitialized)
        {
            // Initialize Tracker
            int square_width = 100;
            QRect initialBoundingBox((width - square_width) / 2, (height - square_width) / 2, square_width, square_width);
            //self->_tracker->initialize(reinterpret_cast<uchar4 *>(const_cast<guint8 *>(dataRGBA)), width, height, initialBoundingBox);

            self->trackerInitialized = true;
        }
        else
        {
            auto start = std::chrono::high_resolution_clock::now();

            //bool trackingSuccess =
                //self->_tracker->processFrame(reinterpret_cast<uchar4 *>(const_cast<guint8 *>(dataRGBA)), width, height, updatedBoundingBox);

            auto end = std::chrono::high_resolution_clock::now();

             // Calculate the elapsed time in microseconds
             auto elapsedTimeUs = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
             if (elapsedTimeUs > 2000)
                std::cout << "Processing time: " << elapsedTimeUs << " microseconds (" <<   std::endl;

            //if (trackingSuccess)
            //{
                self->updatedBBox.setHeight(updatedBoundingBox.height());
                self->updatedBBox.setWidth(updatedBoundingBox.width());
                self->updatedBBox.setLeft(updatedBoundingBox.left());
                self->updatedBBox.setTop(updatedBoundingBox.top());
            /*}
            else
            {
                // Tracking failed
                //self->trackerInitialized = false;
                // Handle tracking failure, e.g., re-initialize or notify the user
            }*/
        }
    }

    gst_buffer_unmap(buffer, &map);
    gst_sample_unref(sample);

    return GST_FLOW_OK;
}



GstPadProbeReturn CameraPipelineDay::osd_sink_pad_buffer_probe(GstPad *pad, GstPadProbeInfo *info, gpointer user_data)
{
    CameraPipelineDay *self = static_cast<CameraPipelineDay *>(user_data);




    // Increment framesSinceLastSeen for all active tracks
    for (auto &entry : self->activeTracks)
    {
        entry.second.framesSinceLastSeen++;
    }

    // Retrieve batch metadata
    NvDsBatchMeta *batch_meta = gst_buffer_get_nvds_batch_meta(GST_BUFFER(info->data));
    if (!batch_meta)
        return GST_PAD_PROBE_OK;

    /// Loop through each frame in the batch
    for (NvDsMetaList *l_frame = batch_meta->frame_meta_list; l_frame != NULL; l_frame = l_frame->next)
    {
        NvDsFrameMeta *frame_meta = (NvDsFrameMeta *)(l_frame->data);

        // **General Overlay Start**

        // Acquire display meta for general overlay
        NvDsDisplayMeta *display_meta = nvds_acquire_display_meta_from_pool(batch_meta);
        display_meta->num_labels = 0;
        display_meta->num_lines = 0;

        // Prepare text labels
        int label_index = 0;

        // Safely access data from DataModel

        OperationalMode currentStateMode = self->m_dataModel->getOperationalStateMode();
        const char* strStateMode;
        switch (currentStateMode) {
        case OperationalMode::Idle:
            strStateMode = "Idle";
            break;
        case OperationalMode::Surveillance:
            strStateMode = "Surveillance";
            break;
        case OperationalMode::Tracking:
            strStateMode = "Tracking";
            break;
        case OperationalMode::Engagement:
            strStateMode = "Engagement";
            break;
        default:
            strStateMode = "Unknown Mode";
            break;
        }

        QString currentMotionMode = self->m_dataModel->getMotionMode();
        double lrfDistance = self->m_dataModel->getLRFDistance();
        double azimuth, elevation;
        self->m_dataModel->getGimbalOrientation(azimuth, elevation);
        double gimbalSpeed = self->m_dataModel->getSpeedSw();
        FireMode fireMode = self->m_dataModel->getFireMode();
        // Function to convert FireMode enum to string
        const char* strMode;
        switch (fireMode) {
        case FireMode::SingleShot:
            strMode = "Single Shot";
            break;
        case FireMode::ShortBurst:
            strMode = "Short Burst";
            break;
        case FireMode::LongBurst:
            strMode = "Long Burst";
            break;
        default:
            strMode = "Unknown Mode";
            break;
        }

        bool detectionEnabled = self->m_dataModel->isDetectionEnabled();
        bool stabilizationEnabled = self->m_dataModel->getStabilizationSw();
        bool activeCamera = self->m_dataModel->getCamera();

        bool gunArmedState = self->m_dataModel->isGunEnabled();          // ARMED or not
        bool ammunitionLoadState = self->m_dataModel->isLoadAmmunition(); // CHARGED or not
        bool stationMotionState = self->m_dataModel->getStationState();   // Station motion state
        bool AuthorizeState = self->m_dataModel->getAuthorizeSw();        // Authorization switch state
        // READY state is true if all the above are true
        bool readyState = gunArmedState && ammunitionLoadState && stationMotionState && AuthorizeState;

        NvOSD_ColorParams fontColor = {1.0, 0.0, 0.0, 1.0}; // White
        NvOSD_ColorParams textBackgroundColor = {0.0, 0.0, 0.0, 0.5}; // Semi-transparent black



        // **State Mode Label**
        display_meta->num_labels++;
        NvOSD_TextParams *txt_params_state = &display_meta->text_params[label_index++];
        txt_params_state->display_text = g_strdup_printf("State Mode: %s", strStateMode);
        txt_params_state->x_offset = 10;
        txt_params_state->y_offset = 30;
        txt_params_state->font_params.font_color = fontColor; // White
        txt_params_state->font_params.font_size = 16;
        txt_params_state->font_params.font_name = "Serif";
        txt_params_state->set_bg_clr = 1;
        txt_params_state->text_bg_clr = textBackgroundColor; // Semi-transparent black

        // **Motion Mode Label**
        display_meta->num_labels++;
        NvOSD_TextParams *txt_params_motion = &display_meta->text_params[label_index++];
        txt_params_motion->display_text = g_strdup_printf("Motion Mode: %s", currentMotionMode.toUtf8().constData());
        txt_params_motion->x_offset = 10;
        txt_params_motion->y_offset = 60;
        txt_params_motion->font_params = txt_params_state->font_params;
        txt_params_motion->set_bg_clr = txt_params_state->set_bg_clr;
        txt_params_motion->text_bg_clr = txt_params_state->text_bg_clr;

        // **LRF Distance Label**
        display_meta->num_labels++;
        NvOSD_TextParams *txt_params_lrf = &display_meta->text_params[label_index++];
        txt_params_lrf->display_text = g_strdup_printf("LRF Distance: %.2f m", lrfDistance);
        txt_params_lrf->x_offset = 10;
        txt_params_lrf->y_offset = 90;
        txt_params_lrf->font_params = txt_params_state->font_params;
        txt_params_lrf->set_bg_clr = txt_params_state->set_bg_clr;
        txt_params_lrf->text_bg_clr = txt_params_state->text_bg_clr;

        // **Detection Status Label**
        display_meta->num_labels++;
        NvOSD_TextParams *txt_params_detection = &display_meta->text_params[label_index++];
        txt_params_detection->display_text = g_strdup_printf("Detection: %s", detectionEnabled ? "On" : "Off");
        txt_params_detection->x_offset = 10;
        txt_params_detection->y_offset = 150; // Adjust as needed
        txt_params_detection->font_params = txt_params_state->font_params;
        txt_params_detection->set_bg_clr = txt_params_state->set_bg_clr;
        txt_params_detection->text_bg_clr = txt_params_state->text_bg_clr;

        // **Stabilization Status Label**
        display_meta->num_labels++;
        NvOSD_TextParams *txt_params_stab = &display_meta->text_params[label_index++];
        txt_params_stab->display_text = g_strdup_printf("Stabilization: %s", stabilizationEnabled ? "On" : "Off");
        txt_params_stab->x_offset = 10;
        txt_params_stab->y_offset = 180; // Adjust as needed
        txt_params_stab->font_params = txt_params_state->font_params;
        txt_params_stab->set_bg_clr = txt_params_state->set_bg_clr;
        txt_params_stab->text_bg_clr = txt_params_state->text_bg_clr;

        // **Display Gimbal Speed on OSD**
        display_meta->num_labels++;
        NvOSD_TextParams *txt_params_speed = &display_meta->text_params[label_index++];
        txt_params_speed->display_text = g_strdup_printf("Gimbal Speed: %.0f%%", gimbalSpeed);

        // Set text parameters (position, font, color)
        txt_params_speed->x_offset = 10; // Adjust x position as needed
        txt_params_speed->y_offset = 210; // Adjust y position as needed
        txt_params_speed->font_params.font_name = "Serif";
        txt_params_speed->font_params.font_size = 16;
        txt_params_speed->font_params.font_color = fontColor; // White color
        txt_params_speed->set_bg_clr = 1;
        txt_params_speed->text_bg_clr = textBackgroundColor; // Semi-transparent black background

        // **Display Fire Mode  on OSD**
        display_meta->num_labels++;
        NvOSD_TextParams *txt_params_mode = &display_meta->text_params[label_index++];



        txt_params_mode->display_text = g_strdup_printf("Fire Mode: %s", strMode);

        // Set text parameters (position, font, color)
        txt_params_mode->x_offset = 10; // Adjust x position as needed
        txt_params_mode->y_offset = 240; // Adjust y position as needed
        txt_params_mode->font_params.font_name = "Serif";
        txt_params_mode->font_params.font_size = 16;
        txt_params_mode->font_params.font_color = fontColor; // White color
        txt_params_mode->set_bg_clr = 1;
        txt_params_mode->text_bg_clr = textBackgroundColor; // Semi-transparent black background

        // ** Active Camera Label**
        display_meta->num_labels++;
        NvOSD_TextParams *txt_params_camera = &display_meta->text_params[label_index++];
        txt_params_camera->display_text = g_strdup_printf("Camera: %s", activeCamera ? "DAY" : "THERMAL");
        txt_params_camera->x_offset = 10;
        txt_params_camera->y_offset = 270; // Adjust as needed
        txt_params_camera->font_params = txt_params_state->font_params;
        txt_params_camera->set_bg_clr = txt_params_state->set_bg_clr;
        txt_params_camera->text_bg_clr = txt_params_state->text_bg_clr;



        // **CHARGED Status Label**
        display_meta->num_labels++;
        NvOSD_TextParams *txt_params_charged = &display_meta->text_params[label_index++];
        txt_params_charged->display_text = g_strdup_printf("CHARGED: %s", ammunitionLoadState ? "CHARGED" : "-");
        txt_params_charged->x_offset = 10;
        txt_params_charged->y_offset = 320; // Adjust as needed
        txt_params_charged->font_params = txt_params_state->font_params;
        txt_params_charged->set_bg_clr = txt_params_state->set_bg_clr;
        txt_params_charged->text_bg_clr = txt_params_state->text_bg_clr;

        // **ARMED Status Label**
        display_meta->num_labels++;
        NvOSD_TextParams *txt_params_armed = &display_meta->text_params[label_index++];
        txt_params_armed->display_text = g_strdup_printf("ARMED: %s", gunArmedState ? "ARMED" : "-");
        txt_params_armed->x_offset = 10;
        txt_params_armed->y_offset = 350; // Adjust as needed
        txt_params_armed->font_params = txt_params_state->font_params;
        txt_params_armed->set_bg_clr = txt_params_state->set_bg_clr;
        txt_params_armed->text_bg_clr = txt_params_state->text_bg_clr;

        // **READY Status Label**
        display_meta->num_labels++;
        NvOSD_TextParams *txt_params_ready = &display_meta->text_params[label_index++];
        txt_params_ready->display_text = g_strdup_printf("READY: %s", readyState ? "READY" : "-");
        txt_params_ready->x_offset = 10;
        txt_params_ready->y_offset = 380; // Adjust as needed
        txt_params_ready->font_params = txt_params_state->font_params;
        txt_params_ready->set_bg_clr = txt_params_state->set_bg_clr;
        txt_params_ready->text_bg_clr = txt_params_state->text_bg_clr;


        // **Draw Crosshair**
        int frame_width = frame_meta->source_frame_width;
        int frame_height = frame_meta->source_frame_height;
        int line_index = 0;

        // Horizontal line
        display_meta->num_lines++;
        NvOSD_LineParams *line_params_h = &display_meta->line_params[line_index++];
        line_params_h->x1 = frame_width / 2 - 20;
        line_params_h->y1 = frame_height / 2;
        line_params_h->x2 = frame_width / 2 + 20;
        line_params_h->y2 = frame_height / 2;
        line_params_h->line_width = 2;
        line_params_h->line_color = fontColor; // White

        // Vertical line
        display_meta->num_lines++;
        NvOSD_LineParams *line_params_v = &display_meta->line_params[line_index++];
        line_params_v->x1 = frame_width / 2;
        line_params_v->y1 = frame_height / 2 - 20;
        line_params_v->x2 = frame_width / 2;
        line_params_v->y2 = frame_height / 2 + 20;
        line_params_v->line_width = 2;
        line_params_v->line_color = fontColor; // White

        // **Add the Display Meta to the Frame**
        nvds_add_display_meta_to_frame(frame_meta, display_meta);

        // **General Overlay End**

        // Apply mode-specific display logic
        switch (self->currentMode)
        {
        case MODE_IDLE:
        {
            // Remove all object metadata
            clear_obj_meta_list(frame_meta);
            break;
        }
        case MODE_DETECTION:
        {
            // Classes to display: person(0), bicycle(1), car(2), motorcycle(3), bus(5), truck(7), boat(8)
            QSet<int> allowed_classes = {0, 1, 2, 3, 5, 7, 8};

            std::vector<NvDsObjectMeta *> objs_to_remove;

            for (NvDsMetaList *l_obj = frame_meta->obj_meta_list; l_obj != NULL; l_obj = l_obj->next)
            {
                NvDsObjectMeta *obj_meta = (NvDsObjectMeta *)(l_obj->data);

                // Check if the object's class is in the allowed list
                //if (allowed_classes.find(obj_meta->class_id) != allowed_classes.end())
                //{
                    // Set display text to class name
                    if (obj_meta->text_params.display_text)
                    {
                        g_free(obj_meta->text_params.display_text);
                    }
                    obj_meta->text_params.display_text = g_strdup(obj_meta->obj_label);
                //}
                //else
                //{
                    // Mark object meta for removal
                   // objs_to_remove.push_back(obj_meta);
                //}
            }

            // Remove unwanted object metadata
            for (NvDsObjectMeta *obj_meta : objs_to_remove)
            {
                nvds_remove_obj_meta_from_frame(frame_meta, obj_meta);
            }
            break;
        }
        case MODE_TRACKING:
        {
            QSet<int> allowed_classes = {0, 1, 2, 3, 5, 7, 8};
            QSet<int> currentFrameTrackIds;
            QSet<int> trackIds;
            std::vector<NvDsObjectMeta *> objs_to_remove;
            int selectedTrackId = self->getSelectedTrackId();

            for (NvDsMetaList *l_obj = frame_meta->obj_meta_list; l_obj != NULL; l_obj = l_obj->next)
            {
                NvDsObjectMeta *obj_meta = (NvDsObjectMeta *)(l_obj->data);

                // Check if the object's class is in the allowed list
                //if (allowed_classes.find(obj_meta->class_id) != allowed_classes.end())
                //{
                    // Collect track IDs
                    int trackId = obj_meta->object_id;
                    currentFrameTrackIds.insert(trackId);

                    // Update or add track info
                    self->activeTracks[trackId] = {trackId, 0};

                    // Set display text to include class name and track ID
                    if (obj_meta->text_params.display_text)
                    {
                        g_free(obj_meta->text_params.display_text);
                    }
                    obj_meta->text_params.display_text = g_strdup_printf("%s ID:%lu", obj_meta->obj_label, obj_meta->object_id);

                    // Highlight selected object
                    if (self->selectedTrackId == obj_meta->object_id)
                    {
                        // Change bounding box color and border width
                        obj_meta->rect_params.border_color = (NvOSD_ColorParams){0.0, 1.0, 0.0, 1.0}; // Red
                        obj_meta->rect_params.border_width = 2;

                        // Draw line from center to object's center
                        NvDsDisplayMeta *display_meta = nvds_acquire_display_meta_from_pool(batch_meta);
                        display_meta->num_lines = 1;
                        display_meta->line_params[0].x1 = frame_meta->source_frame_width / 2;
                        display_meta->line_params[0].y1 = frame_meta->source_frame_height / 2;
                        display_meta->line_params[0].x2 = obj_meta->rect_params.left + obj_meta->rect_params.width / 2;
                        display_meta->line_params[0].y2 = obj_meta->rect_params.top + obj_meta->rect_params.height / 2;
                        display_meta->line_params[0].line_width = 1;
                        display_meta->line_params[0].line_color = (NvOSD_ColorParams){0.0, 1.0, 0.0, 1.0}; // Green
                        nvds_add_display_meta_to_frame(frame_meta, display_meta);

                        // **Calculate Target Angles Adjusted for Cropping**

                        // Image dimensions after cropping
                        double croppedImageWidth = frame_meta->source_frame_width; // Should be 960
                        double croppedImageHeight = frame_meta->source_frame_height; // Should be 720

                        // Image center
                        double imageCenterX = croppedImageWidth / 2.0;
                        double imageCenterY = croppedImageHeight / 2.0;

                        // Target center coordinates
                        double targetX = obj_meta->rect_params.left + obj_meta->rect_params.width / 2.0;
                        double targetY = obj_meta->rect_params.top + obj_meta->rect_params.height / 2.0;

                        // Offsets from center
                        double deltaX = targetX - imageCenterX;
                        double deltaY = imageCenterY - targetY;

                        // Effective FOV calculations
                        double cameraHorizontalFOV = 90.0; // Replace with your camera's actual HFOV
                        double originalImageWidth = 1280.0;
                        double originalImageHeight = originalImageWidth * 9/16;
                        double effectiveHorizontalFOV = cameraHorizontalFOV * (croppedImageWidth / originalImageWidth);
                        double anglePerPixelX = effectiveHorizontalFOV / croppedImageWidth;

                        double cameraVerticalFOV = cameraHorizontalFOV * (originalImageHeight / originalImageWidth);
                        double anglePerPixelY = cameraVerticalFOV / croppedImageHeight;

                        // Calculate target angles
                        double targetAzimuthOffset = deltaX * anglePerPixelX;
                        double targetElevationOffset = deltaY * anglePerPixelY;

                        double currentAzimuth = 0; //self->m_dataModel->get;
                        double currentElevation = 0; //self->m_dataModel->getElevationPosition();

                        double targetAzimuth = currentAzimuth + targetAzimuthOffset;
                        double targetElevation = currentElevation + targetElevationOffset;

                        // Emit signal to update target position
                        qDebug() << "Emitting targetPositionUpdated from CameraSystem instance:" << self;

                        emit self->targetPositionUpdated(targetAzimuth, targetElevation);

                    }
                    std::vector<int> tracksToRemove;
                    for (const auto &entry : self->activeTracks)
                    {
                        if (entry.second.framesSinceLastSeen > self->maxFramesToKeep)
                        {
                            tracksToRemove.push_back(entry.first);
                        }
                    }
                    for (int trackId : tracksToRemove)
                    {
                        if (trackId == self->selectedTrackId)
                        {
                            // Reset the selectedTrackId
                            self->selectedTrackId = -1;
                            // Emit signal to notify GUI
                            emit self->selectedTrackLost(trackId);
                        }
                        self->activeTracks.erase(trackId);                        }

                    // Prepare the list of trackIds to emit
                    QSet<int> trackIds;
                    for (const auto &entry : self->activeTracks)
                    {
                        trackIds.insert(entry.first);
                    }

                    // Compare with previousTrackIds and emit if changed
                    if (trackIds  != self->previousTrackIds)
                    {
                        self->previousTrackIds = trackIds;
                        emit self->trackedTargetsUpdated(trackIds);
                    }
                //}
                //else
                //{
                    // Mark object meta for removal
                //    objs_to_remove.push_back(obj_meta);
                //}
            }



            break;
        }
        case MODE_MANUAL_TRACKING:
        {
            // Remove all detection/tracking metadata
           //clear_obj_meta_list(frame_meta);

            // Add manual tracking bounding box if enabled
            //if (self->manualTrackingEnabled)
            //{
            NvDsDisplayMeta *display_meta = nvds_acquire_display_meta_from_pool(batch_meta);
            NvDsObjectMeta *obj_meta = nvds_acquire_obj_meta_from_pool(batch_meta);

            obj_meta->unique_component_id = 1; // Define your component ID
            obj_meta->confidence = 1.0;

            // Initialize text parameters for displaying speed
            display_meta->num_labels = 1;
            NvOSD_TextParams *txt_params4 = &display_meta->text_params[3];
            txt_params4->display_text = static_cast<char*>(g_malloc0(10));
            snprintf(txt_params4->display_text, 10, "SPEED:%d", static_cast<int>(23.6));
            txt_params4->x_offset = 100;
            txt_params4->y_offset = 210;

            // Initialize rectangle parameters
            /*display_meta->num_rects = 1;
            NvOSD_RectParams *bboxRect = &display_meta->rect_params[0];
            if (self->updatedBBox.height() != 0)
            {
                bboxRect->height = self->updatedBBox.height();
                bboxRect->width = self->updatedBBox.width();
                bboxRect->left = self->updatedBBox.x();
                bboxRect->top = self->updatedBBox.y();
                bboxRect->border_width = 2;
                bboxRect->border_color = (NvOSD_ColorParams){1.0, 0.0, 0.0, 1.0};
            }*/

            // Optionally set display text
            if (obj_meta->text_params.display_text)
            {
                g_free(obj_meta->text_params.display_text);
            }
            obj_meta->text_params.display_text = g_strdup("Manual Target");

            // **Add Bracket and Arrow Lines**
            // Define the number of additional lines needed
            // For two brackets: 4 lines (2 on each side)
            // For one arrow: 2 lines (shaft and head)
            int additionalLines = 6; // Adjust as needed
            display_meta->num_lines += additionalLines;

            // Define bracket parameters
            // Left Bracket
            NvOSD_LineParams *leftBracketTop = &display_meta->line_params[display_meta->num_lines - additionalLines];
            NvOSD_LineParams *leftBracketBottom = &display_meta->line_params[display_meta->num_lines - additionalLines + 1];

            // Right Bracket
            NvOSD_LineParams *rightBracketTop = &display_meta->line_params[display_meta->num_lines - additionalLines + 2];
            NvOSD_LineParams *rightBracketBottom = &display_meta->line_params[display_meta->num_lines - additionalLines + 3];

            // Define arrow parameters
            NvOSD_LineParams *arrowShaft = &display_meta->line_params[display_meta->num_lines - additionalLines + 4];
            NvOSD_LineParams *arrowHead1 = &display_meta->line_params[display_meta->num_lines - additionalLines + 5];
            NvOSD_LineParams *arrowHead2 = &display_meta->line_params[display_meta->num_lines - additionalLines + 6];

            // Calculate bounding box coordinates
            float left = static_cast<float>(self->updatedBBox.x());
            float top = static_cast<float>(self->updatedBBox.y());
            float right = left + static_cast<float>(self->updatedBBox.width());
            float bottom = top + static_cast<float>(self->updatedBBox.height());
            float centerX = left + (self->updatedBBox.width() / 2.0f);
            float centerY = top + (self->updatedBBox.height() / 2.0f);

            // **Configure Left Bracket Lines**
            leftBracketTop->x1 = left;
            leftBracketTop->y1 = top;
            leftBracketTop->x2 = left + 20; // Horizontal line length
            leftBracketTop->y2 = top;
            leftBracketTop->line_width = 2;
            leftBracketTop->line_color = (NvOSD_ColorParams){0.0, 1.0, 0.0, 1.0}; // Green

            leftBracketBottom->x1 = left;
            leftBracketBottom->y1 = bottom;
            leftBracketBottom->x2 = left + 20;
            leftBracketBottom->y2 = bottom;
            leftBracketBottom->line_width = 2;
            leftBracketBottom->line_color = (NvOSD_ColorParams){0.0, 1.0, 0.0, 1.0}; // Green

            // **Configure Right Bracket Lines**
            rightBracketTop->x1 = right;
            rightBracketTop->y1 = top;
            rightBracketTop->x2 = right - 20; // Horizontal line length
            rightBracketTop->y2 = top;
            rightBracketTop->line_width = 2;
            rightBracketTop->line_color = (NvOSD_ColorParams){0.0, 1.0, 0.0, 1.0}; // Green

            rightBracketBottom->x1 = right;
            rightBracketBottom->y1 = bottom;
            rightBracketBottom->x2 = right - 20;
            rightBracketBottom->y2 = bottom;
            rightBracketBottom->line_width = 2;
            rightBracketBottom->line_color = (NvOSD_ColorParams){0.0, 1.0, 0.0, 1.0}; // Green

            // **Configure Arrow Lines**
            // Arrow Shaft


            // **Add Object Meta to Frame**
            nvds_add_obj_meta_to_frame(frame_meta, obj_meta, NULL);

            //}
            break;
        }
        default:
            break;
        } // End of switch-case
    } // End of frame loop


    return GST_PAD_PROBE_OK;
}

void CameraPipelineDay::setPGIEInterval(guint interval)
{    if (!pipeline)
        return;
    g_object_set(G_OBJECT(pgie), "interval", interval, NULL);
}

void CameraPipelineDay::clear_obj_meta_list(NvDsFrameMeta *frame_meta)
{
    NvDsObjectMeta *obj_meta = NULL;
    NvDsMetaList *meta_list = NULL;

    while (frame_meta->obj_meta_list != NULL)
    {
        meta_list = frame_meta->obj_meta_list;
        obj_meta = (NvDsObjectMeta *)(meta_list->data);

        // Remove object meta from frame
        nvds_remove_obj_meta_from_frame(frame_meta, obj_meta);
    }
}

void CameraPipelineDay::setSelectedTrackId(int trackId)
{
    QMutexLocker locker(&mutex);
    selectedTrackId = trackId;
}

// Access selectedTrackId in osd_sink_pad_buffer_probe
int CameraPipelineDay::getSelectedTrackId()
{
    {
        QMutexLocker locker(&mutex);
        if (activeTracks.find(selectedTrackId) != activeTracks.end())
        {
            return selectedTrackId;
        }
        else
        {
            // Optionally, reset selectedTrackId if the track is no longer active
            // selectedTrackId = -1;
            return -1;
        }
    }
}

gboolean CameraPipelineDay::bus_call(GstBus *bus, GstMessage *msg, gpointer data)
{
    CameraPipelineDay *self = static_cast<CameraPipelineDay *>(data);
    switch (GST_MESSAGE_TYPE(msg)) {
    case GST_MESSAGE_EOS:
        qDebug() << "EOS received in bus_call";
        // Proceed with cleanup
        self->stop();
        break;
    case GST_MESSAGE_ERROR:
        // Handle error
        break;
    default:
        break;
    }
    return TRUE;
}
