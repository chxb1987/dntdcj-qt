#include "MikuniWidget.h"
#include "ui_MikuniWidget.h"
#include "MikuniPresenter.h"
#include "App.h"

MikuniWidget::MikuniWidget(QWidget *parent)
  : QWidget(parent)
  , _ui(new Ui::MikuniWidget())
  , _dataContext(nullptr)
{
  _ui->setupUi(this);
  _ui->menuGroup->setTitle(DNTSystemDB::queryText("Menu"));
  _ui->troubleCodeGroup->setTitle(DNTSystemDB::queryText("Trouble Code"));
  _ui->liveDataGroup->setTitle(DNTSystemDB::queryText("Live Data"));
  _ui->waveFromsGroup->setTitle(DNTSystemDB::queryText("Waveforms"));
  _ui->versionGroup->setTitle(DNTSystemDB::queryText("ECU Version"));
  _ui->softwareLabel->setText(DNTSystemDB::queryText("Software Version"));
  _ui->hardwareLabel->setText(DNTSystemDB::queryText("Hardware Version"));
  connect(_ui->liveDataPage, SIGNAL(itemClicked(QModelIndex)), _ui->plotPage, SLOT(currentLiveDataChange(QModelIndex)));
  connect(_ui->menuPage, SIGNAL(backButtonClick()), _ui->plotPage, SLOT(resetData()));
}

void MikuniWidget::setDataContext(MikuniPresenter *dataContext)
{
  if (_dataContext != NULL) {
    _dataContext->disconnect(SIGNAL(setHardwareVersion(QString)));
    _dataContext->disconnect(SIGNAL(setSoftwareVersion(QString)));
  }
  _dataContext = dataContext;
  connect(_dataContext, SIGNAL(setHardwareVersion(QString)), _ui->hardwareVersion, SLOT(setText(QString)));
  connect(_dataContext, SIGNAL(setSoftwareVersion(QString)), _ui->softwareVersion, SLOT(setText(QString)));
  _ui->troubleCodePage->setDataContext(_dataContext);
  _ui->liveDataPage->setDataContext(_dataContext);
  _ui->plotPage->setDataContext(_dataContext);
  _ui->menuPage->setDataContext(_dataContext);
}
