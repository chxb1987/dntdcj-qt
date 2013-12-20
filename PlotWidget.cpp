#include "PlotWidget.h"
#include <sstream>
#include <iomanip>
#include <qwt_series_data.h>
#include <qwt_scale_map.h>
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>
#include <qwt_math.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_legenditem.h>
#include <qwt_legend.h>
#include <qwt_scale_widget.h>

using namespace std;

PlotWidget::PlotWidget(QWidget *parent)
  : QWidget(parent)
  , _mainLayout(new QVBoxLayout(this))
  , _plot(new QwtPlot(this))
  , _canvas(new QwtPlotCanvas())
  , _curve(new PlotCurve(""))
  , _dataContext(nullptr)
  , _minValue(0.0)
  , _maxValue(0.0)
  , _dataCount(0)
  , _timerId(-1)
  , _ld()
{
  setLayout(_mainLayout);
  _mainLayout->addWidget(_plot);

  _plot->setAutoFillBackground(true);
  _plot->setPalette(QPalette(QColor(165, 193, 228)));
  _plot->setAutoReplot(false);

  // canvas
  _canvas->setLineWidth(1);
  _canvas->setFrameStyle(QFrame::Box | QFrame::Plain);

  QPalette canvasPalette(Qt::white);
  canvasPalette.setColor(QPalette::Foreground, QColor(133, 190, 232));
  _canvas->setPalette(canvasPalette);

  _plot->setCanvas(_canvas);
  _plot->plotLayout()->setAlignCanvasToScales(true);

  _curve->attach(_plot);
  _curve->setVisible(true);
  _curve->setRenderHint(QwtPlotItem::RenderAntialiased);
  _curve->setLegendAttribute(QwtPlotCurve::LegendShowLine, true);
  _curve->setPen(Qt::red);

  _mY = new QwtPlotMarker();
  _mY->setLabel(QString("y = 0"));
  _mY->setLabelAlignment(Qt::AlignRight | Qt::AlignTop);
  _mY->setLineStyle(QwtPlotMarker::HLine);
  _mY->setYValue(0.0);
  _mY->attach(_plot);
}

PlotWidget::~PlotWidget()
{
  if (_timerId != -1)
    killTimer(_timerId);
  delete _mY;
  delete _curve;
  delete _canvas;
  delete _plot;
  delete _mainLayout;
}

void PlotWidget::timerEvent(QTimerEvent *e)
{
  Q_UNUSED(e);
  for (int i = _dataCount; i > 0; --i) {
    if (i < HISTORY)
      _data[i] = _data[i - 1];
  }

  _data[0] = _ld.value().toDouble();

  if ((_minValue > _data[0]) || (_maxValue < _data[0])) {
    if (_minValue > _data[0]) _minValue = _data[0];
    if (_maxValue < _data[0]) _maxValue = _data[0];
    _plot->setAxisScale(QwtPlot::yLeft, _minValue, _maxValue);
  }

  if (_dataCount < HISTORY)
    _dataCount++;

  for (int i = 0; i < HISTORY; ++i)
    _timeData[i] += TimerInterval;

  _plot->setAxisScale(QwtPlot::xBottom, _timeData[HISTORY - 1], _timeData[0]);

  _curve->setRawSamples(_timeData, _data, _dataCount);
  _plot->replot();
}

void PlotWidget::setDataContext(ECUPresenter *dataContext)
{
  _dataContext = dataContext;
}

void PlotWidget::resetData()
{
  killTimer(_timerId);
  _dataCount = 0;
  for (int i = 0; i < HISTORY; ++i)
    _timeData[HISTORY - 1 - i] = i * TimerInterval;
  _plot->setAxisTitle(QwtPlot::xBottom, QString(""));
  _plot->setAxisScaleDraw(QwtPlot::xBottom, new PlotTimeScaleDraw(QTime::currentTime()));
  _plot->setAxisScale(QwtPlot::xBottom, 0, HISTORY);
  _plot->setAxisLabelRotation(QwtPlot::xBottom, -50.0);
  _plot->setAxisLabelAlignment(QwtPlot::xBottom, Qt::AlignLeft | Qt::AlignBottom);
  _plot->setAxisTitle(QwtPlot::yLeft, QString(""));

  // In situations, when there is a label at the most right position of the
  // scale, additional space is needed to display the overlapping part
  // of the label would be taken by reducing the width of scale and canvas.
  // To avoid this "jumping canvas" effect, we add a permanent margin.
  // We don't need to do the same for the left border, because there
  // is enough space for the overlapping label below the left scale.
  QwtScaleWidget *scaleWidget = _plot->axisWidget(QwtPlot::xBottom);
  const int fmh = QFontMetrics(scaleWidget->font()).height();
  scaleWidget->setMinBorderDist(0, fmh);
  _timerId = -1;
}

void PlotWidget::currentLiveDataChange(const QModelIndex &index)
{
  // If the timer is running, we do not restart it when click the same
  // live data item.
  auto lds = _dataContext->getLiveData();
  if (_timerId != -1) {
    if (lds[index.row()] == _ld) return;
  }
  resetData();

  _ld = lds[index.row()];
  _plot->setAxisTitle(QwtPlot::xBottom, _ld.content());
  _plot->setAxisTitle(QwtPlot::yLeft, _ld.unit());

  _minValue = _ld.minValue().toDouble();
  _maxValue = _ld.maxValue().toDouble();

  _plot->setAxisScale(QwtPlot::yLeft, _minValue, _maxValue);

  _timerId = startTimer(TimerInterval);
}
