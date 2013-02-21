#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>


#ifndef BASEPLOT_H
#define BASEPLOT_H

class BasePlot : public QwtPlot
{
    Q_OBJECT
public:
    explicit BasePlot(QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // BASEPLOT_H
