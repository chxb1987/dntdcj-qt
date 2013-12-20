#include "App.h"
#include <QApplication>
#include <DNTRegister.h>

using namespace std;

App *App::_inst = nullptr;

App::App()
  : _commbox()
  , _db()
{
  if (_inst != nullptr) return;
  _inst = this;
}

App::~App()
{
  _db.close();
  _commbox.disconnect();
}

bool App::prepare()
{
  RRegister::init(qApp->applicationDirPath());
  RSystemDB::init(qApp->applicationDirPath());
  _commbox.setVersion(RCommbox::C168);
  return _db.open(qApp->applicationDirPath(), "DCJ");
}

App& App::getInstance()
{
  return *_inst;
}

bool App::openCommbox(QString &result)
{
  if (_commbox.connect()) return true;
  result = RSystemDB::queryText("Open Commbox Fail");
  return false;
}

void App::closeCommbox()
{
  _commbox.disconnect();
}

RCommbox& App::commbox()
{
  return _commbox;
}

RVehicleDB& App::db()
{
  return _db;
}
