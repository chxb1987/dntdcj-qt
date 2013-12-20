#ifdef _MSC_VER
#pragma once
#endif

#ifndef __ECU_PRESENTER_H__
#define __ECU_PRESENTER_H__

#include <QtConcurrent/QtConcurrent>
#include <QThreadPool>
#include <DNTAbstractECU.h>
#include <DNTLiveDataList.h>
#include <DNTTroubleCodeVector.h>
#include "MenuPresenter.h"

class ECUPresenter : public MenuPresenter
{
  Q_OBJECT
public:
  static const char* READ_CURRENT_TROUBLE_CODE_ICON;
  static const char* READ_CURRENT_TROUBLE_CODE_ICON_S;
  static const char* READ_HISTORY_TROUBLE_CODE_ICON;
  static const char* READ_HISTORY_TROUBLE_CODE_ICON_S;
  static const char* CLEAR_TROUBLE_CODE_ICON;
  static const char* CLEAR_TROUBLE_CODE_ICON_S;
  static const char* READ_DATA_STREAM_ICON;
  static const char* READ_DATA_STREAM_ICON_S;
  static const char* READ_ECU_VERSION_ICON;
  static const char* READ_ECU_VERSION_ICON_S;
  static const char* TPS_IDLE_SETTING_ICON;
  static const char* TPS_IDLE_SETTING_ICON_S;
  static const char* LONG_TERM_LEARNING_VALUE_INITIALIZATION_ICON;
  static const char* LONG_TERM_LEARNING_VALUE_INITIALIZATION_ICON_S;
  static const char* ISC_LEARN_VALUE_INITIALIZATION_ICON;
  static const char* ISC_LEARN_VALUE_INITIALIZATION_ICON_S;
public:
  enum CommunicationState
  {
    CommunicationFail,
    Standard, // for prepare check ecu
    Extension, // for prepare check ecu
    Success
  };
protected:
  QFutureWatcher<ECUPresenter::CommunicationState> _watcher;
  QFuture<ECUPresenter::CommunicationState> _future;
  QFuture<void> _dataStreamUIFuture;
  QString _info;
  CommunicationState _internalState;
  bool _dataStreamUIUpdating;
  RECUInterfacePtr _ecu;
private:
  CommunicationState readCurrentTroubleCodeReal();
  CommunicationState readHistoryTroubleCodeReal();
  CommunicationState clearTroubleCodeReal();
  CommunicationState realQuit();
protected:
  // prepare page
  virtual CommunicationState prepareToQuit();
  virtual CommunicationState readAllInfoNow() = 0;
  virtual CommunicationState preparePageData();

  // read trouble code
  virtual void readCurrentTroubleCode();
  virtual void readHistoryTroubleCode();
  virtual void clearTroubleCode();

  virtual void runDataStream();
  virtual void stopDataStream();
  virtual void stopUpdateDataStreamUI();
public:
  ECUPresenter(const RECUInterfacePtr &ecu, QObject *parent = 0);
  virtual RLiveDataList& getLiveData();
  virtual void preparePage();
protected slots:
  virtual void realPreparePage() = 0;
  void showTroubleCode(const QString &msg, const RTroubleCodeVector &tcs);
  void showClearTroubleCode(const QString &msg, bool result);
  void showSettingResult();
  void updateDataStreamUI();
  void startUpdateDataStreamUI();
  void dataStreamFinished(bool result);
  void quitFinish();
public slots:
  void quit();
signals:
  void updateTroubleCodeUI(const RTroubleCodeVector &tcs);
  void clearTroubleCodeUI();
  void updateLiveDataUI();
  void clearLiveDataUI();
  void updateValue(int i, const QString &value);
};

#endif // __ECU_PRESENTER_H__
