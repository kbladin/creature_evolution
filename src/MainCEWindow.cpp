#include "GLWidget.h"
#include "MainCEWindow.h"

MainCEWindow::MainCEWindow(CreatureEvolution* ce)
{
    creature_evo_ = ce;
    QGLFormat glFormat;
    glFormat.setVersion( 3, 2 );
    glFormat.setProfile( QGLFormat::CoreProfile ); // Requires >=Qt-4.8.0
    glFormat.setSampleBuffers( true );
    //QGLFormat::setDefaultFormat(glFormat);
    glWidget = new GLWidget(glFormat,0,creature_evo_);

    QHBoxLayout *layout_main = new QHBoxLayout;
    QVBoxLayout *layout_control = new QVBoxLayout;
    QVBoxLayout *layout_button = new QVBoxLayout;
    QPushButton *renderOneButton = new QPushButton("Render best creature! (not working)");
    QPushButton *renderAllButton = new QPushButton("3. Render all generations!");
    QPushButton *simButton = new QPushButton("1. Start simulation.");
    QPushButton *loadButton = new QPushButton("2. Load creatures.");

    //QSignalMapper *signalMapper = new QSignalMapper(this);

      /* for (int i = 0; i < 4; ++i) {
        slide[i] = createSlider();
        connect(slide[i], SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
        controlLayout->addWidget(slide[i]);
        signalMapper->setMapping(slide[i], i);
        connect(slide[i], SIGNAL(valueChanged(int)), signalMapper, SLOT(map()));
    }*/
    //connect(signalMapper, SIGNAL(mapped(int)), this, SIGNAL(setValue(int)));
    //connect(signalMapper, SIGNAL(mapped(int)), this, SIGNAL(digitClicked(int)));

    QSlider *slide[number_of_sliders];
    QVBoxLayout *boxLayout[number_of_sliders];
    QLabel *label_text[number_of_sliders];
    const std::string label_strings[number_of_sliders] = {"Generations:", "Population:", "Cross-over (%) :", "Elitism (%) :", "Mutation (%) :", "Body size:"};


    for(int i = 0; i < number_of_sliders; i++)
    {
        boxLayout[i] = new QVBoxLayout;
        label_text[i] = new QLabel(tr(label_strings[i].c_str()));

        slide[i] = new QSlider(Qt::Horizontal);
        slide[i]->setRange(0, 100);
        slide[i]->setSingleStep(1);
        slide[i]->setPageStep(10);
        slide[i]->setTickInterval(10);
        slide[i]->setTickPosition(QSlider::TicksRight);

        boxLayout[i]->addWidget(label_text[i]);
        boxLayout[i]->addWidget(slide[i]);
        layout_control->addLayout(boxLayout[i]);
    }
    //connect(slider, SIGNAL(valueChanged(int)), this, SLOT(setValueGen(int)));

    //QSignalMapper *signalMapper = new QSignalMapper(this);

    /*box_gen = createSliderLayout(slide_gen, 100, 1, 10, 10, "Generation:", &setValueGen);
    box_pop = createSliderLayout(slide_pop, 100, 1, 10, 10, "Population:");
    box_CO = createSliderLayout(slide_CO, 100, 1, 10, 10, "Cross-over(%):");
    box_elit = createSliderLayout(slide_elit, 100, 1, 10, 10, "Elitism(%):");
    box_mut = createSliderLayout(slide_mut, 100, 1, 10, 10, "Mutation(%):");
    box_change_dim = createSliderLayout(slide_change_dim, 100, 1, 10, 10, "Change body dimension");*/

    //controlLayout->addWidget(slide[0]);
    /*layout_control->addLayout(box_gen);
    layout_control->addLayout(box_pop);
    layout_control->addLayout(box_CO);
    layout_control->addLayout(box_elit);
    layout_control->addLayout(box_mut);
    layout_control->addLayout(box_change_dim);*/

    layout_button->addWidget(simButton);
    layout_button->addWidget(loadButton);
    layout_button->addWidget(renderOneButton);
    layout_button->addWidget(renderAllButton);

    layout_main->addWidget(glWidget);
    layout_main->addLayout(layout_control);
    layout_main->addLayout(layout_button);

    setLayout(layout_main);
    setWindowTitle(tr("Creature Evolution"));

    // ----- Connect buttons -----
    //connect(dummyButton,SIGNAL(clicked()), this, SLOT(testPrint()));
    connect(renderAllButton,SIGNAL(clicked()), glWidget, SLOT(enableRendering()));
    connect(simButton, SIGNAL(clicked()), this, SLOT(startEvolution()));
    connect(loadButton, SIGNAL(clicked()), this, SLOT(loadCreature()));
    connect(&evolution_thread_starter_, SIGNAL(finished()), this, SLOT(evoDone()));
    // ----- Connect sliders -----
    connect(slide[0], SIGNAL(valueChanged(int)), this, SLOT(setValueGen(int)));
    connect(slide[1], SIGNAL(valueChanged(int)), this, SLOT(setValuePop(int)));
    connect(slide[2], SIGNAL(valueChanged(int)), this, SLOT(setValueCO(int)));
    connect(slide[3], SIGNAL(valueChanged(int)), this, SLOT(setValueElit(int)));
    connect(slide[4], SIGNAL(valueChanged(int)), this, SLOT(setValueMut(int)));
    connect(slide[5], SIGNAL(valueChanged(int)), this, SLOT(setBodyDimension(int)));

    /*connect(slide_gen, SIGNAL(valueChanged(int)), this, SLOT(setValueGen(int)));
    connect(slide_pop, SIGNAL(valueChanged(int)), this, SLOT(setValuePop(int)));
    connect(slide_CO, SIGNAL(valueChanged(int)), this, SLOT(setValueCO(int)));
    connect(slide_elit, SIGNAL(valueChanged(int)), this, SLOT(setValueElit(int)));
    connect(slide_mut, SIGNAL(valueChanged(int)), this, SLOT(setValueMut(int)));
    connect(slide_change_dim, SIGNAL(valueChanged(int)), this, SLOT(setBodyDimension(int)));*/

}

/*
QVBoxLayout *MainCEWindow::createSliderLayout(QSlider *slider, int range, int step,
                                              int page, int tick, std::string label, void (*function)(int))
{
    QVBoxLayout *boxLayout = new QVBoxLayout;
    QLabel *label_text = new QLabel(tr(label.c_str()));

    slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, range);
    slider->setSingleStep(step);
    slider->setPageStep(page);
    slider->setTickInterval(tick);
    slider->setTickPosition(QSlider::TicksRight);
    //connect(slider, SIGNAL(valueChanged(int)), this, SLOT(function(int)));
    boxLayout->addWidget(label_text);
    boxLayout->addWidget(slider);

    return boxLayout;
}
*/

void MainCEWindow::setValueGen(int value) {
    SettingsManager::Instance()->SetMaxGenerations(value);
}

void MainCEWindow::setValuePop(int value) {
    SettingsManager::Instance()->SetPopulationSize(value);
}

void MainCEWindow::setValueCO(int value) {
    SettingsManager::Instance()->SetCrossover((float)(value)/(float)(normalize));
}

void MainCEWindow::setValueElit(int value) {
    SettingsManager::Instance()->SetElitism((float)(value)/(float)(normalize));

}
void MainCEWindow::setValueMut(int value) {
    SettingsManager::Instance()->SetMutation((float)(value)/(float)(normalize));
    qDebug()<<(float)(value)/(float)(normalize);
}
void MainCEWindow::setBodyDimension(int value) {
    float dim = (float)(value)/(float)(normalize);
    SettingsManager::Instance()->SetMainBodyDimension(Vec3(dim/2, dim/2, dim));
}

void MainCEWindow::changePressed() {
}

void MainCEWindow::changeReleased() {
}

void MainCEWindow::keyPressEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}

void MainCEWindow::testPrint() {
    qDebug("Button works!");
}

static void startEvo(CreatureEvolution* CE) {
    CE->Run();
}

void MainCEWindow::startEvolution() {
    QApplication::setOverrideCursor(Qt::BusyCursor);
    evolution_thread_starter_.setFuture(QtConcurrent::run(::startEvo, creature_evo_));
    evoDone();
}

void MainCEWindow::loadCreature() {
    creature_evo_->LoadAllBestCreatures();
}

void MainCEWindow::evoDone() {
    QApplication::restoreOverrideCursor();
}

void MainCEWindow::renderWorm() {
}
