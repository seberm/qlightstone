#include <QDebug>
#include <QThread>
#include "manager.h"


Manager::Manager(QObject *parent) :
    QObject(parent)
{
    m_fd = NULL;

    // Automatically initialize all devices
    connectDevices();
}


Manager::~Manager() {
    disconnectDevices();
}


bool Manager::connectDevices() {
    // Already initialized and connected
    if (m_fd)
        return false;

    if (!(m_fd = lightstone_create())) {
        qWarning() << tr("] Can't create lightstone file descriptor");
        return false;
    }

    int count = lightstone_get_count(m_fd);
    if (!count) {
        lightstone_delete(m_fd);
        m_fd = NULL;
        qWarning() << tr("] No lightstone HW connected!");
        return false;
    }

    /* For now... support only for one device! */
    int ret = -1;
    /*
    for (int i = 0; i < count; ++i) {
    */
    int i = 0;
        qDebug() << tr("] Opening device: %1").arg(i);
        ret = lightstone_open(m_fd, i);
        if (ret < 0) {
            qWarning() << tr("] Cannot open lightstone: %1").arg(i);
            qWarning() << this->getLightstoneErr(ret);

            lightstone_delete(m_fd);
            m_fd = NULL;
            return false;
            //continue;
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
    //}

    return (bool) m_fd;
}


void Manager::disconnectDevices() {
    if (!m_fd)
        return;

    foreach (Device *d, m_devices)
        delete d;

    // Close and delete lightstone device
    lightstone_delete(m_fd);

    m_fd = NULL;
}


bool Manager::isConnected() {
    return (bool) m_fd;
}


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
