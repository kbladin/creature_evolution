#include <GL/glew.h>
#include <QtWidgets/qwidget.h>
#include <QtCore/QTimer>
#include <QDebug>
//#include <QtOpenGL>

#include <math.h>
#include <iostream>

#include "GLWidget.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

GLWidget::GLWidget(QGLFormat format, QWidget *parent, CreatureEvolution* ce)
    : QGLWidget(format, parent)
{
    ce_handle_ = ce;
    enable_render_ = false;
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(16);
}

GLWidget::~GLWidget()
{
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(400, 400);
}

void GLWidget::initializeGL()
{
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
    }

}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(enable_render_) {
        ce_handle_->StepTheWorld();
        ce_handle_->UpdateTheWorld();
        ce_handle_->RenderTheWorld();
    }
}

void GLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
    qDebug() << lastPos;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {

    }
    else if (event->buttons() & Qt::RightButton) {

    }
    lastPos = event->pos();
}

void GLWidget::enableRendering() {
    enable_render_ = true;
    qDebug("render enabled");
    ce_handle_->InitWorld();
    
}
