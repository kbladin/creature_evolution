
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
    QHBoxLayout* renderLayout = new QHBoxLayout;
    QPushButton *renderOneButton = new QPushButton("Render best creature! (not working)");
    QPushButton *renderAllButton = new QPushButton("3. Render all generations!");
    QPushButton *simButton = new QPushButton("1. Start simulation.");
    QPushButton *loadButton = new QPushButton("2. Load creatures.");
    

    controlLayout->addWidget(simButton);
    controlLayout->addWidget(loadButton);

    renderLayout->addWidget(renderOneButton);
    renderLayout->addWidget(renderAllButton);

    controlLayout->addLayout(renderLayout);

    mainLayout->addWidget(glWidget);
    mainLayout->addLayout(controlLayout);

    setLayout(mainLayout);

    setWindowTitle(tr("Creature Evolution"));
    //connect(dummyButton,SIGNAL(clicked()), this, SLOT(testPrint()));
    connect(renderAllButton,SIGNAL(clicked()), glWidget, SLOT(enableRendering()));
    connect(simButton, SIGNAL(clicked()), this, SLOT(startEvolution()));
    connect(loadButton, SIGNAL(clicked()), this, SLOT(loadCreature()));
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

void MainCEWindow::loadCreature() {
    creature_evo_->LoadAllBestCreatures();
}

void MainCEWindow::evoDone() {
    QApplication::restoreOverrideCursor();
}

void MainCEWindow::renderWorm() {

}
