#include "App.h"
#include <QApplication>
#include <DNTRegister.h>

using namespace std;

App *App::_inst = nullptr;

App::App()
  : _commbox(nullptr)
  , _db(nullptr)
{
  if (_inst != nullptr) return;
  _inst = this;
}

App::~App()
{
  if (_commbox != nullptr) delete _commbox;
  if (_db != nullptr) delete _db;
  _commbox = nullptr;
  _db = nullptr;
}

bool App::prepare()
{
  DNTRegister::init(qApp->applicationDirPath());
  DNTSystemDB::init(qApp->applicationDirPath());
  _db = new DNTVehicleDB(qApp->applicationDirPath(), "DCJ");
  _commbox = new DNTCommbox(RCommboxVer::C168);
  return _db->open();
}

App* App::getInstance()
{
  return _inst;
}

bool App::openCommbox(QString &result)
{
  if (!_commbox) return false;
  if (_commbox->connect()) return true;
  result = DNTSystemDB::queryText("Open Commbox Fail");
  return false;
}

void App::closeCommbox()
{
  if (!_commbox) return;
  _commbox->disconnect();
}

DNTCommbox& App::commbox()
{
  return *_commbox;
}

DNTVehicleDB& App::db()
{
  return *_db;
}
