#include "MikuniPresenter.h"
#include <QtConcurrent/QtConcurrent>
#include <boost/algorithm/string.hpp>
#include "MikuniWidget.h"
#include "App.h"

MikuniPresenter::MikuniPresenter(RMikuniPowertrain::Model model, QObject *parent)
  : ECUPresenter(RMikuniPowertrainPtr(new RMikuniPowertrain(AppInst().commbox(), AppInst().db(), model)), parent)
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
  auto ecu = qSharedPointerCast<RMikuniPowertrain>(_ecu);
  auto version = ecu->getVersion();

  if (version.isEmpty()) {
    _info = ecu->getLastInfo();
    return CommunicationFail;
  }

  auto vec = version.split('\n');
  emit setHardwareVersion(vec[0]);
  emit setSoftwareVersion(vec[1]);

  auto tc = ecu->getTroubleCode();
  if (!tc->tryReadCurrent()) {
    return CommunicationFail;
  }

  auto tcs = tc->waitCurrentFinish();
  if (tcs.isNull()) {
    _info = tc->getMessage();
    return CommunicationFail;
  }

  emit updateTroubleCodeUI(tcs);

  auto& ld = ecu->getDataStream()->getLiveData();
  for (int i = 0; i < ld.size(); ++i) {
    ld[i].setIsShowed(true);
  }
  return Success;
}

void MikuniPresenter::tpsIdleSetting()
{
  emit showStatus(RSystemDB::queryText("Communicating"));

  _watcher.disconnect();
  connect(&_watcher, SIGNAL(finished()), this, SLOT(showSettingResult()));
  _future = QtConcurrent::run(this, &MikuniPresenter::tpsIdleSetting2);
  _watcher.setFuture(_future);
}

MikuniPresenter::CommunicationState MikuniPresenter::tpsIdleSetting2()
{
  stopDataStream();
  auto ecu = qSharedPointerCast<RMikuniPowertrain>(_ecu);
  auto ret = ecu->tpsIdleSetting();

  if (!ret) {
    _info = ecu->getLastInfo();
    _internalState = CommunicationFail;
  } else {
    _info = AppInst().db().getText("TPS Idle Setting Success", "Mikuni");
    _internalState = Success;
  }
  runDataStream();
  return _internalState;
}

void MikuniPresenter::longTermLearnValueZoneInitialization()
{
  emit showStatus(RSystemDB::queryText("Communicating"));

  _watcher.disconnect();
  connect(&_watcher, SIGNAL(finished()), this, SLOT(showSettingResult()));
  _future = QtConcurrent::run(this, &MikuniPresenter::longTermLearnValueZoneInitialization2);
  _watcher.setFuture(_future);
}

MikuniPresenter::CommunicationState MikuniPresenter::longTermLearnValueZoneInitialization2()
{
  stopDataStream();
  auto ecu = qSharedPointerCast<RMikuniPowertrain>(_ecu);
  auto ret = ecu->longTermLearnValueZoneInitialization();

  if (!ret) {
    _info = ecu->getLastInfo();
    _internalState = CommunicationFail;
  } else {
    _info = AppInst().db().getText("Long Term Learn Value Zone Initialization Success", "Mikuni");
    _internalState = Success;
  }
  runDataStream();
  return _internalState;
}

void MikuniPresenter::iscLearnValueInitialization()
{
  emit showStatus(RSystemDB::queryText("Communicating"));

  _watcher.disconnect();
  connect(&_watcher, SIGNAL(finished()), this, SLOT(showSettingResult()));
  _future = QtConcurrent::run(this, &MikuniPresenter::iscLearnValueInitialization2);
  _watcher.setFuture(_future);
}

MikuniPresenter::CommunicationState MikuniPresenter::iscLearnValueInitialization2()
{
  stopDataStream();
  auto ecu = qSharedPointerCast<RMikuniPowertrain>(_ecu);
  auto ret = ecu->iscLearnValueInitialization();

  if (!ret) {
    _info = ecu->getLastInfo();
    _internalState = CommunicationFail;
  } else {
    _info = AppInst().db().getText("ISC Learn Value Initialization Success", "Mikuni");
    _internalState = Success;
  }
  runDataStream();
  return _internalState;
}


