#include "MikuniPresenter.h"
#include <QtConcurrent/QtConcurrent>
#include <boost/algorithm/string.hpp>
#include "MikuniWidget.h"
#include "App.h"

MikuniPresenter::MikuniPresenter(RMikuniModel model, QObject *parent)
  : ECUPresenter(new DNTMikuniPowertrain(AppInst()->commbox()->getNative(), AppInst()->db()->getNative(), model), parent)
{

}

MikuniPresenter::~MikuniPresenter()
{
  stopDataStream();
}

void MikuniPresenter::setMikuniWidget(MikuniWidget *widget)
{
  ECUPresenter::setWidget((QWidget*)widget);
}

void MikuniPresenter::show()
{
  MikuniWidget *widget = (MikuniWidget*)_widget;
  widget->setDataContext(this);
  ECUPresenter::show();
}

MikuniPresenter::CommunicationState MikuniPresenter::readAllInfoNow()
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
  return Success;
}

MikuniPresenter::CommunicationState MikuniPresenter::readCurrentTroubleCodeData()
{
  auto tc = _ecu->getTroubleCode();
  auto ret = tc.readCurrent();

  if (!ret) {
    _info = _ecu->getLastInfo();
    _internalState = CommunicationFail;
  } else {
    _internalState = Success;
  }

  return _internalState;
}

MikuniPresenter::CommunicationState MikuniPresenter::readHistoryTroubleCodeData()
{
  auto tc =_ecu->getTroubleCode();
  auto ret = tc.readHistory();

  if (!ret) {
    _info = _ecu->getLastInfo();
    _internalState = CommunicationFail;
  } else {
    _internalState = Success;
  }

  return _internalState;
}

MikuniPresenter::CommunicationState MikuniPresenter::clearTroubleCodeData()
{
  auto tc = _ecu->getTroubleCode();
  auto ret = tc.clear();

  if (!ret) {
    _info = _ecu->getLastInfo();
    _internalState = CommunicationFail;
  } else {
    _info = DNTSystemDB::queryText("Clear Trouble Code Finish");
    _internalState = Success;
  }

  return _internalState;
}

void MikuniPresenter::tpsIdleSetting()
{
  emit showStatus(DNTSystemDB::queryText("Communicating"));

  _watcher.disconnect();
  connect(&_watcher, SIGNAL(finished()), this, SLOT(showSettingResult()));
  _future = QtConcurrent::run(this, &MikuniPresenter::tpsIdleSetting2);
  _watcher.setFuture(_future);
}

MikuniPresenter::CommunicationState MikuniPresenter::tpsIdleSetting2()
{
  stopDataStream();
  DNTMikuniPowertrain *ecu = (DNTMikuniPowertrain*)_ecu;
  auto ret = ecu->tpsIdleSetting();

  if (!ret) {
    _info = ecu->getLastInfo();
    _internalState = CommunicationFail;
  } else {
    _info = AppInst()->db()->getText("TPS Idle Setting Success", "Mikuni");
    _internalState = Success;
  }
  runDataStream();
  return _internalState;
}

void MikuniPresenter::longTermLearnValueZoneInitialization()
{
  emit showStatus(DNTSystemDB::queryText("Communicating"));

  _watcher.disconnect();
  connect(&_watcher, SIGNAL(finished()), this, SLOT(showSettingResult()));
  _future = QtConcurrent::run(this, &MikuniPresenter::longTermLearnValueZoneInitialization2);
  _watcher.setFuture(_future);
}

MikuniPresenter::CommunicationState MikuniPresenter::longTermLearnValueZoneInitialization2()
{
  stopDataStream();
  DNTMikuniPowertrain *ecu = (DNTMikuniPowertrain*)_ecu;
  auto ret = ecu->longTermLearnValueZoneInitialization();

  if (!ret) {
    _info = ecu->getLastInfo();
    _internalState = CommunicationFail;
  } else {
    _info = AppInst()->db()->getText("Long Term Learn Value Zone Initialization Success", "Mikuni");
    _internalState = Success;
  }
  runDataStream();
  return _internalState;
}

void MikuniPresenter::iscLearnValueInitialization()
{
  emit showStatus(DNTSystemDB::queryText("Communicating"));

  _watcher.disconnect();
  connect(&_watcher, SIGNAL(finished()), this, SLOT(showSettingResult()));
  _future = QtConcurrent::run(this, &MikuniPresenter::iscLearnValueInitialization2);
  _watcher.setFuture(_future);
}

MikuniPresenter::CommunicationState MikuniPresenter::iscLearnValueInitialization2()
{
  stopDataStream();
  DNTMikuniPowertrain *ecu = (DNTMikuniPowertrain*)_ecu;
  auto ret = ecu->iscLearnValueInitialization();

  if (!ret) {
    _info = ecu->getLastInfo();
    _internalState = CommunicationFail;
  } else {
    _info = AppInst()->db()->getText("ISC Learn Value Initialization Success", "Mikuni");
    _internalState = Success;
  }
  runDataStream();
  return _internalState;
}

void MikuniPresenter::stopDataStreamData()
{
  auto ds = _ecu->getDataStream();
  ds.stopRead();
  ds.stopCalc();
}

MikuniPresenter::CommunicationState MikuniPresenter::readDataStream()
{
  auto ds = _ecu->getDataStream();
  QtConcurrent::run(&ds, &DNTDataStreamFunction::readData);
  if (!ds.calcData())
    return CommunicationFail;
  return Success;
}

DNTLiveDataList MikuniPresenter::getLiveData()
{
  auto ds = _ecu->getDataStream();
  return ds.getLiveData();
}

DNTTroubleCodeVector MikuniPresenter::getTroubleCode()
{
  auto tc = _ecu->getTroubleCode();
  return tc.getTroubleCodes();
}

