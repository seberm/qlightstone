#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QPair>
#include <lightstone/lightstone.h>

class Device : public QObject
{
    Q_OBJECT
public:
    explicit Device(lightstone *fd, int id, QObject *parent = 0);

    const QString getSerial();
    QPair<float,float> getValues();
    int getID();

private:
    int m_id;
    lightstone *m_fd;

    QString m_serial;
    
signals:
    void serialFound(const QString &serial);
    
public slots:
    void lookUpSerial();

};

#endif // DEVICE_H
