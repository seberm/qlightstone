#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:
    void refreshValues(int deviceID, float hrv, float scl);
    void addDevice(int deviceID);
};

#endif // MAINWINDOW_H
