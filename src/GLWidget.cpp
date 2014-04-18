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

GLWidget::~GLWidget(){
}

QSize GLWidget::minimumSizeHint() const{
  return QSize(50, 50);
}

QSize GLWidget::sizeHint() const{
  return QSize(400, 400);
}

void GLWidget::initializeGL(){
  glewExperimental = true; // Needed for core profile
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
  }
  glClearColor(0.8f, 0.8f, 1.0f, 1.0f);

  ShaderManager::Instance();

  TextureManager::Instance();
}

void GLWidget::paintGL(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if(enable_render_) {
    ce_handle_->StepTheWorld();
    ce_handle_->UpdateTheWorld();
    ce_handle_->RenderTheWorld();
  }
}

void GLWidget::resizeGL(int width, int height){
  SettingsManager::Instance()->SetFrameWidth(width);
  SettingsManager::Instance()->SetFrameHeight(height);
  int side = qMin(width, height);
  glViewport((width - side) / 2, (height - side) / 2, side, side);
}

void GLWidget::mousePressEvent(QMouseEvent *event){
  lastPos = event->pos();
  qDebug() << lastPos;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event){
  // dx and dy returns difference in pixels. This will be double for retina
  // screens. Frame width and height however returns the retina pixels.
  // Therefore the sensitivity is dependent on the screen. Maybe not that good
  // but strange that it is different.
  int dx = event->x() - lastPos.x();
  int dy = event->y() - lastPos.y();

  if (event->buttons() & Qt::LeftButton) {
    Camera* current_cam = SceneManager::Instance()->GetCamera();
    if (current_cam){
      float width = SettingsManager::Instance()->GetFrameWidth();
      float height = SettingsManager::Instance()->GetFrameHeight();
      float sense = SettingsManager::Instance()->GetRotationSensitivity();
      // X-position handles the rotation around the y-axis and vice versa.
      // The rotation should not be dependent on the size of the window.
      current_cam->IncrementYrotation(sense * (dx / width));
      current_cam->IncrementXrotation(sense * (dy / height));
    }
  }
  else if (event->buttons() & Qt::RightButton) {

  }
  lastPos = event->pos();
}

void GLWidget::wheelEvent(QWheelEvent* event){
  Camera* current_cam = SceneManager::Instance()->GetCamera();
  if (current_cam){
    current_cam->IncrementZposition(event->delta() / 100.0f);
  }
};

void GLWidget::enableRendering() {
    qDebug("render enabled");

    //ce_handle_->InitWorld();

    std::cout << "GLWIDGET: Init'ed the world" << std::endl;
    enable_render_ = true;
}
