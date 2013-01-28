#include <QDebug>
#include <QThread>
#include "manager.h"


Manager::Manager(QObject *parent) :
    QObject(parent)
{
    if (!(m_fd = lightstone_create())) {
        qWarning() << tr("] Can't create lightstone file descriptor");
        return;
    }

    int count = lightstone_get_count(m_fd);
    if (!count) {
        qWarning() << tr("] No lightstone HW connected!");
        return;
    }

    int ret = -1;
    for (int i = 0; i < count; ++i) {
        qDebug() << tr("] Opening device: %1").arg(i);
        ret = lightstone_open(m_fd, i);
        if (ret < 0) {
            qWarning() << tr("] Cannot open lightstone: %1").arg(i);
            qWarning() << this->getLightstoneErr(ret);
            return;
        }

        Device *d = new Device(m_fd, i);
        connect(d, SIGNAL(serialFound(QString)),
                this, SLOT(deviceSerialFound(QString)));

        connect(d, SIGNAL(valuesFound(float,float)),
                this, SLOT(deviceValuesFound(float,float)));

        m_devices.append(d);
        qDebug() << tr("] Device %1 successfully opened").arg(d->getID());
        emit newDeviceFound(d->getID());

        d->start();
    }
}


Manager::~Manager() {
    foreach (Device *d, m_devices)
        delete d;

    // Close and delete lightstone device
    lightstone_delete(m_fd);
}


/*
void Manager::run() {
  //thread test
        QThread *thread = new QThread(this);

        connect(thread, SIGNAL(started()), d, SLOT(lookUpSerial()));
        connect(d, SIGNAL(serialFound(QString)), thread, SLOT(quit()));
        //connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
        d->moveToThread(thread);

        workerThread->start();
    foreach (Device *d, m_devices) {
        QThread *workerThread = new QThread(this);

        connect(workerThread, SIGNAL(started()), d, SLOT(lookUpSerial()));
        connect(d, SIGNAL(serialFound(QString)), workerThread, SLOT(quit()));
        //connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
        d->moveToThread(workerThread);

        // Starts an event loop, and emits workerThread->started()
        workerThread->start();
    }
}
*/


const QString Manager::getLightstoneErr(int err) {
    switch (err) {
    case E_LIGHTSTONE_NOT_INITED:
        return tr("device not initialized");

    case E_LIGHTSTONE_NOT_OPENED:
        return tr("device was not opened");

    case E_LIGHTSTONE_DRIVER_ERROR:
        return tr("driver error (do you have permission to read usb?)");

    default:
        return tr("Unknown error");
    }
}


Device* Manager::getDeviceByID(int deviceID) {
    return m_devices.at(deviceID);
}


void Manager::deviceSerialFound(const QString &serial) {
    Device *d = qobject_cast<Device*>(sender());
    qDebug() << tr("] Device %1: Serial: %2").arg(d->getID()).arg(serial);
}


void Manager::deviceValuesFound(float hrv, float scl) {
    Device *d = qobject_cast<Device*>(sender());
    emit newValues(d->getID(), hrv, scl);
}
