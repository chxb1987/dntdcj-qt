#ifdef _MSC_VER
#pragma once
#endif


#ifndef __PLOT_WIDGET_H__
#define __PLOT_WIDGET_H__

#include <QWidget>
#include <QVBoxLayout>
#include <QColor>
#include <QPainter>
#include <QModelIndex>
#include <qwt_plot.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_marker.h>
#include <DNTLiveDataList.h>
#include "PlotBackground.h"
#include "PlotCurve.h"
#include "PlotTimeScaleDraw.h"
#include "ECUPresenter.h"

class PlotWidget : public QWidget
{
  Q_OBJECT
public:
  static const int TimerInterval = 25;
  static const int HISTORY = 60 * (1000 / TimerInterval);
private:
  QVBoxLayout *_mainLayout;
  QwtPlot *_plot;
  QwtPlotCanvas* _canvas;
  PlotCurve *_curve;
  QwtPlotMarker *_mY;
  ECUPresenter *_dataContext;
  double _data[HISTORY];
  double _timeData[HISTORY];
  double _minValue;
  double _maxValue;
  int _dataCount;
  int _timerId;
  DNTLiveDataItem _ld;
private:
protected:
  void timerEvent(QTimerEvent *e);
public:
  explicit PlotWidget(QWidget *parent = 0);
  ~PlotWidget();
  void setDataContext(ECUPresenter *dataContext);
public slots:
  void resetData();
  void currentLiveDataChange(const QModelIndex &index);
};

#endif // __PLOT_WIDGET_H__
