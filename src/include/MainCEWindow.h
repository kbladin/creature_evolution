#ifndef MAINCEWINDOW_H
#define MAINCEWINDOW_H

#include <QtWidgets/QApplication>

#include <QtWidgets/QWidget>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>

#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QComboBox>


#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QStyle>
#include <QtWidgets/QMainWindow>
#include <QtDebug>

#include "SliderWidget.h"
#include "Creature.h"

QT_BEGIN_NAMESPACE
class QSlider;
QT_END_NAMESPACE

class GLWidget;
class EvolutionManager;

class MainCEWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainCEWindow();

signals:
    void valueChanged(int value);
    void RequestSimulationEnd();

public slots:
    void testPrint();
    void startEvolution();
    void loadCreature(int index);
    void renderWorm();

    void evoDone();

    void GotNewCreature(const Creature &new_creature);

    void setValueMut(int value);
    void setValueMutInternal(int value);
    void setValueMutSigma(int value);
    static void setValueGen(int value);
    void setValuePop(int value);
    void setValueCO(int value);
    void setValueElit(int value);
    void setBodyDimension(int value);
    void changePressed();
    void changeReleased();
    void GameOfWorms();
    void ChangeCreatureType(int type);

    void FSetDistTarget(int value);
    void FSetDistZ(int value);
    void FSetMaxY(int value);
    void FSetAccumY(int value);
    void FSetAccumHeadY(int value);
    void FSetDeviationX(int value);
    void FSetEnergy(int value);

protected:
    void keyPressEvent(QKeyEvent *event);
private:
    void CreateDockWindows();
    void CreateStatusBar();
    void CreateActions();
    void CreateMenus();
    void CreateToolBar();
    void DisableCriticalWidgets();

    QMenu* main_menu_;
    QToolBar* tool_bar_;
    QDockWidget* dock_simulation;
    QDockWidget* dock_fitness;
    QComboBox* creature_list;
    //ACTIONS
    QAction* exitAct;
    QAction* evoAct;
    QAction* showSimDock;
    QAction* showFitnessDock;

    QLineEdit* p_edit;
    QLineEdit* g_edit;

    int creature_count_;

    QSlider *slide_gen;
    QSlider *slide_pop;
    QSlider *slide_CO;
    QSlider *slide_elit;
    QSlider *slide_mut;
    QSlider *slide_change_dim;

    QFutureWatcher<void> evolution_thread_starter_;

    QHBoxLayout *layout_main;
    QVBoxLayout *layout_control;
    QVBoxLayout *layout_button;
    QVBoxLayout *layout_hide;


    QBoxLayout *box_gen;
    QBoxLayout *box_pop;
    QBoxLayout *box_CO;
    QBoxLayout *box_elit;
    QBoxLayout *box_mut;
    QBoxLayout *box_change_dim;

    SliderWidget* generation_slider;
    SliderWidget* generation_size_slider;
    SliderWidget* crossover_slider;
    SliderWidget* elitism_slider;
    SliderWidget* mutation_slider;
    SliderWidget* mutation_internal_slider;
    SliderWidget* mutation_sigma_slider;

    SliderWidget* f_dist_light_slider;
    SliderWidget* f_dist_z_slider;
    SliderWidget* f_max_y_slider;
    SliderWidget* f_accum_y_slider;
    SliderWidget* f_accum_head_slider;
    SliderWidget* f_dev_x_slider;
    SliderWidget* f_energy_slider;

    QPushButton *simButton;
    QPushButton *cancelButton;
    QPushButton *loadButton;
    QPushButton *gameofwormsbtn;
    QPushButton *dummyButton;

    GLWidget *glWidget;
    static const int normalize = 100;
    static const int number_of_sliders = 6;

    bool isVisible;
    bool first_run_;
    bool sim_in_progress_;
    std::vector<Creature> creatures_;

    EvolutionManager* EM_;
};

#endif // MAINCEWINDOW_H
