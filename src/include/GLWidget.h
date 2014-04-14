#ifndef GLWIDGET_H
#define GLWIDGET_H

// External
#include <GL/glew.h>
#include <QtOpenGL/QGLWidget>
#include <QtGui/QMouseEvent>
#include <QtGui/QWheelEvent>
#include <QDebug>
#include <QtCore/QTimer>
#include <QtWidgets/qwidget.h>
// Internal
#include "CreatureEvolution.h"



class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QGLFormat format, QWidget *parent = 0, CreatureEvolution* ce = NULL);
    ~GLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

public slots:
    void enableRendering();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent* event);

private:
    QPoint lastPos;

    bool enable_render_;
    CreatureEvolution* ce_handle_;
};

#endif // GLWIDGET_H
