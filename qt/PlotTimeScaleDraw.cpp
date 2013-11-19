#include "plottimescaledraw.h"

PlotTimeScaleDraw::PlotTimeScaleDraw(const QTime &base)
  : _base(base)
{
}

QwtText PlotTimeScaleDraw::label(double v) const
{
  QTime upTime = _base.addMSecs(static_cast<int>(v));
  return upTime.toString();
}
