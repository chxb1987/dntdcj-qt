#include "HJ125T_16CPresenter.h"
#include <boost/bind.hpp>
#include <DNTSystemDB.h>
#include "App.h"

HJ125T_16CPresenter::HJ125T_16CPresenter(QObject *parent)
  : MikuniPresenter(RMikuniModel::DCJ_16C, parent)
{

}

void HJ125T_16CPresenter::realPreparePage()
{
  auto result = _watcher.result();

  if (result == CommunicationFail) {
    quit();
    return;
  }

  QString name = DNTSystemDB::queryText("Read Current Trouble Code");
  _funcSelected[name] = boost::bind(&HJ125T_16CPresenter::readCurrentTroubleCode, this);
  emit itemAdd(MenuItem(name, READ_CURRENT_TROUBLE_CODE_ICON, READ_CURRENT_TROUBLE_CODE_ICON_S));

  name = DNTSystemDB::queryText("Read History Trouble Code");
  _funcSelected[name] = boost::bind(&HJ125T_16CPresenter::readHistoryTroubleCode, this);
  emit itemAdd(MenuItem(name, READ_HISTORY_TROUBLE_CODE_ICON, READ_HISTORY_TROUBLE_CODE_ICON_S));

  name = DNTSystemDB::queryText("Clear Trouble Code");
  _funcSelected[name] = boost::bind(&HJ125T_16CPresenter::clearTroubleCode, this);
  emit itemAdd(MenuItem(name, CLEAR_TROUBLE_CODE_ICON, CLEAR_TROUBLE_CODE_ICON_S));

  name = AppInst()->db().getText("TPS Idle Adjustment", "Mikuni");
  _funcSelected[name] = boost::bind(&HJ125T_16CPresenter::tpsIdleSetting, this);
  emit itemAdd(MenuItem(name, TPS_IDLE_SETTING_ICON, TPS_IDLE_SETTING_ICON_S));

  name = AppInst()->db().getText("Long Term Learn Value Zone Initialization", "Mikuni");
  _funcSelected[name] = boost::bind(&HJ125T_16CPresenter::longTermLearnValueZoneInitialization, this);
  emit itemAdd(MenuItem(name, LONG_TERM_LEARNING_VALUE_INITIALIZATION_ICON, LONG_TERM_LEARNING_VALUE_INITIALIZATION_ICON_S));

  name = AppInst()->db().getText("ISC Learn Value Initialize", "Mikuni");
  _funcSelected[name] = boost::bind(&HJ125T_16CPresenter::iscLearnValueInitialization, this);
  emit itemAdd(MenuItem(name, ISC_LEARN_VALUE_INITIALIZATION_ICON, ISC_LEARN_VALUE_INITIALIZATION_ICON_S));

  emit hideStatus();
}
