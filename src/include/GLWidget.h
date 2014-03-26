#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <GL/glew.h>
#include <QtOpenGL/QGLWidget>
#include "CreatureEvolution.h"
#include <QtGui/QMouseEvent>

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

private:
    QPoint lastPos;

    bool enable_render_;
    CreatureEvolution* ce_handle_;
};

#endif // GLWIDGET_H
