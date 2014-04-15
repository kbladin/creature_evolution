
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QApplication>

#include "GLWidget.h"
#include "MainCEWindow.h"

MainCEWindow::MainCEWindow(CreatureEvolution* ce)
{
    std::cout << "Setting up window." << std::endl;
    creature_evo_ = ce;
    QGLFormat glFormat;
    glFormat.setVersion( 3, 2 );
    glFormat.setProfile( QGLFormat::CoreProfile ); // Requires >=Qt-4.8.0
    glFormat.setSampleBuffers( true );
    //QGLFormat::setDefaultFormat(glFormat);
    glWidget = new GLWidget(glFormat,0,creature_evo_);




    QHBoxLayout *mainLayout = new QHBoxLayout;
    QVBoxLayout* controlLayout = new QVBoxLayout;
    QPushButton *dummyButton = new QPushButton("Push for pleasure!");
    QPushButton *simButton = new QPushButton("Start simulation.");
    controlLayout->addWidget(dummyButton);
    controlLayout->addWidget(simButton);

    mainLayout->addWidget(glWidget);
    mainLayout->addLayout(controlLayout);

    setLayout(mainLayout);

    setWindowTitle(tr("Creature Evolution"));
    //connect(dummyButton,SIGNAL(clicked()), this, SLOT(testPrint()));
    connect(dummyButton,SIGNAL(clicked()), glWidget, SLOT(enableRendering()));
    connect(simButton, SIGNAL(clicked()), this, SLOT(startEvolution()));
    
    connect(&evolution_thread_starter_, SIGNAL(finished()), this, SLOT(evoDone()));


    std::cout << "Done!" << std::endl;
}

QSlider *MainCEWindow::createSlider()
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 360 * 16);
    slider->setSingleStep(16);
    slider->setPageStep(15 * 16);
    slider->setTickInterval(15 * 16);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
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

static void startEvo(CreatureEvolution* CE) {
    CE->Run();
}

void MainCEWindow::startEvolution() {
    QApplication::setOverrideCursor(Qt::BusyCursor);
    evolution_thread_starter_.setFuture(QtConcurrent::run(::startEvo, creature_evo_));
    evoDone();
}

void MainCEWindow::evoDone() {
    QApplication::restoreOverrideCursor();
}

void MainCEWindow::renderWorm() {

}
