#ifdef _MSC_VER
#pragma once
#endif

#ifndef __LIVEDATA_WIDGET_H__
#define __LIVEDATA_WIDGET_H__

#include <QWidget>
#include "ui_LiveDataWidget.h"
#include "ECUPresenter.h"
#include "LiveDataDelegate.h"
#include "LiveDataModel.h"

class LiveDataWidget : public QWidget
{
  Q_OBJECT
private:
  Ui::LiveDataWidget _ui;
  LiveDataModel _model;
  LiveDataDelegate _delegate;
  ECUPresenter *_dataContext;
protected:
  void changeEvent(QEvent *event);
public:
  explicit LiveDataWidget(QWidget *parent = 0);
  void setDataContext(ECUPresenter *dataContext);
public slots:
  void setValue(int index, const QString &value);
  void updateData();
  void clear();
signals:
  void itemClicked(const QModelIndex &index);
};

#endif // __LIVEDATA_WIDGET_H__
