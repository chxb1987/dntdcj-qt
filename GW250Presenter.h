#ifdef _MSC_VER
#pragma once
#endif

#ifndef __GW250_PRESENTER_H__
#define __GW250_PRESENTER_H__

#include "ECUPresenter.h"

class GW250Widget;
class GW250Presenter : public ECUPresenter
{
  Q_OBJECT
protected:
  virtual CommunicationState readAllInfoNow();
public:
  GW250Presenter(QObject *parent = 0);
  ~GW250Presenter();
  void setGW250Widget(GW250Widget *widget);
  virtual void show();
protected slots:
  virtual void realPreparePage();
};

#endif // __GW250_PRESENTER_H__
