#include "ECUPresenter.h"
#include <DNTSystemDB.h>
#include "App.h"

using namespace std;

const char* ECUPresenter::READ_CURRENT_TROUBLE_CODE_ICON = ":/icons/ReadCurrentTroubleCode.png";
const char* ECUPresenter::READ_CURRENT_TROUBLE_CODE_ICON_S = ":/icons/ReadCurrentTroubleCode.png";
const char* ECUPresenter::READ_HISTORY_TROUBLE_CODE_ICON = ":/icons/ReadHistoryTroubleCode.png";
const char* ECUPresenter::READ_HISTORY_TROUBLE_CODE_ICON_S = ":/icons/ReadHistoryTroubleCode.png";
const char* ECUPresenter::CLEAR_TROUBLE_CODE_ICON = ":/icons/ClearTroubleCode.png";
const char* ECUPresenter::CLEAR_TROUBLE_CODE_ICON_S = ":/icons/ClearTroubleCode.png";
const char* ECUPresenter::READ_DATA_STREAM_ICON = ":/icons/ReadDataStream.png";
const char* ECUPresenter::READ_DATA_STREAM_ICON_S = ":/icons/ReadDataStream.png";
const char* ECUPresenter::READ_ECU_VERSION_ICON = ":/icons/ReadECUVersion.png";
const char* ECUPresenter::READ_ECU_VERSION_ICON_S = ":/icons/ReadECUVersion.png";
const char* ECUPresenter::TPS_IDLE_SETTING_ICON = ":/icons/TPSIdleSetting.png";
const char* ECUPresenter::TPS_IDLE_SETTING_ICON_S = ":/icons/TPSIdleSetting.png";
const char* ECUPresenter::LONG_TERM_LEARNING_VALUE_INITIALIZATION_ICON = ":/icons/LongTermLearningValueInitialize.png";
const char* ECUPresenter::LONG_TERM_LEARNING_VALUE_INITIALIZATION_ICON_S = ":/icons/LongTermLearningValueInitialize.png";
const char* ECUPresenter::ISC_LEARN_VALUE_INITIALIZATION_ICON = ":/icons/IdleControlLearningValueInitialize.png";
const char* ECUPresenter::ISC_LEARN_VALUE_INITIALIZATION_ICON_S = ":/icons/IdleControlLearningValueInitialize.png";

ECUPresenter::ECUPresenter(const RECUInterfacePtr &ecu, QObject *parent)
  : MenuPresenter(parent)
  , _watcher()
  , _future()
  , _info()
  , _dataStreamUIFuture()
  , _internalState(Success)
  , _dataStreamUIUpdating(false)
  , _ecu(ecu)
{

}

void ECUPresenter::preparePage()
{
  _watcher.disconnect();
  connect(&_watcher, SIGNAL(finished()), this, SLOT(realPreparePage()));
  _future = QtConcurrent::run(this, &ECUPresenter::preparePageData);
  _watcher.setFuture(_future);
}

ECUPresenter::CommunicationState ECUPresenter::preparePageData()
{
  emit clearTroubleCodeUI();
  emit clearLiveDataUI();
  emit itemClr();

  emit showStatus(RSystemDB::queryText("OpenCommbox"));
  if (!AppInst().openCommbox(_info)) {
    _internalState = CommunicationFail;
  } else if (!_ecu || !(_ecu->ioChannelInit())) {
    _info = _ecu->getLastInfo();
    _internalState = CommunicationFail;
  } else {
    emit showStatus(RSystemDB::queryText("Communicating"));
    _internalState = readAllInfoNow();
  }

  if (_internalState != CommunicationFail) {
    auto tc = _ecu->getTroubleCode();
    connect(tc, SIGNAL(currentFinished(QString,RTroubleCodeVector)), this, SLOT(showTroubleCode(QString, RTroubleCodeVector)));
    connect(tc, SIGNAL(historyFinished(QString,RTroubleCodeVector)), this, SLOT(showTroubleCode(QString,RTroubleCodeVector)));
    connect(tc, SIGNAL(clearFinished(QString, bool)), this, SLOT(showClearTroubleCode(QString,bool)));

    auto &ld = getLiveData();
    ld.collate();
    emit updateLiveDataUI();
    runDataStream();
  }

  return _internalState;
}

void ECUPresenter::readCurrentTroubleCode()
{
  emit showStatus(RSystemDB::queryText("Communicating"));
  stopDataStream();
  auto tc = _ecu->getTroubleCode();
  if (!tc->tryReadCurrent())
    runDataStream();
}

void ECUPresenter::readHistoryTroubleCode()
{
  emit showStatus(AppInst().getText("Communicating", "System"));

  stopDataStream();
  auto tc = _ecu->getTroubleCode();
  if (!tc->tryReadHistory())
    runDataStream();
}

void ECUPresenter::clearTroubleCode()
{
  emit showStatus(AppInst().getText("Clearing Trouble Code, Please Wait", "System"));

  stopDataStream();
  auto tc = _ecu->getTroubleCode();
  if (!tc->tryClear())
    runDataStream();
}

void ECUPresenter::showTroubleCode(const QString &msg, const RTroubleCodeVector &tcs)
{
  _internalState = Success;
  runDataStream();
  if (!msg.isEmpty()) {
    emit showCritical(msg);
    return;
  }

  emit updateTroubleCodeUI(tcs);
  if (tcs.empty()) {
    emit showInfo(RSystemDB::queryText("None Trouble Code"));
  } else {
    emit hideStatus();
  }
}

void ECUPresenter::showClearTroubleCode(const QString &msg, bool result)
{
  runDataStream();
  if (!result) emit showCritical(msg);
  emit showInfo(msg);
  _internalState = Success;
}

void ECUPresenter::runDataStream()
{
  auto ds = _ecu->getDataStream();
  connect(ds, SIGNAL(dataStreamFinished(bool)), this, SLOT(dataStreamFinished(bool)));
  ds->start();
  startUpdateDataStreamUI();
}

void ECUPresenter::stopDataStream()
{
  _ecu->getDataStream()->stop();
  stopUpdateDataStreamUI();
}

void ECUPresenter::dataStreamFinished(bool result)
{
  if (!result) {
    _info = _ecu->getLastInfo();
    emit showCritical(_info);
  }
}

void ECUPresenter::startUpdateDataStreamUI()
{
  _dataStreamUIUpdating = true;
  _dataStreamUIFuture = QtConcurrent::run(this, &ECUPresenter::updateDataStreamUI);
}

void ECUPresenter::stopUpdateDataStreamUI()
{
  _dataStreamUIUpdating = false;
  if (_dataStreamUIFuture.isRunning())
    _dataStreamUIFuture.waitForFinished();
}

void ECUPresenter::updateDataStreamUI()
{
  auto& vec = getLiveData();
  if (vec.isEmpty()) {
    _dataStreamUIUpdating = false;
    return;
  }

  auto items = vec.getShowedItems();
  while (_dataStreamUIUpdating) {
    for (int i = 0; i < items.size(); ++i) {
      QThread::currentThread()->msleep(10);
      emit updateValue(i, items[i].value());
    }
  }
}

void ECUPresenter::showSettingResult()
{
  auto result = _watcher.result();
  _internalState = Success;

  if (result == CommunicationFail) {
    emit showCritical(_info);
    return;
  }

  emit showInfo(_info);
}

void ECUPresenter::quit()
{
  emit showStatus(RSystemDB::queryText("Communicating"));

  _watcher.disconnect();
  connect(&_watcher, SIGNAL(finished()), this, SLOT(quitFinish()));
  _future = QtConcurrent::run(this, &ECUPresenter::realQuit);
  _watcher.setFuture(_future);
}

ECUPresenter::CommunicationState ECUPresenter::prepareToQuit()
{
  stopDataStream();
  return _internalState;
}

ECUPresenter::CommunicationState ECUPresenter::realQuit()
{
  CommunicationState ret = prepareToQuit();
  AppInst().closeCommbox();
  return ret;
}

void ECUPresenter::quitFinish()
{
  auto result = _watcher.result();
  if (result == CommunicationFail) {
    emit showCritical(_info);
  } else {
    emit hideStatus();
  }
  _preDataContext->show();
}

RLiveDataList &ECUPresenter::getLiveData()
{
  return _ecu->getDataStream()->getLiveData();
}
