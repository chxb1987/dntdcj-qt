#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MIKUNI_WIDGET_H__
#define __MIKUNI_WIDGET_H__

#include <QWidget>

namespace Ui
{
class MikuniWidget;
}

class MikuniPresenter;
class MikuniWidget : public QWidget
{
  Q_OBJECT
private:
  Ui::MikuniWidget *_ui;
  MikuniPresenter *_dataContext;
public:
  explicit MikuniWidget(QWidget *parent = 0);
  void setDataContext(MikuniPresenter *dataContext);
};

#endif // __MIKUNI_WIDGET_H__
