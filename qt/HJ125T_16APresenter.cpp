#include "HJ125T_16APresenter.h"
#include <QMessageBox>
#include <boost/bind.hpp>
#include <DNTSystemDB.h>
#include "App.h"

HJ125T_16APresenter::HJ125T_16APresenter(QObject *parent)
  : MikuniPresenter(RMikuniModel::DCJ_16A, parent)
{

}

void HJ125T_16APresenter::realPreparePage()
{
  auto result = _watcher.result();

  if (result == CommunicationFail) {
    quit();
    return;
  }

  QString name = DNTSystemDB::queryText("Read Current Trouble Code");
  emit itemAdd(MenuItem(name, READ_CURRENT_TROUBLE_CODE_ICON, READ_CURRENT_TROUBLE_CODE_ICON_S));
  _funcSelected[name] = boost::bind(&HJ125T_16APresenter::readCurrentTroubleCode, this);


  name = DNTSystemDB::queryText("Read History Trouble Code");
  _funcSelected[name] = boost::bind(&HJ125T_16APresenter::readHistoryTroubleCode, this);
  emit itemAdd(MenuItem(name, READ_HISTORY_TROUBLE_CODE_ICON, READ_HISTORY_TROUBLE_CODE_ICON_S));

  name = DNTSystemDB::queryText("Clear Trouble Code");
  _funcSelected[name] = boost::bind(&HJ125T_16APresenter::clearTroubleCode, this);
  emit itemAdd(MenuItem(name, CLEAR_TROUBLE_CODE_ICON, CLEAR_TROUBLE_CODE_ICON_S));

  name = AppInst()->db().getText("TPS Idle Adjustment", "Mikuni");
  _funcSelected[name] = boost::bind(&HJ125T_16APresenter::tpsIdleSetting, this);
  emit itemAdd(MenuItem(name, TPS_IDLE_SETTING_ICON, TPS_IDLE_SETTING_ICON_S));

  if (result == Extension) {
    name = AppInst()->db().getText("Long Term Learn Value Zone Initialization", "Mikuni");
    _funcSelected[name] = boost::bind(&HJ125T_16APresenter::longTermLearnValueZoneInitialization, this);
    emit itemAdd(MenuItem(name, LONG_TERM_LEARNING_VALUE_INITIALIZATION_ICON, LONG_TERM_LEARNING_VALUE_INITIALIZATION_ICON_S));

    name = AppInst()->db().getText("ISC Learn Value Initialize", "Mikuni");
    _funcSelected[name] = boost::bind(&HJ125T_16APresenter::iscLearnValueInitialization, this);
    emit itemAdd(MenuItem(name, ISC_LEARN_VALUE_INITIALIZATION_ICON, ISC_LEARN_VALUE_INITIALIZATION_ICON_S));
  }

  emit hideStatus();
}

HJ125T_16APresenter::CommunicationState HJ125T_16APresenter::readAllInfoNow()
{
  DNTMikuniPowertrain *ecu = (DNTMikuniPowertrain*)_ecu;
  auto version = ecu->getVersion();

  if (version.isEmpty()) {
    _info = ecu->getLastInfo();
    return CommunicationFail;
  }

  auto vec = version.split('\n');
  emit setHardwareVersion(vec[0]);
  emit setSoftwareVersion(vec[1]);

  auto tc = ecu->getTroubleCode();
  if (!tc.readCurrent()) {
    _info = ecu->getLastInfo();
    return CommunicationFail;
  }

  emit updateTroubleCodeUI();
  if (vec[0] == QString("ECU200-A001D") ||
      vec[0] == QString("ECU200-A002") ||
      vec[0] == QString("ECU200-A003"))
    return Extension;
  return Standard;
}
