#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <lightstone/lightstone.h>

class Device : public QThread
{
    Q_OBJECT
public:
    explicit Device(lightstone *fd, int id, QObject *parent = 0);
    ~Device();
    int getID();

protected:
    void run();

private:
    int m_id;
    lightstone *m_fd;

    float m_avgHRV;
    float m_avgSCL;

    QString m_serial;
    QString m_version;

    QTimer *m_timer;
    
signals:
    void serialFound(const QString &serial);
    void versionFound(const QString &version);
    void valuesFound(float hrv, float scl);

private slots:
    void readValues();
};

#endif // DEVICE_H
