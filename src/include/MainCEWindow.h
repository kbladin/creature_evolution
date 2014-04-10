#ifndef MAINCEWINDOW_H
#define MAINCEWINDOW_H

#include <CreatureEvolution.h>

QT_BEGIN_NAMESPACE
class QSlider;
class QCheckBox;
class QComboBox;
class QGroupBox;
class QLabel;
class QSpinBox;
class QStackedWidget;
QT_END_NAMESPACE

class GLWidget;

class MainCEWindow : public QWidget
{
    Q_OBJECT

public:
    MainCEWindow(CreatureEvolution* ce);

public slots:
    void testPrint();
    void startEvolution();
    void renderWorm();
    void testChangeFun1();
    void testChangeFun2();
protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QSlider *createSlider();

    GLWidget *glWidget;
    CreatureEvolution* creature_evo_;
};

#endif // MAINCEWINDOW_H
