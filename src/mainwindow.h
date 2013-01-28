#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QVector>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>

#include "manager.h"
class Manager;


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

    QwtPlot *m_basePlot;
    QwtPlotCurve *m_curveHRV;
    QwtPlotCurve *m_curveSCL;

    QVector<double> *m_vectXHRV;
    float counter;
    QVector<double> *m_vectYHRV;

    float m_hrv;
    float m_scl;

private slots:
    void refreshValues(int deviceID, float hrv, float scl);
    void refreshUI();
    void addDevice(int deviceID);
};

#endif // MAINWINDOW_H
