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

ECUPresenter::ECUPresenter(DNTAbstractECU *ecu, QObject *parent)
  : MenuPresenter(parent)
  , _watcher()
  , _future()
  , _dataStreamWatcher()
  , _dataStreamFuture()
  , _info()
  , _dataStreamUIFuture()
  , _internalState(Success)
  , _dataStreamUIUpdating(false)
  , _ecu(ecu)
{

}

ECUPresenter::~ECUPresenter()
{
  if (_ecu != nullptr)
    delete _ecu;
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

  emit showStatus(DNTSystemDB::queryText("OpenCommbox"));
  if (!AppInst()->openCommbox(_info)) {
    _internalState = CommunicationFail;
  } else if ((_ecu == nullptr) ||
             !(_ecu->ioChannelInit())) {
    _info = _ecu->getLastInfo();
    _internalState = CommunicationFail;
  } else {
    emit showStatus(DNTSystemDB::queryText("Communicating"));
    _internalState = readAllInfoNow();
  }

  if (_internalState != CommunicationFail) {
    getLiveData().collate();
    emit updateLiveDataUI();
    runDataStream();
  }

  return _internalState;
}

void ECUPresenter::readCurrentTroubleCode()
{
  emit showStatus(DNTSystemDB::queryText("Communicating"));

  _watcher.disconnect();
  connect(&_watcher, SIGNAL(finished()), this, SLOT(showTroubleCode()));
  _future = QtConcurrent::run(this, &ECUPresenter::readCurrentTroubleCodeReal);
  _watcher.setFuture(_future);
}

ECUPresenter::CommunicationState ECUPresenter::readCurrentTroubleCodeReal()
{
  stopDataStream();
  auto ret = readCurrentTroubleCodeData();
  runDataStream();
  return ret;
}

void ECUPresenter::readHistoryTroubleCode()
{
  emit showStatus(AppInst()->getText("Communicating", "System"));

  _watcher.disconnect();
  connect(&_watcher, SIGNAL(finished()), this, SLOT(showTroubleCode()));
  _future = QtConcurrent::run(this, &ECUPresenter::readHistoryTroubleCodeReal);
  _watcher.setFuture(_future);
}

ECUPresenter::CommunicationState ECUPresenter::readHistoryTroubleCodeReal()
{
  stopDataStream();
  auto ret = readHistoryTroubleCodeData();
  runDataStream();
  return ret;
}

void ECUPresenter::clearTroubleCode()
{
  emit showStatus(AppInst()->getText("Clearing Trouble Code, Please Wait", "System"));

  _watcher.disconnect();
  connect(&_watcher, SIGNAL(finished()), this, SLOT(showSettingResult()));
  _future = QtConcurrent::run(this, &ECUPresenter::clearTroubleCodeReal);
  _watcher.setFuture(_future);
}

ECUPresenter::CommunicationState ECUPresenter::clearTroubleCodeReal()
{
  stopDataStream();
  auto ret = clearTroubleCodeData();
  runDataStream();
  return ret;
}

void ECUPresenter::showTroubleCode()
{
  auto result = _watcher.result();

  if (result == CommunicationFail) {
    emit showCritical(_info);
    return;
  }

  auto tcs = getTroubleCode();
  emit updateTroubleCodeUI();
  if (tcs.empty()) {
    emit showInfo(DNTSystemDB::queryText("None Trouble Code"));
  } else {
    emit hideStatus();
  }
}

void ECUPresenter::runDataStream()
{
  _dataStreamWatcher.disconnect();
  connect(&_dataStreamWatcher, SIGNAL(finished()), this, SLOT(dataStreamFinish()));
  _dataStreamFuture = QtConcurrent::run(this, &ECUPresenter::readDataStream);
  _dataStreamWatcher.setFuture(_dataStreamFuture);
  startUpdateDataStreamUI();
}

void ECUPresenter::stopDataStream()
{
  stopUpdateDataStreamUI();
  stopDataStreamData();
  if (_dataStreamWatcher.isRunning())
    _dataStreamWatcher.waitForFinished();
}

void ECUPresenter::dataStreamFinish()
{
  auto ret = _dataStreamWatcher.result();
  if (ret != Success) {
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
  auto vec = getLiveData();
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

  if (result == CommunicationFail) {
    emit showCritical(_info);
    return;
  }

  emit showInfo(_info);
}

void ECUPresenter::quit()
{
  emit showStatus(DNTSystemDB::queryText("Communicating"));

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
  AppInst()->closeCommbox();
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

DNTLiveDataList &ECUPresenter::getLiveData()
{
  auto ds = _ecu->getDataStream();
  return ds.getLiveData();
}
