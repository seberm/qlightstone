#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"


const int REFRESH_TIME = 500; // == 500ms

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionQuit, SIGNAL(triggered()),
            qApp, SLOT(quit()));


    m_manager = new Manager(this);
    connect(m_manager, SIGNAL(newDeviceFound(int)),
            this, SLOT(addDevice(int)));

    m_refreshTimer = new QTimer(this);
    connect(m_refreshTimer, SIGNAL(timeout()),
            this, SLOT(refreshUI()));
    m_refreshTimer->start(REFRESH_TIME);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::refreshUI() {
    Device *d = m_manager->getDeviceByID(0);
    QPair<float,float> vals = d->getValues();

    //this->setWindowTitle(QString::number(vals.first));
    qDebug() << "hrv:" << vals.first << "; scl:" << vals.second;
}


void MainWindow::addDevice(int id) {
    ui->listWidgetDevices->addItem(QString::number(id));
}
