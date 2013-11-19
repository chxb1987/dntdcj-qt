#include "TroubleCodeWidget.h"
#include "ui_TroubleCodeWidget.h"
#include "App.h"

TroubleCodeWidget::TroubleCodeWidget(QWidget *parent)
  : QWidget(parent)
  , _ui(new Ui::TroubleCodeWidget())
  , _model(this)
  , _dataContext(nullptr)
{
  _ui->setupUi(this);
  _ui->tableView->setModel(&_model);
}

TroubleCodeWidget::~TroubleCodeWidget()
{
  delete _ui;
}

void TroubleCodeWidget::changeEvent(QEvent *event)
{
  if (event->type() == QEvent::LanguageChange) {
    _ui->retranslateUi(this);
  } else {
    QWidget::changeEvent(event);
  }
}

void TroubleCodeWidget::clear()
{
  _model.clear();
}

void TroubleCodeWidget::updateData()
{
  if (_dataContext == nullptr) return;
  _model.update(_dataContext->getTroubleCode());
}

void TroubleCodeWidget::setDataContext(ECUPresenter *dataContext)
{
  if (_dataContext != nullptr) {
    _dataContext->disconnect(SIGNAL(updateTroubleCodeUI()));
    _dataContext->disconnect(SIGNAL(clearTroubleCodeUI()));
  }
  _dataContext = dataContext;
  connect(_dataContext, SIGNAL(updateTroubleCodeUI()), this, SLOT(updateData()));
  connect(_dataContext, SIGNAL(clearTroubleCodeUI()), this, SLOT(clear()));
}
