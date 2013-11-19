#include "plotcurve.h"

PlotCurve::PlotCurve(const QString &title)
  : QwtPlotCurve(title)
{
  setRenderHint(QwtPlotItem::RenderAntialiased);
}

void PlotCurve::setColor(const QColor &color)
{
  QColor c = color;
  c.setAlpha(150);

  setPen(c);
  setBrush(c);
}

