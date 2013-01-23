#include <lightstone/lightstone.h>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

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


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*
    lightstone* dev = lightstone_create();

    if (!lightstone_get_count(dev)) {
        qWarning() << "No lightstone HW connected!";
        return;
    }

    int ret = lightstone_open(dev, 0);
    if (ret < 0) {
        qWarning() << "Cannot open lightstone!";
        return;
    }
    QString ser(lightstone_get_serial(dev));
    qDebug() << "ser:" << ser;
    ui->lblSerial->setText(ser);
    ui->lblVersion->setText(lightstone_get_version(dev));
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}
