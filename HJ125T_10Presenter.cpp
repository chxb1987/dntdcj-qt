#include "HJ125T_10Presenter.h"
#include <boost/bind.hpp>
#include <QtDebug>
#include <DNTSystemDB.h>
#include "App.h"

HJ125T_10Presenter::HJ125T_10Presenter(QObject *parent)
  : MikuniPresenter(RMikuniPowertrain::DCJ_10, parent)
{

}

void HJ125T_10Presenter::realPreparePage()
{
  auto result = _watcher.result();

  if (result == CommunicationFail) {
    quit();
    return;
  }

  QString name = RSystemDB::queryText("Read Current Trouble Code");
  _funcSelected[name] = boost::bind(&HJ125T_10Presenter::readCurrentTroubleCode, this);
  emit itemAdd(MenuItem(name, READ_CURRENT_TROUBLE_CODE_ICON, READ_CURRENT_TROUBLE_CODE_ICON_S));

  name = RSystemDB::queryText("Read History Trouble Code");
  _funcSelected[name] = boost::bind(&HJ125T_10Presenter::readHistoryTroubleCode, this);
  emit itemAdd(MenuItem(name, READ_HISTORY_TROUBLE_CODE_ICON, READ_HISTORY_TROUBLE_CODE_ICON_S));

  name = RSystemDB::queryText("Clear Trouble Code");
  _funcSelected[name] = boost::bind(&HJ125T_10Presenter::clearTroubleCode, this);
  emit itemAdd(MenuItem(name, CLEAR_TROUBLE_CODE_ICON, CLEAR_TROUBLE_CODE_ICON_S));

  name = AppInst().db().getText("TPS Idle Adjustment", "Mikuni");
  _funcSelected[name] = boost::bind(&HJ125T_10Presenter::tpsIdleSetting, this);
  emit itemAdd(MenuItem(name, TPS_IDLE_SETTING_ICON, TPS_IDLE_SETTING_ICON_S));

  name = AppInst().db().getText("Long Term Learn Value Zone Initialization", "Mikuni");
  _funcSelected[name] = boost::bind(&HJ125T_10Presenter::longTermLearnValueZoneInitialization, this);
  emit itemAdd(MenuItem(name, LONG_TERM_LEARNING_VALUE_INITIALIZATION_ICON, LONG_TERM_LEARNING_VALUE_INITIALIZATION_ICON_S));

  name = AppInst().db().getText("ISC Learn Value Initialize", "Mikuni");
  _funcSelected[name] = boost::bind(&HJ125T_10Presenter::iscLearnValueInitialization, this);
  emit itemAdd(MenuItem(name, ISC_LEARN_VALUE_INITIALIZATION_ICON, ISC_LEARN_VALUE_INITIALIZATION_ICON_S));

  emit hideStatus();
}
