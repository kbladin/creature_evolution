#include "GLWidget.h"
#include "MainCEWindow.h"
#include "SettingsManager.h"

MainCEWindow::MainCEWindow(CreatureEvolution* ce)
{
    creature_evo_ = ce;
    QGLFormat glFormat;
    glFormat.setVersion( 3, 2 );
    glFormat.setProfile( QGLFormat::CoreProfile ); // Requires >=Qt-4.8.0
    glFormat.setSampleBuffers( true );
    //QGLFormat::setDefaultFormat(glFormat);
    glWidget = new GLWidget(glFormat,0,creature_evo_);

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

    /*SettingsManager::()->setPopulationSize(5);
    SettingsManager::Instance()->setCrossover(0.8);
    SettingsManager::Instance()->setElitism(0.2);
    SettingsManager::Instance()->setMutation(0.8);
    */

    QHBoxLayout *layout_main = new QHBoxLayout;
    QVBoxLayout *layout_controll = new QVBoxLayout;
    QVBoxLayout *layout_button = new QVBoxLayout;
    QPushButton *button_dummy = new QPushButton("Push for pleasure!");
    QPushButton *button_sim = new QPushButton("Start simulation.");
    QPushButton *button_test = new QPushButton("Change color");

    QSignalMapper *signalMapper = new QSignalMapper(this);

    box_gen = createSliderLayout(slide_gen, 100, 1, 10, 10, "Generation:");
    box_pop = createSliderLayout(slide_pop, 100, 1, 10, 10, "Population:");
    box_CO = createSliderLayout(slide_CO, 100, 1, 10, 10, "Cross-over(%):");
    box_elit = createSliderLayout(slide_elit, 100, 1, 10, 10, "Elitism(%):");
    box_mut = createSliderLayout(slide_mut, 100, 1, 10, 10, "Mutation(%):");

    //controlLayout->addWidget(slide[0]);
    layout_controll->addLayout(box_gen);
    layout_controll->addLayout(box_pop);
    layout_controll->addLayout(box_CO);
    layout_controll->addLayout(box_elit);
    layout_controll->addLayout(box_mut);

    layout_button->addWidget(button_dummy);
    layout_button->addWidget(button_sim);
    layout_button->addWidget(button_test);

    layout_main->addWidget(glWidget);
    layout_main->addLayout(layout_controll);
    layout_main->addLayout(layout_button);

    setLayout(layout_main);
    setWindowTitle(tr("Creature Evolution"));

    // ----- Connect buttons -----
    connect(button_dummy,SIGNAL(clicked()), glWidget, SLOT(enableRendering()));
    connect(button_sim, SIGNAL(clicked()), this, SLOT(startEvolution()));
    connect(button_test, SIGNAL(pressed()), this, SLOT(changePressed()));
    connect(button_test, SIGNAL(released()), this, SLOT(changeReleased()));
    // ----- Connect sliders -----
    //connect(slide[0], SIGNAL(valueChanged(int)), this, SLOT(setValueGen(int)));
    //connect(slide_gen, SIGNAL(valueChanged(int)), this, SLOT(setValueGen(int)));
    //connect(slide_pop, SIGNAL(valueChanged(int)), this, SLOT(setValuePop(int)));
    //connect(slide_CO, SIGNAL(valueChanged(int)), this, SLOT(setValueCO(int)));
    //connect(slide_elit, SIGNAL(valueChanged(int)), this, SLOT(setValueElit(int)));
}

QVBoxLayout *MainCEWindow::createSliderLayout(QSlider *slider, int range, int step,
                                          int page, int tick, std::string label)
{
    QVBoxLayout *boxLayout = new QVBoxLayout;
    QLabel *label_text = new QLabel(tr(label.c_str()));

    slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, range);
    slider->setSingleStep(step);
    slider->setPageStep(page);
    slider->setTickInterval(tick);
    slider->setTickPosition(QSlider::TicksRight);

    boxLayout->addWidget(label_text);
    boxLayout->addWidget(slider);

    return boxLayout;
}

/*SettingsManager::()->setPopulationSize(5);
SettingsManager::Instance()->setCrossover(0.8);
SettingsManager::Instance()->setElitism(0.2);
SettingsManager::Instance()->setMutation(0.8);*/
void MainCEWindow::setValueGen(int value)
{
    SettingsManager::Instance()->SetMaxGenerations(value);
    qDebug()<<value;
}

void MainCEWindow::setValuePop(int value)
{
    SettingsManager::Instance()->SetPopulationSize(value);
    qDebug()<<value;
}

void MainCEWindow::setValueCO(int value)
{
    SettingsManager::Instance()->SetCrossover(float(value/normalize));
    qDebug()<<(float)value/normalize;
}

void MainCEWindow::setValueElit(int value)
{
    SettingsManager::Instance()->SetElitism(float(value/normalize));
    qDebug()<<(float)value/normalize;
}
void MainCEWindow::setValueMut(int value)
{
    SettingsManager::Instance()->SetMutation(float(value/normalize));
    qDebug()<<(float)value/normalize;
}

void MainCEWindow::changePressed()
{

}

void MainCEWindow::changeReleased()
{

}

void MainCEWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}

void MainCEWindow::testPrint() {
    qDebug("Button works!");
}

void MainCEWindow::startEvolution() {
    creature_evo_->Run();
}

void MainCEWindow::renderWorm() {

}
