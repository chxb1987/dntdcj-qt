#ifdef _MSC_VER
#pragma once
#endif

#ifndef __PLOT_TIME_SCALE_DRAW_H__
#define __PLOT_TIME_SCALE_DRAW_H__

#include <QTime>
#include <qwt_scale_draw.h>

class PlotTimeScaleDraw : public QwtScaleDraw
{
public:
public:
  PlotTimeScaleDraw(const QTime &base);
  virtual QwtText label(double v) const;
private:
  QTime _base;
};

#endif // __PLOT_TIME_SCALE_DRAW_H__
