#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

const int REFRESH_INTERVAL = 50; // [ms]


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


    m_basePlot = new QwtPlot(this);
    m_basePlot->setAxisAutoScale(0);
    m_curveHRV = new QwtPlotCurve(tr("HRV"));
    m_curveHRV->setPen(QPen(Qt::red));
    m_curveSCL = new QwtPlotCurve(tr("SCL"));
    m_curveSCL->setPen(QPen(Qt::blue));

    m_curveHRV->attach(m_basePlot);
    m_curveSCL->attach(m_basePlot);

    ui->layoutTabPlots->addWidget(m_basePlot);

    m_refreshTimer = new QTimer(this);
    connect(m_refreshTimer, SIGNAL(timeout()),
            this, SLOT(refreshUI()));

    m_refreshTimer->start(REFRESH_INTERVAL);


    m_vectTime = new QVector<double>(100);
    m_vectYHRV = new QVector<double>(100);
    m_vectYSCL = new QVector<double>(100);

//hack
counter = 0;
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::refreshUI() {
    //small hack
    if (m_hrv < 1.5)
        m_vectYHRV->append(m_hrv);
    else
        return;

    m_vectYSCL->append(m_scl);
    m_vectTime->append(counter);
    counter += 0.2;

    m_curveHRV->setData(*m_vectTime, *m_vectYHRV);
    m_curveSCL->setData(*m_vectTime, *m_vectYSCL);
    m_basePlot->replot();
}


void MainWindow::refreshValues(int deviceID, float hrv, float scl) {
    Q_UNUSED(deviceID);

    m_hrv = hrv;
    m_scl = scl;

    ui->lblHRV->setText(QString::number(m_hrv, 'f', 6));
    ui->lblSCL->setText(QString::number(m_scl, 'f', 6));
}


void MainWindow::addDevice(int deviceID) {
    Q_UNUSED(deviceID);
}
