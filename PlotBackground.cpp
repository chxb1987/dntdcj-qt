#include "plotbackground.h"

PlotBackground::PlotBackground()
{
  setZ(0.0);
}

int PlotBackground::rtti() const
{
  return QwtPlotItem::Rtti_PlotUserItem;
}

void PlotBackground::draw(QPainter *painter,
                          const QwtScaleMap &xMap,
                          const QwtScaleMap &yMap,
                          const QRectF &canvasRect) const
{
  Q_UNUSED(xMap);
  QColor c(Qt::white);
  QRectF r = canvasRect;

  int i = yMap.sDist();
  int a = i / 10;

  while(i > 0) {
    r.setBottom(yMap.transform(i - a));
    r.setTop(yMap.transform(i));
    painter->fillRect(r, c);

    c = c.dark(110);
    i -= a;
  }
}

