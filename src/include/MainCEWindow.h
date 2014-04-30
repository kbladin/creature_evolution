#ifndef MAINCEWINDOW_H
#define MAINCEWINDOW_H

#include <QtWidgets/QApplication>

#include <QtWidgets/QWidget>
#include <QFutureWatcher>
#include <CreatureEvolution.h>
#include <QtConcurrent/QtConcurrent>

#include <QtWidgets/QGroupBox>
#include <CreatureEvolution.h>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLabel>
#include <QtDebug>
#include <QtGui>
#include <QSignalMapper>

#include "SliderWidget.h"

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
    void loadCreature();
    void renderWorm();

    void evoDone();

    void setValueMut(int value);
    static void setValueGen(int value);
    void setValuePop(int value);
    void setValueCO(int value);
    void setValueElit(int value);


    void changePressed();
    void changeReleased();

    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
protected:
    void keyPressEvent(QKeyEvent *event);

private:
    //QVBoxLayout *createSliderLayout(QSlider *slider, int range, int step, int page, int tick, std::string label, void (*function)(int));
    QWidget *transWindow;

    QSlider *slide_gen;
    QSlider *slide_pop;
    QSlider *slide_CO;
    QSlider *slide_elit;
    QSlider *slide_mut;
    QSlider *slide_change_dim;

    QFutureWatcher<void> evolution_thread_starter_;

    QBoxLayout *box_gen;
    QBoxLayout *box_pop;
    QBoxLayout *box_CO;
    QBoxLayout *box_elit;
    QBoxLayout *box_mut;
    QBoxLayout *box_change_dim;

    GLWidget *glWidget;
    CreatureEvolution* creature_evo_;

    QPoint _mousePosition;

    static const int normalize = 100;
    static const int number_of_sliders = 6;
    bool _mousePressed;
};

class W: public QWidget
{
    Q_OBJECT
public:
    W(QWidget *parent = 0)
        : QWidget(parent, Qt::FramelessWindowHint), locked(false)
    {
        QPushButton *lock   = new QPushButton("Lock");
        QPushButton *unlock = new QPushButton("Unlock");
        QPushButton *quit   = new QPushButton("&Quit");

        connect(lock,   SIGNAL(clicked()), this, SLOT(set));
        connect(unlock, SIGNAL(clicked()), this, SLOT(unlock()));
        connect(quit, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));

        QHBoxLayout *l = new QHBoxLayout;
        l->addWidget(lock);
        l->addWidget(unlock);
        l->addWidget(quit);
        setLayout(l);
    }

public slots:
    void lock() {
      locked = true;
      move(x(), 0); // move window to the top of the screen
    }
    void unlock() { locked = false; }
void setBodyDimension(int value);

protected:
    void mousePressEvent(QMouseEvent *evt)
    {
        oldPos = evt->globalPos();
    }

    void mouseMoveEvent(QMouseEvent *evt)
    {
        const QPoint delta = evt->globalPos() - oldPos;
        if (locked)
            // if locked, ignore delta on y axis, stay at the top
            move(x()+delta.x(), y());
        else
            move(x()+delta.x(), y()+delta.y());
        oldPos = evt->globalPos();
    }

private:
    bool locked;
    QPoint oldPos;
};


#endif // MAINCEWINDOW_H
