#ifdef _MSC_VER
#pragma once
#endif

#ifndef __HJ125T_16APRESENTER_H__
#define __HJ125T_16APRESENTER_H__

#include <QtConcurrent/QtConcurrent>
#include "MikuniPresenter.h"

class HJ125T_16APresenter : public MikuniPresenter
{
  Q_OBJECT
protected:
  virtual CommunicationState readAllInfoNow();
public:
  HJ125T_16APresenter(QObject *parent = 0);
protected slots:
  void realPreparePage();
};


#endif // __HJ125T_16APRESENTER_H__
