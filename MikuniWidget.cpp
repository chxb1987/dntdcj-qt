#include "MikuniWidget.h"
#include "MikuniPresenter.h"
#include "App.h"

MikuniWidget::MikuniWidget(QWidget *parent)
  : QWidget(parent)
  , _ui()
  , _dataContext(nullptr)
{
  _ui.setupUi(this);
  _ui.menuGroup->setTitle(RSystemDB::queryText("Menu"));
  _ui.troubleCodeGroup->setTitle(RSystemDB::queryText("Trouble Code"));
  _ui.liveDataGroup->setTitle(RSystemDB::queryText("Live Data"));
  _ui.waveFromsGroup->setTitle(RSystemDB::queryText("Waveforms"));
  _ui.versionGroup->setTitle(RSystemDB::queryText("ECU Version"));
  _ui.softwareLabel->setText(RSystemDB::queryText("Software Version"));
  _ui.hardwareLabel->setText(RSystemDB::queryText("Hardware Version"));
  connect(_ui.liveDataPage, SIGNAL(itemClicked(QModelIndex)), _ui.plotPage, SLOT(currentLiveDataChange(QModelIndex)));
  connect(_ui.menuPage, SIGNAL(backButtonClick()), _ui.plotPage, SLOT(resetData()));
}

void MikuniWidget::setDataContext(MikuniPresenter *dataContext)
{
  if (_dataContext != nullptr) {
    _dataContext->disconnect(SIGNAL(setHardwareVersion(QString)));
    _dataContext->disconnect(SIGNAL(setSoftwareVersion(QString)));
  }
  _dataContext = dataContext;
  connect(_dataContext, SIGNAL(setHardwareVersion(QString)), _ui.hardwareVersion, SLOT(setText(QString)));
  connect(_dataContext, SIGNAL(setSoftwareVersion(QString)), _ui.softwareVersion, SLOT(setText(QString)));
  _ui.troubleCodePage->setDataContext(_dataContext);
  _ui.liveDataPage->setDataContext(_dataContext);
  _ui.plotPage->setDataContext(_dataContext);
  _ui.menuPage->setDataContext(_dataContext);
}
