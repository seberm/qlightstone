#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include <QVector>

#include "baseplot.h"
#include "manager.h"
class Manager;
class BasePlot;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    Manager *m_manager;
    QTimer *m_refreshTimer;

    BasePlot *m_basePlot;
    QwtPlotCurve *m_curveHRV;
    QwtPlotCurve *m_curveSCL;

    QVector<double> *m_vectTime;
    int counter;
    QVector<double> *m_vectYHRV;
    QVector<double> *m_vectYSCL;

    float m_hrv;
    float m_scl;

    bool m_paused;
    bool m_connected;

    QLabel *m_lblStatus;
    void createStatusBar();
    void updateStatusBar();

private slots:
    void refreshValues(int deviceID, float hrv, float scl);
    void refreshUI();
    void pauseContinueUI();
    void resetUI();
    void connectDisconnectDevices();
    void addDevice(int deviceID);
    void showHideHRV(int state);
    void showHideSCL(int state);
};

#endif // MAINWINDOW_H
