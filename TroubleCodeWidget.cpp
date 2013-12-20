#include "TroubleCodeWidget.h"
#include "App.h"

TroubleCodeWidget::TroubleCodeWidget(QWidget *parent)
  : QWidget(parent)
  , _ui()
  , _model(this)
  , _dataContext(nullptr)
{
  _ui.setupUi(this);
  _ui.tableView->setModel(&_model);
}

void TroubleCodeWidget::changeEvent(QEvent *event)
{
  if (event->type() == QEvent::LanguageChange) {
    _ui.retranslateUi(this);
  } else {
    QWidget::changeEvent(event);
  }
}

void TroubleCodeWidget::clear()
{
  _model.clear();
}

void TroubleCodeWidget::updateData(const RTroubleCodeVector &tcs)
{
  _model.update(tcs);
}

void TroubleCodeWidget::setDataContext(ECUPresenter *dataContext)
{
  if (_dataContext != nullptr) {
    _dataContext->disconnect(SIGNAL(updateTroubleCodeUI(RTroubleCodeVector)));
    _dataContext->disconnect(SIGNAL(clearTroubleCodeUI()));
  }
  _dataContext = dataContext;
  connect(_dataContext, SIGNAL(updateTroubleCodeUI(RTroubleCodeVector)), this, SLOT(updateData(RTroubleCodeVector)));
  connect(_dataContext, SIGNAL(clearTroubleCodeUI()), this, SLOT(clear()));
}
