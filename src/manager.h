#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QList>

#include <lightstone/lightstone.h>

#include "device.h"
class Device;


class Manager : public QObject
{
    Q_OBJECT
public:
    explicit Manager(QObject *parent = 0);
    ~Manager();

    Device* getDeviceByID(int deviceID);

private:
    QList<Device*> m_devices;
    lightstone *m_fd;

    const QString getLightstoneErr(int err);

signals:
    void newDeviceFound(int deviceID);
    void newValues(int deviceID, float hrv, float scl);
    
public slots:
private slots:
    void deviceSerialFound(const QString &serial);
    void deviceValuesFound(float hrv, float scl);
    
};

#endif // MANAGER_H
