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


    int max_gen = SettingsManager::Instance()->GetMaxGenerations();
    SliderWidget* generation_slider = new SliderWidget("Number of generations: ", max_gen, 100, 1, 10, 10);
    SliderWidget* generation_slider1 = new SliderWidget("Number of generations: ", max_gen, 100, 1, 10, 10);
    SliderWidget* generation_slider2 = new SliderWidget("Number of generations: ", max_gen, 100, 1, 10, 10);
    SliderWidget* generation_slider3 = new SliderWidget("Number of generations: ", max_gen, 100, 1, 10, 10);

    connect(generation_slider, SIGNAL(valueChanged(int)), this, SLOT(setValueGen(int)));

    layout_button->addWidget(simButton);
    layout_button->addWidget(loadButton);
    layout_button->addWidget(renderOneButton);
    layout_button->addWidget(renderAllButton);

    layout_control->addWidget(generation_slider);
    layout_control->addWidget(generation_slider1);
    layout_control->addWidget(generation_slider2);
    layout_control->addWidget(generation_slider3);
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

}


/*QVBoxLayout *MainCEWindow::createSliderLayout(QSlider *slider, int range, int step,
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
}*/


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
