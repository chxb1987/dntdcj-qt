#ifdef _MSC_VER
#pragma once
#endif

#ifndef __APP_H__
#define __APP_H__

#include <QMessageBox>
#include <DNTCommbox.h>
#include <DNTVehicleDB.h>
#include <DNTSystemDB.h>
#include <DNTMikuniPowertrain.h>
#include "MainWindow.h"

class App
{
  friend class MainWindow;
private:
  static App *_inst;
  RCommbox _commbox;
  RVehicleDB _db;
public: // construct
  App();
  ~App();
  static App &getInstance();
  inline QString getText(const QString &text, const QString &sys)
  {
    return _db.getText(text, sys);
  }

  bool prepare();

public: // Diag
  bool openCommbox(QString &result);
  void closeCommbox();
  RCommbox &commbox();
  RVehicleDB &db();
};

inline App& AppInst()
{
  return App::getInstance();
}

#endif // __APP_H__
