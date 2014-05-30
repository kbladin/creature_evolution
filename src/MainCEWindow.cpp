#include "GLWidget.h"
#include "MainCEWindow.h"
#include "EvolutionManager.h"
#include "Scene.h"

#include <QtWidgets/QDockWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QMessageBox>


MainCEWindow::MainCEWindow()
{
    isVisible = true;
    creature_count_ = 0;
    first_run_ = true;
    sim_in_progress_ = false;


    EM_ = new EvolutionManager();
    QGLFormat glFormat;
    glFormat.setVersion( 3, 2 );
    glFormat.setProfile( QGLFormat::CoreProfile ); // Requires >=Qt-4.8.0
    glFormat.setSampleBuffers( true );
    glWidget = new GLWidget(glFormat,0);


    simButton = new QPushButton("Start simulation");
    creature_list = new QComboBox();
    creature_list->setEditable(true);
    creature_list->setInsertPolicy(QComboBox::NoInsert);
    connect(creature_list, SIGNAL(activated(int)), this, SLOT(loadCreature(int)));
    cancelButton = new QPushButton("Cancel");
    pauseButton = new QPushButton("Pause");

    pauseButton->setDisabled(true);
    cancelButton->setDisabled(true);
    
    int max_gen = SettingsManager::Instance()->GetMaxGenerations();
    int pop_size = SettingsManager::Instance()->GetPopulationSize();
    int elitism = 100 * SettingsManager::Instance()->GetElitism();
    int mutation = 100 * SettingsManager::Instance()->GetMutation();
    int mutation_internal = 100 * SettingsManager::Instance()->GetMutationInternal();
    int mutation_sigma = 100 * SettingsManager::Instance()->GetMutationSigma();

    generation_slider = new SliderWidget("Number of generations: ", max_gen, 0, 100, 1, 10, 10);
    generation_size_slider = new SliderWidget("Generation size: ", pop_size, 0, 100, 1, 10, 10);
    elitism_slider = new SliderWidget("Elitism ratio (%): ", elitism, 0, 100, 1, 10, 10);
    mutation_internal_slider = new SliderWidget("Mutation rate (%): ", mutation_internal, 0, 100, 1, 10, 10);
    mutation_sigma_slider = new SliderWidget("Mutation strength (%) : ", mutation_sigma, 0, 100, 1, 10, 10);


    int f_dist_light = 100*SettingsManager::Instance()->GetFitnessDistanceLight();
    int f_dist_z = 100*SettingsManager::Instance()->GetFitnessDistanceZ();
    int f_max_y = 100*SettingsManager::Instance()->GetFitnessMaxY();
    int f_accum_y = 100*SettingsManager::Instance()->GetFitnessAccumY();
    int f_accum_head_y = 100*SettingsManager::Instance()->GetFitnessAccumHeadY();
    int f_dev_x = 100*SettingsManager::Instance()->GetFitnessDeviationX();
    int f_energy = 100*SettingsManager::Instance()->GetFitnessEnergy();

    f_dist_light_slider = new SliderWidget("Keep distance to target: ", f_dist_light, -100, 100, 1, 10, 10);
    f_dist_z_slider = new SliderWidget("Distance along Z-axis: ", f_dist_z, -100, 100, 1, 10, 10);
    f_max_y_slider = new SliderWidget("Jump high: ", f_max_y, -100, 100, 1, 10, 10);
    f_accum_y_slider = new SliderWidget("Keep center of mass high: ", f_accum_y, -100, 100, 1, 10, 10);
    f_accum_head_slider = new SliderWidget("Keep head high: ", f_accum_head_y, -100, 100, 1, 10, 10);
    f_dev_x_slider = new SliderWidget("Minimize deviation along X-axis: ", f_dev_x, -100, 100, 1, 10, 10);
    f_energy_slider = new SliderWidget("Energy efficiency: ", f_energy, -100, 100, 1, 10, 10);


    connect(generation_slider, SIGNAL(valueChanged(int)), this, SLOT(setValueGen(int)));
    connect(generation_size_slider, SIGNAL(valueChanged(int)), this, SLOT(setValuePop(int)));
    connect(elitism_slider, SIGNAL(valueChanged(int)), this, SLOT(setValueElit(int)));
    connect(mutation_internal_slider, SIGNAL(valueChanged(int)), this, SLOT(setValueMutInternal(int)));
    connect(mutation_sigma_slider, SIGNAL(valueChanged(int)), this, SLOT(setValueMutSigma(int)));

    connect(f_dist_light_slider, SIGNAL(valueChanged(int)), this, SLOT(FSetDistTarget(int)));
    connect(f_dist_z_slider, SIGNAL(valueChanged(int)), this, SLOT(FSetDistZ(int)));
    connect(f_max_y_slider, SIGNAL(valueChanged(int)), this, SLOT(FSetMaxY(int)));
    connect(f_accum_y_slider, SIGNAL(valueChanged(int)), this, SLOT(FSetAccumY(int)));
    connect(f_accum_head_slider, SIGNAL(valueChanged(int)), this, SLOT(FSetAccumHeadY(int)));
    connect(f_dev_x_slider, SIGNAL(valueChanged(int)), this, SLOT(FSetDeviationX(int)));
    connect(f_energy_slider, SIGNAL(valueChanged(int)), this, SLOT(FSetEnergy(int)));

    connect(simButton, SIGNAL(clicked()), this, SLOT(startEvolution()));


    connect(cancelButton, SIGNAL(clicked()), EM_, SLOT(RequestEndNow()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(evoDone()));
    connect(pauseButton, SIGNAL(clicked()), EM_, SLOT(RequestPauseNow()));

    connect(EM_, SIGNAL(NewCreature(const Creature &)), this, SLOT(GotNewCreature(const Creature &)));

    connect(&evolution_thread_starter_, SIGNAL(finished()), this, SLOT(evoDone()));

    setCentralWidget(glWidget);
    CreateStatusBar();
    CreateDockWindows();
    CreateActions();
    CreateMenus();
    CreateToolBar();


}

void MainCEWindow::setValueGen(int value) {
    SettingsManager::Instance()->SetMaxGenerations(value);
}

void MainCEWindow::setValuePop(int value) {
    SettingsManager::Instance()->SetPopulationSize(value);
}

void MainCEWindow::setValueSimTime(int value) {
    SettingsManager::Instance()->SetSimulationTime(value);
}

void MainCEWindow::setValueCO(int value) {
    SettingsManager::Instance()->SetCrossover((float)(value)/(float)(normalize));
}

void MainCEWindow::setValueElit(int value) {
    SettingsManager::Instance()->SetElitism((float)(value)/(float)(normalize));

}
void MainCEWindow::setValueMut(int value) {
    SettingsManager::Instance()->SetMutation((float)(value)/(float)(normalize));
    qDebug()<<SettingsManager::Instance()->GetMutation();
}
void MainCEWindow::setValueMutInternal(int value) {
    SettingsManager::Instance()->SetMutationInternal((float)(value)/(float)(normalize));
    qDebug()<<SettingsManager::Instance()->GetMutationInternal();
}
void MainCEWindow::setValueMutSigma(int value) {
    SettingsManager::Instance()->SetMutationSigma((float)(value)/(float)(normalize));
    qDebug()<<SettingsManager::Instance()->GetMutationSigma();
}
void MainCEWindow::setBodyDimension(int value) {
    float dim = (float)(value)/(float)(normalize);
    SettingsManager::Instance()->SetMainBodyDimension(Vec3(dim/2, dim/2, dim));
}

void MainCEWindow::FSetDistTarget(int value) {
    SettingsManager::Instance()->SetFitnessDistanceLight((float)(value)/(float)(normalize));
}
void MainCEWindow::FSetDistZ(int value) {
    SettingsManager::Instance()->SetFitnessDistanceZ((float)(value)/(float)(normalize));
}
void MainCEWindow::FSetMaxY(int value) {
    SettingsManager::Instance()->SetFitnessMaxY((float)(value)/(float)(normalize));
}
void MainCEWindow::FSetAccumY(int value) {
    SettingsManager::Instance()->SetFitnessAccumY((float)(value)/(float)(normalize));
}
void MainCEWindow::FSetAccumHeadY(int value) {
    SettingsManager::Instance()->SetFitnessAccumHeadY((float)(value)/(float)(normalize));
}
void MainCEWindow::FSetDeviationX(int value) {
    SettingsManager::Instance()->SetFitnessDeviationX((float)(value)/(float)(normalize));
}
void MainCEWindow::FSetEnergy(int value) {
    SettingsManager::Instance()->SetFitnessEnergy((float)(value)/(float)(normalize));
}

void MainCEWindow::keyPressEvent(QKeyEvent *e) {
    switch (e->key()){
        case Qt::Key_Escape:
            close();
            break;
        case Qt::Key_Up: {
            Vec3 new_pos = SettingsManager::Instance()->GetTargetPos();
            new_pos.z += 1;
            SettingsManager::Instance()->SetTargetPos(new_pos);
            std::cout << "Key_Up" << std::endl;
            break;
        }
        case Qt::Key_Down: {
            Vec3 new_pos = SettingsManager::Instance()->GetTargetPos();
            new_pos.z -= 1;
            SettingsManager::Instance()->SetTargetPos(new_pos);
            std::cout << "Key_Down" << std::endl;
            break;
        }
        case Qt::Key_Left: {
            Vec3 new_pos = SettingsManager::Instance()->GetTargetPos();
            new_pos.x += 1;
            SettingsManager::Instance()->SetTargetPos(new_pos);
            std::cout << "Key_Left" << std::endl;
            break;
        }
        case Qt::Key_Right: {
            Vec3 new_pos = SettingsManager::Instance()->GetTargetPos();
            new_pos.x -= 1;
            SettingsManager::Instance()->SetTargetPos(new_pos);
            std::cout << "Key_Right" << std::endl;
            break;
        }
        default:
            QWidget::keyPressEvent(e);
    }
}

static void startEvo(EvolutionManager* EM) {
    EM->startEvolutionProcess();
}

void MainCEWindow::startEvolution() {
    int gens = g_edit->text().toInt();
    int pops = p_edit->text().toInt();
    int sim_time = sim_time_edit->text().toInt();

    setValueGen(gens);
    setValuePop(pops);
    setValueSimTime(sim_time);

    sim_in_progress_ = true;
    if (!first_run_) {
     QMessageBox msgBox;
     msgBox.setText("Are you sure you want to start a new simulation?");
     msgBox.setInformativeText("Old simulation will be deleted.");
     msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
     msgBox.setDefaultButton(QMessageBox::Save);
     int ret = msgBox.exec();

     switch (ret) {
        case QMessageBox::Ok:
            break;
       case QMessageBox::Cancel:
           return;
       default:
           return;
         }
    }

    DisableCriticalWidgets();

    creatures_.clear();
    creature_list->clear();
    creature_count_ = 0;
    first_run_ = false;

    evolution_thread_starter_.setFuture(QtConcurrent::run(::startEvo, EM_));
}

void MainCEWindow::loadCreature(int index) {
    Scene::Instance()->RestartSimulation(std::vector<Creature>(1,
        creatures_.at(index)));
}

void MainCEWindow::GameOfWorms() {
    float displacement = 0.0f;

    float num_of_creatures = (float) creatures_.size() / 10.0f;
    std::vector<Creature> viz_creatures;
    for (float i = 0; i < creatures_.size(); i += num_of_creatures) {
        viz_creatures.push_back(creatures_[floor(i)+0.01f]);
        displacement += 1.0f;
    }
    Scene::Instance()->RestartSimulation(viz_creatures);

}

void MainCEWindow::DisableCriticalWidgets() {
    simButton->setDisabled(true);
    g_edit->setDisabled(true);
    p_edit->setDisabled(true);
    cancelButton->setDisabled(false);
}

void MainCEWindow::evoDone() {
    sim_in_progress_ = false;
    statusBar()->showMessage(tr("Simulation done!"));
    simButton->setDisabled(false);
    g_edit->setDisabled(false);
    p_edit->setDisabled(false);
    cancelButton->setDisabled(true);
    pauseButton->setDisabled(true);
}

void MainCEWindow::GotNewCreature(const Creature &new_creature) {
    std::cout << "Got creature! Fitness: " <<
        new_creature.GetFitness() << std::endl;
    Creature add = new_creature;
    creatures_.push_back(add);
    creature_count_++;
    creature_list->addItem(QString("%1").arg(creature_count_));
    int max = SettingsManager::Instance()->GetMaxGenerations();
    QString message = QString("Simulation in progress...   Generation %1 / %2").arg(creature_count_).arg(max);
    statusBar()->showMessage(tr(message.toStdString().c_str()));
}

void MainCEWindow::CreateActions() {
    exitAct = new QAction(tr("&Quit"), this);
    exitAct->setStatusTip(tr("Quit CreatureEvolution"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    evoAct = new QAction(tr("&Start Evolution!"), this);
    showSimDock = new QAction(tr("&Show Simulation properties"), this);
    connect(showSimDock, SIGNAL(triggered()), dock_simulation, SLOT(show()));

    showFitnessDock = new QAction(tr("&Show Fitness properties"), this);
    connect(showFitnessDock, SIGNAL(triggered()), dock_fitness, SLOT(show()));
}

void MainCEWindow::CreateMenus() {
    main_menu_ = menuBar()->addMenu(tr("&File"));
    main_menu_->addAction(exitAct);

    main_menu_ = menuBar()->addMenu(tr("&Windows"));
    main_menu_->addAction(showSimDock);
    main_menu_->addAction(showFitnessDock);
}

void MainCEWindow::CreateStatusBar() {
    statusBar()->showMessage(tr("Idle"));
}

void MainCEWindow::CreateToolBar() {
    QLabel* view_gen = new QLabel("View generation: ");
    tool_bar_ = addToolBar(tr("Main Tool Bar"));
    tool_bar_->addWidget(simButton);
    tool_bar_->addWidget(cancelButton);
    tool_bar_->addWidget(view_gen);
    tool_bar_->addWidget(creature_list);
    tool_bar_->setFloatable(false);
    tool_bar_->setMovable(false);
}

void MainCEWindow::CreateDockWindows() {
    dock_simulation = new QDockWidget(tr("Simulation properties"), this);
    dock_simulation->setAllowedAreas(Qt::LeftDockWidgetArea |
         Qt::RightDockWidgetArea);

    QVBoxLayout* dockedwidgets = new QVBoxLayout;
    QWidget* multiple_widgets = new QWidget;

    QHBoxLayout* creature_layout = new QHBoxLayout;
    QLabel* c_label = new QLabel("Creature type");
    QComboBox* c_list = new QComboBox();
    c_list->addItem("Pony");
    c_list->addItem("Worm");
    c_list->addItem("Crawler");
    c_list->addItem("Human");
    c_list->addItem("Table");
    c_list->addItem("Frog");
    creature_layout->addWidget(c_label);
    creature_layout->addWidget(c_list);

    connect (c_list, SIGNAL (activated (int)), this,
         SLOT (ChangeCreatureType (int)));

    QHBoxLayout* generation_layout = new QHBoxLayout;
    QLabel* g_label = new QLabel("Number of generations: ");
    g_edit = new QLineEdit(QString("%1").arg(SettingsManager::Instance()->GetMaxGenerations()));
    connect(g_edit, SIGNAL(valueChanged(int)), this, SLOT(setValueGen(int)));
    generation_layout->addWidget(g_label);
    generation_layout->addWidget(g_edit);
    

    QHBoxLayout* population_layout = new QHBoxLayout;
    QLabel* p_label = new QLabel("Population size: ");
    p_edit = new QLineEdit(QString("%1").arg(SettingsManager::Instance()->GetPopulationSize()));
    connect(p_edit, SIGNAL(valueChanged(int)), this, SLOT(setValuePop(int)));

    QHBoxLayout* sim_time_layout = new QHBoxLayout;
    QLabel* sim_time_label = new QLabel("Simulation time: ");
    sim_time_edit = new QLineEdit(QString("%1").arg(SettingsManager::Instance()->GetSimulationTime()));
    connect(sim_time_edit, SIGNAL(valueChanged(int)), this, SLOT(setValueSimTime(int)));

    population_layout->addWidget(p_label);
    population_layout->addWidget(p_edit);

    sim_time_layout->addWidget(sim_time_label);
    sim_time_layout->addWidget(sim_time_edit);

    dockedwidgets->addLayout(creature_layout);
    dockedwidgets->addLayout(generation_layout);
    dockedwidgets->addLayout(population_layout);
    dockedwidgets->addLayout(sim_time_layout);
    
    dockedwidgets->addWidget(elitism_slider);
    dockedwidgets->addWidget(mutation_internal_slider);
    dockedwidgets->addWidget(mutation_sigma_slider);

    multiple_widgets->setLayout(dockedwidgets);
    dock_simulation->setWidget(multiple_widgets);

    addDockWidget(Qt::RightDockWidgetArea, dock_simulation);

    dock_fitness = new QDockWidget(tr("Fitness properties"), this);
    dock_fitness->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    QVBoxLayout* dockedwidgets_fitness = new QVBoxLayout;
    QWidget* multiple_widgets_fitness = new QWidget;

    dockedwidgets_fitness->addWidget(f_dist_light_slider);
    dockedwidgets_fitness->addWidget(f_max_y_slider);
    dockedwidgets_fitness->addWidget(f_accum_y_slider);
    dockedwidgets_fitness->addWidget(f_accum_head_slider);

    multiple_widgets_fitness->setLayout(dockedwidgets_fitness);

    dock_fitness->setWidget(multiple_widgets_fitness);


    addDockWidget(Qt::LeftDockWidgetArea, dock_fitness);

}

void MainCEWindow::ChangeCreatureType(int type) {
    std::cout << "Creature type: " << type << std::endl;
    SettingsManager::Instance()->SetCreatureType(type);
}
