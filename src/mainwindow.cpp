#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

const int REFRESH_INTERVAL = 50; // [ms]
const int PLOT_SIZE = 200;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionQuit, SIGNAL(triggered()),
            qApp, SLOT(quit()));
    connect(ui->actionPause, SIGNAL(triggered()),
            this, SLOT(pauseContinueUI()));
    connect(ui->btnPause, SIGNAL(clicked()),
            this, SLOT(pauseContinueUI()));
    connect(ui->actionReset, SIGNAL(triggered()),
            this, SLOT(resetUI()));
    connect(ui->actionConnectDisconnect, SIGNAL(triggered()),
            this, SLOT(connectDisconnectDevices()));
    connect(ui->btnReset, SIGNAL(clicked()),
            this, SLOT(resetUI()));
    connect(ui->checkBoxShowHRV, SIGNAL(stateChanged(int)),
            this, SLOT(showHideHRV(int)));
    connect(ui->checkBoxShowSCL, SIGNAL(stateChanged(int)),
            this, SLOT(showHideSCL(int)));

    m_manager = new Manager(this);
    connect(m_manager, SIGNAL(newDeviceFound(int)),
            this, SLOT(addDevice(int)));

    connect(m_manager, SIGNAL(newValues(int,float,float)),
            this, SLOT(refreshValues(int,float,float)));


    m_basePlot = new BasePlot(this);
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

    m_vectTime = new QVector<double>(PLOT_SIZE);
    m_vectYHRV = new QVector<double>(PLOT_SIZE);
    m_vectYSCL = new QVector<double>(PLOT_SIZE);

//hack
counter = 0;
    m_paused = false;
    m_connected = m_manager->isConnected();
    if (m_connected)
        ui->actionConnectDisconnect->setText(tr("&Disconnect"));

    createStatusBar();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::createStatusBar() {
    m_lblStatus = new QLabel(ui->statusBar);
    m_lblStatus->setMinimumSize(m_lblStatus->sizeHint());

    ui->statusBar->addWidget(m_lblStatus, 20);
    updateStatusBar();
}


void MainWindow::updateStatusBar() {
    QString status = m_connected ? tr("Connected") : tr("Disconnected");
    m_lblStatus->setText(tr("Status: %1").arg(status));
}


void MainWindow::refreshUI() {
    // Sometimes we get bad values - we don't want to show them
    if (m_hrv > 4 || m_hrv < 1e-1)
        return;

    if (m_vectTime->count() >= PLOT_SIZE) {
        m_vectYHRV->pop_front();
        m_vectYSCL->pop_front();
        m_vectTime->pop_front();
    }

    m_basePlot->setAxisScale(2, counter - PLOT_SIZE, counter);

    m_vectYHRV->append(m_hrv);
    m_vectYSCL->append(m_scl);
    m_vectTime->append(counter);
    counter += 1;

    m_curveHRV->setData(*m_vectTime, *m_vectYHRV);
    m_curveSCL->setData(*m_vectTime, *m_vectYSCL);
    m_basePlot->replot();
}


void MainWindow::pauseContinueUI() {
    if (!m_paused) {
        m_refreshTimer->stop();
        ui->btnPause->setText(tr("Continue"));
        ui->actionPause->setText(tr("&Continue"));
        m_paused = true;
    } else {
        m_refreshTimer->start();
        ui->btnPause->setText(tr("Pause"));
        ui->actionPause->setText(tr("&Pause"));
        m_paused = false;
    }
}


void MainWindow::connectDisconnectDevices() {
    if (!m_connected) {
        if ((m_connected = m_manager->connectDevices()) == true)
            ui->actionConnectDisconnect->setText(tr("&Disconnect"));
    } else {
        m_manager->disconnectDevices();
        ui->actionConnectDisconnect->setText(tr("&Connect"));
        m_connected = false;
    }

    updateStatusBar();
}


void MainWindow::resetUI() {
    m_vectYHRV->resize(0);
    m_vectYSCL->resize(0);
    m_vectTime->resize(0);
    counter = 0;
    m_basePlot->replot();
}


void MainWindow::refreshValues(int deviceID, float hrv, float scl) {
    Q_UNUSED(deviceID);

    m_hrv = hrv;
    m_scl = scl;

    ui->lblHRV->setText(QString::number(m_hrv, 'f', 6));
    ui->lblSCL->setText(QString::number(m_scl, 'f', 6));
}


void MainWindow::showHideHRV(int state) {
    if (state == Qt::Checked)
        m_curveHRV->attach(m_basePlot);
    else
        m_curveHRV->detach();
}


void MainWindow::showHideSCL(int state) {
    if (state == Qt::Checked)
        m_curveSCL->attach(m_basePlot);
    else
        m_curveSCL->detach();
}


void MainWindow::addDevice(int deviceID) {
    Q_UNUSED(deviceID);
}
