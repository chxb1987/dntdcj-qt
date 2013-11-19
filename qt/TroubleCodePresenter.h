#ifdef _MSC_VER
#pragma once
#endif

#ifndef __TROUBLECODE_PRESENTER_H__
#define __TROUBLECODE_PRESENTER_H__

#include <QObject>
#include "TroubleCodeWidget.h"

class TroubleCodePresenter : public QObject
{
  Q_OBJECT
private:
  TroubleCodeWidget *_widget;
public:
  explicit TroubleCodePresenter(QObject *parent = 0);
  void setWidget(TroubleCodeWidget *widget);
  void show();
signals:
  void sendShow(QWidget *widget);
};

#endif // __TROUBLECODE_PRESENTER_H__
