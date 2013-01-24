#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QThread>
#include <QList>

#include <lightstone/lightstone.h>

#include "device.h"
class Device;


class Manager : public QThread
{
    Q_OBJECT
public:
    explicit Manager(QObject *parent = 0);
    ~Manager();

    Device* getDeviceByID(int id);

protected:
    void run();
    
private:
    QList<Device*> m_devices;
    lightstone *m_fd;

    const QString getLightstoneErr(int err);

signals:
    void newDeviceFound(int id);
    
public slots:
private slots:
    void deviceSerialFound(const QString &serial);

    
};

#endif // MANAGER_H
