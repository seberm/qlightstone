#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

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

private slots:
    void refreshUI();
    void addDevice(int id);
};

#endif // MAINWINDOW_H
