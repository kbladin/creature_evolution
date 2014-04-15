#ifndef MAINCEWINDOW_H
#define MAINCEWINDOW_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QGroupBox>
#include <CreatureEvolution.h>
#include "Body.h"

QT_BEGIN_NAMESPACE
class QSlider;
QT_END_NAMESPACE

class GLWidget;

class MainCEWindow : public QWidget
{
    Q_OBJECT

public:
    MainCEWindow(CreatureEvolution* ce);

signals:
    void valueChanged(int value);

public slots:
    void testPrint();
    void startEvolution();
    void renderWorm();

    void setValueMut(int value);
    void setValueGen(int value);
    void setValuePop(int value);
    void setValueCO(int value);
    void setValueElit(int value);
    void setBodyDimension(int value);

    void changePressed();
    void changeReleased();
protected:
    void keyPressEvent(QKeyEvent *event);
private:
    QSlider *createSlider(int range, int step, int page, int tick);
    QSlider *slide[4];
    QSlider *slide_gen;
    QSlider *slide_pop;
    QSlider *slide_CO;
    QSlider *slide_elit;
    QSlider *slide_mut;
    QSlider *slide_change_dim;

    GLWidget *glWidget;
    CreatureEvolution* creature_evo_;
    static const int normalize = 100;
};

#endif // MAINCEWINDOW_H
