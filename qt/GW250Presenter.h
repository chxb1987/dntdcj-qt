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
  virtual CommunicationState readCurrentTroubleCodeData();
  virtual CommunicationState readHistoryTroubleCodeData();
  virtual CommunicationState clearTroubleCodeData();
  virtual void stopDataStreamData();
  virtual CommunicationState readDataStream();
public:
  GW250Presenter(QObject *parent = 0);
  ~GW250Presenter();
  void setGW250Widget(GW250Widget *widget);
  virtual void show();
  virtual DNTTroubleCodeVector getTroubleCode();
protected slots:
  virtual void realPreparePage();
};

#endif // __GW250_PRESENTER_H__
