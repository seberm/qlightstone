#include <QDebug>
#include "device.h"

const int TIMEOUT = 400; // [ms]
const int VALS_FOR_AVERAGE = 4;

Device::Device(lightstone *fd, int id, QObject *parent) :
    QThread(parent)
{
    m_fd = fd;
    m_id = id;

    m_avgHRV = -1;
    m_avgSCL = -1;

    m_timer = new QTimer(this);
    m_timer->setInterval(TIMEOUT);
    connect(m_timer, SIGNAL(timeout()),
            this, SLOT(readValues()));
}


Device::~Device() {

}


void Device::readValues() {
    lightstone_info info;
    float hrv = 0;
    float scl = 0;
    int count = 0;

    for (count = 0; count < VALS_FOR_AVERAGE; ++count) {
        info = lightstone_get_info(m_fd);
        hrv += info.hrv;
        scl += info.scl;
    }

    m_avgHRV = hrv / count;
    m_avgSCL = scl / count;

    emit valuesFound(m_avgHRV, m_avgSCL);
}


void Device::run() {
    m_timer->start();
}


/*
const QString Device::getSerial() {
    if (m_serial.isEmpty())
    //! \todo catch error here
        m_serial = lightstone_get_serial(m_fd);

    return m_serial;
}


QPair<float,float> Device::getValues() {
    lightstone_info info = lightstone_get_info(m_fd);

    QPair<float,float> vals;

    vals.first = info.hrv;
    vals.second = info.scl;
    return vals;
}


void Device::lookUpSerial() {
    emit serialFound(this->getSerial());
}


*/

int Device::getID() {
    return m_id;
}

