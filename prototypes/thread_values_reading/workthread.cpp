#include "workthread.h"
#include <QDebug>

WorkThread::WorkThread(QObject *parent) :
    QObject(parent)
{

    m_l = lightstone_create();
    int ret = lightstone_open(m_l, 0);
    if (ret < 0)
        qDebug() << "cant open device!";

            //printf("Serial: %s\n", lightstone_get_serial(test));

            //printf("Version: %s\n", lightstone_get_version(test));

    m_timer = new QTimer(this);
    m_timer->setInterval(0);
    connect(m_timer, SIGNAL(timeout()),
            this, SLOT(getValue()));
}


void WorkThread::getValue() {
    lightstone_info r;
    r = lightstone_get_info(m_l);

    m_val.first = QString::number(r.hrv);
    m_val.second = QString::number(r.scl);

    emit gotValues(m_val.first, m_val.second);
}


void WorkThread::startGetting() {
    m_timer->start();
    qDebug() << "started getting";
}


WorkThread::~WorkThread() {
    lightstone_delete(m_l);
}
