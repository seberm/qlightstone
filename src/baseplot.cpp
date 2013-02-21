#include "baseplot.h"

BasePlot::BasePlot(QWidget *parent) :
    QwtPlot(parent)
{
    setAxisScale(0, 0, 5);
}
