#include "GW250Presenter.h"
#include <QtConcurrent/QtConcurrent>
#include <boost/bind.hpp>
#include <DNTDensoPowertrain.h>
#include "App.h"
#include "GW250Widget.h"

GW250Presenter::GW250Presenter(QObject *parent)
  : ECUPresenter(new DNTDensoPowertrain(AppInst()->commbox(), AppInst()->db(), RDensoModel::DCJ_GW250), parent)
{

}

GW250Presenter::~GW250Presenter()
{
  stopDataStream();
}

void GW250Presenter::setGW250Widget(GW250Widget *widget)
{
  ECUPresenter::setWidget((QWidget*)widget);
}

void GW250Presenter::show()
{
  GW250Widget *widget = (GW250Widget*)_widget;
  widget->setDataContext(this);
  ECUPresenter::show();
}

void GW250Presenter::realPreparePage()
{
  auto result = _watcher.result();

  if (result == CommunicationFail) {
    quit();
    return;
  }

  QString name = DNTSystemDB::queryText("Read Current Trouble Code");
  _funcSelected[name] = boost::bind(&GW250Presenter::readCurrentTroubleCode, this);
  emit itemAdd(MenuItem(name, READ_CURRENT_TROUBLE_CODE_ICON, READ_CURRENT_TROUBLE_CODE_ICON_S));

  name = DNTSystemDB::queryText("Read History Trouble Code");
  _funcSelected[name] = boost::bind(&GW250Presenter::readHistoryTroubleCode, this);
  emit itemAdd(MenuItem(name, READ_HISTORY_TROUBLE_CODE_ICON, READ_HISTORY_TROUBLE_CODE_ICON_S));

  name = DNTSystemDB::queryText("Clear Trouble Code");
  _funcSelected[name] = boost::bind(&GW250Presenter::clearTroubleCode, this);
  emit itemAdd(MenuItem(name, CLEAR_TROUBLE_CODE_ICON, CLEAR_TROUBLE_CODE_ICON_S));
}

GW250Presenter::CommunicationState GW250Presenter::readAllInfoNow()
{
  DNTDensoPowertrain *ecu = (DNTDensoPowertrain*)_ecu;

  if (!ecu->getTroubleCode().readCurrent()) {
    _info = ecu->getLastInfo();
    return CommunicationFail;
  }

  emit updateTroubleCodeUI();
  return Success;
}

GW250Presenter::CommunicationState GW250Presenter::readCurrentTroubleCodeData()
{
  bool ret = _ecu->getTroubleCode().readCurrent();

  if (!ret) {
    _info = _ecu->getLastInfo();
    _internalState = CommunicationFail;
  } else {
    _internalState = Success;
  }

  return _internalState;
}

GW250Presenter::CommunicationState GW250Presenter::readHistoryTroubleCodeData()
{
  bool ret = _ecu->getTroubleCode().readHistory();

  if (!ret) {
    _info = _ecu->getLastInfo();
    _internalState = CommunicationFail;
  } else {
    _internalState = Success;
  }

  return _internalState;
}

GW250Presenter::CommunicationState GW250Presenter::clearTroubleCodeData()
{
  bool ret = _ecu->getTroubleCode().clear();

  if (!ret) {
    _info = _ecu->getLastInfo();
    _internalState = CommunicationFail;
  } else {
    _internalState = Success;
  }

  return _internalState;
}

void GW250Presenter::stopDataStreamData()
{
  auto ds = _ecu->getDataStream();
  ds.stopCalc();
  ds.stopRead();
}

GW250Presenter::CommunicationState GW250Presenter::readDataStream()
{
  auto ds = _ecu->getDataStream();
  QtConcurrent::run(&ds, &DNTDataStreamFunction::readData);
  if (!ds.calcData())
    return CommunicationFail;
  return Success;
}

DNTTroubleCodeVector GW250Presenter::getTroubleCode()
{
  auto tc = _ecu->getTroubleCode();
  return tc.getTroubleCodes();
}


