#include "MainMenuPresenter.h"
#include <boost/bind.hpp>
#include "App.h"

MainMenuPresenter::MainMenuPresenter(HJ125T_16APresenter *hj125t_16a,
                                     HJ125T_16CPresenter *hj125t_16c,
                                     HJ125T_10Presenter *hj125t_10,
                                     GW250Presenter *gw250,
                                     QObject *parent)
  : MenuPresenter(parent)
  , _hj125t_16a(hj125t_16a)
  , _hj125t_16c(hj125t_16c)
  , _hj125t_10(hj125t_10)
  , _gw250(gw250)
{
  _hj125t_16a->setPreDataContext(this);
  _hj125t_16c->setPreDataContext(this);
  _hj125t_10->setPreDataContext(this);
  _gw250->setPreDataContext(this);
}

void MainMenuPresenter::preparePage()
{
  QString icon = ":/icons/Vehicle.png";
  QString icon_s = ":/icons/VehicleSelected.png";

  emit itemClr();

  QString name = AppInst().db().getText("HJ125T-16A", "DCJ");
  emit itemAdd(MenuItem(name, icon, icon_s));
  _funcSelected[name] = boost::bind(&HJ125T_16APresenter::show, _hj125t_16a);

  name = AppInst().db().getText("HJ125T-16C", "DCJ");
  _funcSelected[name] = boost::bind(&HJ125T_16CPresenter::show, _hj125t_16c);
  emit itemAdd(MenuItem(name, icon, icon_s));

  name = AppInst().db().getText("HJ125T-10", "DCJ");
  _funcSelected[name] = boost::bind(&HJ125T_10Presenter::show, _hj125t_10);
  emit itemAdd(MenuItem(name, icon, icon_s));

  name = AppInst().db().getText("GW250", "DCJ");
  _funcSelected[name] = boost::bind(&GW250Presenter::show, _gw250);
  emit itemAdd(MenuItem(name, icon, icon_s));
}

void MainMenuPresenter::quit()
{

}
