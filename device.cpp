#include "device.h"

Device::Device(lightstone *fd, int id, QObject *parent) :
    QObject(parent)
{
    m_fd = fd;
    m_id = id;
}


const QString Device::getSerial() {
    if (m_serial.isEmpty())
    //! \todo catch error here
        m_serial = lightstone_get_serial(m_fd);

    return m_serial;
}


QPair<float,float> Device::getValues() {
    lightstone_info info = lightstone_get_info(m_fd);

    QPair<float,float> vals;

    //Err!
    if (info.hrv < 0 || info.scl < 0)
        return vals;

    vals.first = info.hrv;
    vals.second = info.scl;
    return vals;
}


void Device::lookUpSerial() {
    emit serialFound(this->getSerial());
}


int Device::getID() {
    return m_id;
}
