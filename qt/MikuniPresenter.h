#ifdef _MSC_VER
#pragma once
#endif


#ifndef __MIKUNI_PRESENTER_H__
#define __MIKUNI_PRESENTER_H__

#include <DNTMikuniPowertrain.h>
#include "ECUPresenter.h"
#include "MenuItem.h"

class MikuniWidget;
class MikuniPresenter : public ECUPresenter
{
  Q_OBJECT
protected:
  virtual CommunicationState readAllInfoNow();
  virtual CommunicationState readCurrentTroubleCodeData();
  virtual CommunicationState readHistoryTroubleCodeData();
  virtual CommunicationState clearTroubleCodeData();
  void tpsIdleSetting();
  CommunicationState tpsIdleSetting2();
  void longTermLearnValueZoneInitialization();
  CommunicationState longTermLearnValueZoneInitialization2();
  void iscLearnValueInitialization();
  CommunicationState iscLearnValueInitialization2();
  virtual CommunicationState readDataStream();
  virtual void stopDataStreamData();
public:
  MikuniPresenter(RMikuniModel model, QObject *parent = 0);
  ~MikuniPresenter();
  void setMikuniWidget(MikuniWidget *widget);
  virtual void show();
  virtual DNTTroubleCodeVector getTroubleCode();
signals:
  void setSoftwareVersion(const QString &text);
  void setHardwareVersion(const QString &text);
};

#endif // __MIKUNI_PRESENTER_H__
