#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"


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

    connect(m_manager, SIGNAL(newValues(int,float,float)),
            this, SLOT(refreshValues(int,float,float)));
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::refreshValues(int deviceID, float hrv, float scl) {
    Q_UNUSED(deviceID);

    ui->lblHRV->setText(QString::number(hrv, 'f', 6));
    ui->lblSCL->setText(QString::number(scl, 'f', 6));
}


void MainWindow::addDevice(int deviceID) {
    Q_UNUSED(deviceID);
}
