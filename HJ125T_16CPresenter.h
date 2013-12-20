#ifdef _MSC_VER
#pragma once
#endif

#ifndef __HJ125T_16CPRESENTER_H__
#define __HJ125T_16CPRESENTER_H__

#include "MikuniPresenter.h"

class HJ125T_16CPresenter : public MikuniPresenter
{
  Q_OBJECT
public:
  HJ125T_16CPresenter(QObject *parent = 0);
protected slots:
  void realPreparePage();
};

#endif // __HJ125T_16CPRESENTER_H__

