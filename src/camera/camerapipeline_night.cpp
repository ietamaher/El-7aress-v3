#include "include/camera/camerapipeline_night.h"
#include <QDebug>
#include <gst/gl/gl.h>
#include <chrono>
#include <iostream>

CameraPipelineNight::CameraPipelineNight(int cameraIndex, QObject *parent)
    : QObject(parent),
    pipeline(nullptr),
    appsink(nullptr),
    source(nullptr),
    bus(nullptr),
    busWatchId(0),
    cameraIndex(cameraIndex),
    currentMode(MODE_NONE1),
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
 }

CameraPipelineNight::~CameraPipelineNight()
{
    stop();
}

void CameraPipelineNight::start()
{

     buildPipeline();
}

void CameraPipelineNight::stop()
{
    gst_element_set_state(pipeline, GST_STATE_NULL);
    if (busWatchId)
    {
        gst_bus_remove_watch(bus);
        busWatchId = 0;
    }
    if (bus)
    {
        gst_object_unref(bus);
        bus = nullptr;
    }
    if (pipeline)
    {
        gst_object_unref(pipeline);
        pipeline = nullptr;
    }

}

void CameraPipelineNight::setTracker()
{

    trackerInitialized = false;
    setTrackState = true;
    // Adjust pipeline elements based on mode
}
void CameraPipelineNight::setProcessingMode(ProcessingMode mode)
{
    currentMode = mode;
    // Adjust pipeline elements based on mode
}

void CameraPipelineNight::selectTarget(int trackId)
{
    // Implement logic to focus on the selected target
}

void CameraPipelineNight::buildPipeline()
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
    g_object_set(G_OBJECT(pgie), "config-file-path", "/home/rapit/DeepStream-Yolo/config_infer_primary_yoloV8.txt",NULL);// /opt/nvidia/deepstream/deepstream-6.3/sources/apps/sample_apps/deepstream-test2/dstest2_pgie_config.txt", NULL);

    // Tracker
    tracker = gst_element_factory_make("nvtracker", "tracker");
    g_object_set(G_OBJECT(tracker), "ll-lib-file", "/opt/nvidia/deepstream/deepstream/lib/libnvds_nvmultiobjecttracker.so", NULL);
    g_object_set(G_OBJECT(tracker), "ll-config-file", "/opt/nvidia/deepstream/deepstream-6.3/sources/apps/sample_apps/deepstream-test2/dstest2_tracker_config.txt", NULL);

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



    GstPad *sinkpad = gst_element_get_request_pad(streammux, "sink_0");
    GstPad *srcpad = gst_element_get_static_pad(capsfilter2, "src");
    if (gst_pad_link(srcpad, sinkpad) != GST_PAD_LINK_OK) {
        g_printerr("Failed to link capsfilter2 to streammux. Exiting.\n");
        return ;
    }
    gst_object_unref(srcpad);
    gst_object_unref(sinkpad);

    g_object_set(G_OBJECT(sink), "sync", FALSE, NULL);

    gst_bin_add_many (GST_BIN (pipeline), source, capsfilter1, jpegparse, decoder, aspectratiocrop, nvvidconvsrc1,  capsfilter2, streammux,  pgie, tracker, nvvidconvsrc2, nvosd, nvvidconvsrc3, capsfilter3,  appsink, NULL);

    if(!gst_element_link_many  (source, capsfilter1, jpegparse, decoder, aspectratiocrop,  nvvidconvsrc1, capsfilter2, streammux, pgie, tracker, nvvidconvsrc2,  nvosd,  nvvidconvsrc3, capsfilter3, appsink, NULL)){
        qWarning("Elements could not be linked. Exiting.");
        return;
    }
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

    GstPad *osd_sink_pad = gst_element_get_static_pad (nvosd, "sink");
    if (!osd_sink_pad)
        g_print ("Unable to get sink pad\n");
    else
        gst_pad_add_probe (osd_sink_pad, GST_PAD_PROBE_TYPE_BUFFER,
                          osd_sink_pad_buffer_probe, this, NULL);
    gst_object_unref (osd_sink_pad);

    qInfo("Elements are linked...");
    // getting more information
    gst_debug_set_active(true);
    gst_debug_set_default_threshold(GST_LEVEL_WARNING);

    // Start playing
    gst_element_set_state(pipeline, GST_STATE_PLAYING);

    // Clean up
    // Add bus watcher
    bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
    //bus_watch_id = gst_bus_add_watch(bus, bus_call, this);
    gst_object_unref(bus);


}

GstFlowReturn CameraPipelineNight::on_new_sample(GstAppSink *sink, gpointer data)
{
    CameraPipelineNight *self = static_cast<CameraPipelineNight *>(data);
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



GstPadProbeReturn CameraPipelineNight::osd_sink_pad_buffer_probe(GstPad *pad, GstPadProbeInfo *info, gpointer user_data)
{

    CameraPipelineNight *self = static_cast<CameraPipelineNight *>(user_data);

    // Increment framesSinceLastSeen for all active tracks
    for (auto &entry : self->activeTracks)
    {
        entry.second.framesSinceLastSeen++;
    }

    // Retrieve batch metadata
        NvDsBatchMeta *batch_meta = gst_buffer_get_nvds_batch_meta(GST_BUFFER(info->data));
        if (!batch_meta)
            return GST_PAD_PROBE_OK;

        // Loop through each frame in the batch
        for (NvDsMetaList *l_frame = batch_meta->frame_meta_list; l_frame != NULL; l_frame = l_frame->next)
        {
            NvDsFrameMeta *frame_meta = (NvDsFrameMeta *)(l_frame->data);

            // Apply mode-specific display logic
            switch (self->currentMode)
            {
            case MODE_NONE1:
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

void CameraPipelineNight::setPGIEInterval(guint interval)
{
    g_object_set(G_OBJECT(pgie), "interval", interval, NULL);
}

void CameraPipelineNight::clear_obj_meta_list(NvDsFrameMeta *frame_meta)
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

void CameraPipelineNight::setSelectedTrackId(int trackId)
{
    QMutexLocker locker(&mutex);
    selectedTrackId = trackId;
}

// Access selectedTrackId in osd_sink_pad_buffer_probe
int CameraPipelineNight::getSelectedTrackId()
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
