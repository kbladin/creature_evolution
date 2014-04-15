#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtDebug>
#include <QSignalMapper>
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

    QHBoxLayout *mainLayout = new QHBoxLayout;
    QHBoxLayout *controlLayout = new QHBoxLayout;
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    QPushButton *simButton = new QPushButton("Start simulation.");
    QPushButton *dummyButton = new QPushButton("Push for pleasure!");
    QPushButton *testButton = new QPushButton("Set body dimension");

    QSignalMapper *signalMapper = new QSignalMapper(this);

    slide[0] = createSlider(100, 1, 10, 10);
    slide_pop = createSlider(100, 1, 10, 10);
    slide_CO = createSlider(100, 1, 10, 10);
    slide_elit = createSlider(100, 1, 10, 10);
    slide_mut = createSlider(100, 1, 10, 10);
    slide_change_dim = createSlider(100, 1, 10, 10);

    controlLayout->addWidget(slide[0]);
    controlLayout->addWidget(slide_pop);
    controlLayout->addWidget(slide_CO);
    controlLayout->addWidget(slide_elit);
    controlLayout->addWidget(slide_mut);
    controlLayout->addWidget(slide_change_dim);

    buttonLayout->addWidget(dummyButton);
    buttonLayout->addWidget(simButton);
    buttonLayout->addWidget(testButton);
    mainLayout->addWidget(glWidget);
    mainLayout->addLayout(controlLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
    setWindowTitle(tr("Creature Evolution"));

    // ----- Connect buttons -----
    connect(simButton, SIGNAL(clicked()), this, SLOT(startEvolution()));
    connect(simButton, SIGNAL(clicked()), glWidget, SLOT(enableRendering()));
    connect(testButton, SIGNAL(pressed()), this, SLOT(changePressed()));      // Should this do something?
    //connect(testButton, SIGNAL(released()), this, SLOT(changeReleased()));    // Should this do something?

    // ----- Connect sliders -----
    connect(slide[0], SIGNAL(valueChanged(int)), this, SLOT(setValueGen(int)));
    connect(slide_pop, SIGNAL(valueChanged(int)), this, SLOT(setValuePop(int)));
    connect(slide_CO, SIGNAL(valueChanged(int)), this, SLOT(setValueCO(int)));
    connect(slide_elit, SIGNAL(valueChanged(int)), this, SLOT(setValueElit(int)));
    connect(slide_mut, SIGNAL(valueChanged(int)), this, SLOT(setValueMut(int)));
    connect(slide_change_dim, SIGNAL(valueChanged(int)), this, SLOT(setBodyDimension(int)));

}

QSlider *MainCEWindow::createSlider(int range, int step, int page, int tick){
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, range); // 10
    slider->setSingleStep(step); // 1
    slider->setPageStep(page); // 10
    slider->setTickInterval(tick); // 10
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}

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
    qDebug()<<"hej";
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

void MainCEWindow::startEvolution() {
    creature_evo_->Run();
}

void MainCEWindow::renderWorm() {

}
