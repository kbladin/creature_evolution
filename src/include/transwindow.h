#ifndef TRANSWINDOW_H
#define TRANSWINDOW_H

#include "MainCEWindow.h"

class TransWindow : public QWidget
{
    Q_OBJECT
public:
    explicit TransWindow(QWidget *parent = 0);
signals:
    void valueChanged(int value);
public slots:
/*
    void setValueMut(int value);
    void setValueGen(int value);
    void setValuePop(int value);
    void setValueCO(int value);
    void setValueElit(int value);
    void setBodyDimension(int value);
*/
protected:

    void mousePressEvent(QMouseEvent *evt);
    void mouseMoveEvent(QMouseEvent *evt);

private:

    // ----Sliders----
    QSlider *slide_gen;
    QSlider *slide_pop;
    QSlider *slide_CO;
    QSlider *slide_elit;
    QSlider *slide_mut;
    QSlider *slide_change_dim;

    // ----Boxes----
    QBoxLayout *box_gen;
    QBoxLayout *box_pop;
    QBoxLayout *box_CO;
    QBoxLayout *box_elit;
    QBoxLayout *box_mut;
    QBoxLayout *box_change_dim;

    static const int normalize = 100;
    static const int number_of_sliders = 6;

    QPoint oldPosition;
    QPoint delta;

};

#endif // TRANSWINDOW_H
