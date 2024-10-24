#include "include/gui/videoglwidget_gl.h"
#include <QOpenGLTexture>
#include <QDebug>

VideoGLWidget_gl::VideoGLWidget_gl(QWidget *parent)
    : QOpenGLWidget(parent), currentFrame(nullptr), frameWidth(0), frameHeight(0) {
    gst_init(nullptr, nullptr);
}

VideoGLWidget_gl::~VideoGLWidget_gl() {
    makeCurrent();
    glDeleteTextures(1, &textureID);
    doneCurrent();
}

void VideoGLWidget_gl::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.9f, 0.9f, 0.9f, 0.5f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void VideoGLWidget_gl::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    frameMutex.lock();
    if (currentFrame && frameWidth > 0 && frameHeight > 0) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, frameWidth, frameHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, currentFrame);

        glBegin(GL_QUADS);
            glTexCoord2f(0, 1); glVertex2f(-1, -1);
            glTexCoord2f(1, 1); glVertex2f(1, -1);
            glTexCoord2f(1, 0); glVertex2f(1, 1);
            glTexCoord2f(0, 0); glVertex2f(-1, 1);
        glEnd();

        glDisable(GL_TEXTURE_2D);
    }
    frameMutex.unlock();
}

void VideoGLWidget_gl::pushFrame(uchar4 *frame, int width, int height) {
    frameMutex.lock();
    currentFrame = frame;
    frameWidth = width;
    frameHeight = height;
    frameMutex.unlock();

    update();
}

void VideoGLWidget_gl::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}
