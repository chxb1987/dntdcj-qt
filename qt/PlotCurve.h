#ifdef _MSC_VER
#pragma once
#endif

#ifndef __PLOT_CURVE_H__
#define __PLOT_CURVE_H__

#include <qwt_plot_curve.h>
#include <QString>
#include <QColor>

class PlotCurve : public QwtPlotCurve
{
public:
  PlotCurve(const QString &title);
  void setColor(const QColor &color);
};

#endif // __PLOT_CURVE_H__
