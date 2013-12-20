#include "GW250Presenter.h"
#include <QtConcurrent/QtConcurrent>
#include <boost/bind.hpp>
#include <DNTDensoPowertrain.h>
#include "App.h"
#include "GW250Widget.h"

GW250Presenter::GW250Presenter(QObject *parent)
  : ECUPresenter(RDensoPowertrainPtr(new RDensoPowertrain(AppInst().commbox(), AppInst().db(), RDensoPowertrain::DCJ_GW250)), parent)
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

  QString name = RSystemDB::queryText("Read Current Trouble Code");
  _funcSelected[name] = boost::bind(&GW250Presenter::readCurrentTroubleCode, this);
  emit itemAdd(MenuItem(name, READ_CURRENT_TROUBLE_CODE_ICON, READ_CURRENT_TROUBLE_CODE_ICON_S));

  name = RSystemDB::queryText("Read History Trouble Code");
  _funcSelected[name] = boost::bind(&GW250Presenter::readHistoryTroubleCode, this);
  emit itemAdd(MenuItem(name, READ_HISTORY_TROUBLE_CODE_ICON, READ_HISTORY_TROUBLE_CODE_ICON_S));

  name = RSystemDB::queryText("Clear Trouble Code");
  _funcSelected[name] = boost::bind(&GW250Presenter::clearTroubleCode, this);
  emit itemAdd(MenuItem(name, CLEAR_TROUBLE_CODE_ICON, CLEAR_TROUBLE_CODE_ICON_S));
}

GW250Presenter::CommunicationState GW250Presenter::readAllInfoNow()
{
  auto tc = _ecu->getTroubleCode();
  if (!tc->tryReadCurrent()) {
    return CommunicationFail;
  }

  auto tcs = tc->waitCurrentFinish();
  if (tcs.isNull()) {
    _info = tc->getMessage();
    return CommunicationFail;
  }

  auto &ld = _ecu->getDataStream()->getLiveData();
  for (int i = 0; i < ld.size(); ++i) {
    ld[i].setIsShowed(true);
  }

  emit updateTroubleCodeUI(tcs);
  return Success;
}


