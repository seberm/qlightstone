#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QObject>
#include <QPair>
#include <QTimer>

#include <lightstone/lightstone.h>

class WorkThread : public QObject
{
    Q_OBJECT
public:
    explicit WorkThread(QObject *parent = 0);
    ~WorkThread();
    
signals:
    void gotValues(QString,QString);
    
public slots:
    void startGetting();

private:
    QTimer *m_timer;
    QPair<QString,QString> m_val;
    lightstone *m_l;

private slots:
    void getValue();
    
};

#endif // WORKTHREAD_H
