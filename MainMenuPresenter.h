#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MAIN_MENU_PRESENTER_H__
#define __MAIN_MENU_PRESENTER_H__

#include "MenuPresenter.h"
#include "HJ125T_10Presenter.h"
#include "HJ125T_16APresenter.h"
#include "HJ125T_16CPresenter.h"
#include "GW250Presenter.h"

class MainMenuPresenter : public MenuPresenter
{
  Q_OBJECT
private:
  HJ125T_16APresenter *_hj125t_16a;
  HJ125T_16CPresenter *_hj125t_16c;
  HJ125T_10Presenter *_hj125t_10;
  GW250Presenter *_gw250;
public:
  explicit MainMenuPresenter(HJ125T_16APresenter *hj125t_16a,
                             HJ125T_16CPresenter *hj125t_16c,
                             HJ125T_10Presenter *hj125t_10,
                             GW250Presenter *gw250,
                             QObject *parent = 0);
  void preparePage();
  void quit();
};

#endif // __MAIN_MENU_PRESENTER_H__
