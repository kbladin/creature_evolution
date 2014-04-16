#ifndef MAINCEWINDOW_H
#define MAINCEWINDOW_H

#include <QtWidgets/QWidget>
#include <QFutureWatcher>
#include <CreatureEvolution.h>
#include <QtConcurrent/QtConcurrent>


QT_BEGIN_NAMESPACE
class QSlider;
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
    void loadCreature();
    void renderWorm();
    void evoDone();
protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QSlider *createSlider();

    QFutureWatcher<void> evolution_thread_starter_;
    GLWidget *glWidget;
    CreatureEvolution* creature_evo_;
};

#endif // MAINCEWINDOW_H
