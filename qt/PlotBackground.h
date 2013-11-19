#ifdef _MSC_VER
#pragma once
#endif

#ifndef __PLOT_BACKGROUND_H__
#define __PLOT_BACKGROUND_H__

#include <QPainter>
#include <QRectF>
#include <qwt_plot_item.h>
#include <qwt_scale_map.h>

class PlotBackground : public QwtPlotItem
{
public:
  PlotBackground();
  virtual int rtti() const;
  virtual void draw(QPainter *painter,
                    const QwtScaleMap &xMap,
                    const QwtScaleMap &yMap,
                    const QRectF &canvasRect) const;
};

#endif // __PLOT_BACKGROUND_H__
