#ifdef _MSC_VER
#pragma once
#endif

#ifndef __GW250_WIDGET_H__
#define __GW250_WIDGET_H__

#include <QWidget>
#include "ECUPresenter.h"

namespace Ui
{
class GW250Widget;
}

class GW250Widget : public QWidget
{
  Q_OBJECT
public:
  explicit GW250Widget(QWidget *parent = 0);
  ~GW250Widget();
  void setDataContext(ECUPresenter *dataContext);
private:
  Ui::GW250Widget *_ui;
  ECUPresenter *_dataContext;
};

#endif // __GW250_WIDGET_H__
