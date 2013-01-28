#include <QDebug>
#include <QThread>
#include "mainwindow.h"
#include "workthread.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    WorkThread *t = new WorkThread;
    connect(t, SIGNAL(gotValues(QString,QString)),
            this, SLOT(changeValues(QString,QString)));

        QThread *worker = new QThread(this);
        connect(worker, SIGNAL(started()), t, SLOT(startGetting()));
        //connect(t, SIGNAL(serialFound(QString)), worker, SLOT(quit()));
        t->moveToThread(worker);

        // Starts an event loop, and emits workerThread->started()
        worker->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::changeValues(const QString &first,const QString &sec) {
    qDebug() << "Got values: " << first << "; " << sec;
}
