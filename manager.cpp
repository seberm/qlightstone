#include <QDebug>
#include <QThread>
#include "manager.h"

/*
    lightstone* test = lightstone_create();
        lightstone_info r;
        int ret, count, i, j;

        count = lightstone_get_count(test);

        if(!count)
        {
            printf("No lightstones connected!\n");
            return 1;
        }
        printf("Found %d Lightstones\n", count);
        for(i = 0; i < count; ++i)
        {
            ret = lightstone_open(test, i);
            if(ret < 0)
            {
                printf("Cannot open lightstone!\n");
                return 1;
            }
            printf("Opening lightstone %d\n", i + 1);
            printf("Getting first 10 HRV/SCL pairs:\n");
            for(j = 0; j < 10; ++j)
            {
                r = lightstone_get_info(test);
                if(r.hrv < 0)
                {
                    printf("Error reading lightstone, shutting down!\n");
                    break;
                }
                printf ("%f %f\n", r.hrv, r.scl);
            }
            printf("Getting serial string ...\n");
            printf("Serial: %s\n", lightstone_get_serial(test));

            printf("Getting version string ...\n");
            printf("Version: %s\n", lightstone_get_version(test));

            printf("Closed lightstone %d\n", i + 1);
        }
        lightstone_delete(test);


 */



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

        m_devices.append(d);
        qDebug() << tr("] Device %1 successfully opened").arg(d->getID());
        emit newDeviceFound(d->getID());
    }


    //thread test
    /*
    foreach (Device *d, m_devices) {
        QThread *workerThread = new QThread(this);

        connect(workerThread, SIGNAL(started()), d, SLOT(lookUpSerial()));
        connect(d, SIGNAL(serialFound(QString)), workerThread, SLOT(quit()));
        //connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
        d->moveToThread(workerThread);

        // Starts an event loop, and emits workerThread->started()
        workerThread->start();
    }
    */
}


Manager::~Manager() {
    foreach (Device *d, m_devices)
        delete d;

    // Close and delete lightstone device
    lightstone_delete(m_fd);
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


Device* Manager::getDeviceByID(int id) {
    return m_devices.at(id);
}


void Manager::deviceSerialFound(const QString &serial) {
    Device *d = qobject_cast<Device*>(sender());
    qDebug() << tr("] Device %1: Serial: %2").arg(d->getID()).arg(serial);
}

