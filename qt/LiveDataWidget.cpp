#include "LiveDataWidget.h"
#include "ui_LiveDataWidget.h"

LiveDataWidget::LiveDataWidget(QWidget *parent)
  : QWidget(parent)
  , _ui(new Ui::LiveDataWidget)
  , _model()
  , _delegate()
  , _dataContext(nullptr)
{
  _ui->setupUi(this);
  _ui->tableView->setModel(&_model);
  _ui->tableView->setItemDelegate(&_delegate);
  _ui->tableView->setWordWrap(true);

  connect(_ui->tableView, SIGNAL(clicked(QModelIndex)), this, SIGNAL(itemClicked(QModelIndex)));
}

LiveDataWidget::~LiveDataWidget()
{
  delete _ui;
}

void LiveDataWidget::setValue(int index, const QString &value)
{
  _model.setData(index, value);
}

void LiveDataWidget::changeEvent(QEvent *event)
{
  if (event->type() == QEvent::LanguageChange)
    _ui->retranslateUi(this);
  else
    QWidget::changeEvent(event);
}

void LiveDataWidget::updateData()
{
  if (_dataContext == nullptr) return;
  _model.update(_dataContext->getLiveData());
}

void LiveDataWidget::clear()
{
  _model.clear();
}

void LiveDataWidget::setDataContext(ECUPresenter *dataContext)
{
  if (dataContext == nullptr) return;
  if (_dataContext != nullptr) {
    _dataContext->disconnect(SIGNAL(updateLiveDataUI()));
    _dataContext->disconnect(SIGNAL(clearLiveDataUI()));
    _dataContext->disconnect(SIGNAL(updateValue(int, QString)));
  }
  _dataContext = dataContext;
  connect(_dataContext, SIGNAL(updateLiveDataUI()), this, SLOT(updateData()));
  connect(_dataContext, SIGNAL(clearLiveDataUI()), this, SLOT(clear()));
  connect(_dataContext, SIGNAL(updateValue(int,QString)), this, SLOT(setValue(int,QString)));
}
