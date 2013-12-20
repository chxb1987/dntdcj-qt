#ifdef _MSC_VER
#pragma once
#endif

#ifndef __HJ125T_10PRESENTER_H__
#define __HJ125T_10PRESENTER_H__

#include "MikuniPresenter.h"

class HJ125T_10Presenter : public MikuniPresenter
{
  Q_OBJECT
public:
  HJ125T_10Presenter(QObject *parent = 0);
protected slots:
  void realPreparePage();
};

#endif // __HJ125T_10PRESENTER_H__
