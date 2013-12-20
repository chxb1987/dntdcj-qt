#include "MenuWidget.h"
#include "app.h"

MenuWidget::MenuWidget(QWidget *parent)
  : QWidget(parent)
  , _ui()
  , _model()
  , _selectionModel(&_model)
  , _dataContext(nullptr)
{
  _ui.setupUi(this);
  _ui.listView->setModel(&_model);
  _ui.listView->setSelectionModel(&_selectionModel);
  _ui.listView->setIconSize(QSize(128, 128));
  _ui.backButton->setEnabled(false);
  _ui.backButton->setText(RSystemDB::queryText("Back"));
  connect(&_selectionModel, SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(currentItemChange(QModelIndex,QModelIndex)));
  connect(_ui.backButton, SIGNAL(clicked()), this, SIGNAL(backButtonClick()));
}

void MenuWidget::on_listView_doubleClicked(const QModelIndex &index)
{
  if (index.isValid()) {
    auto item = _model.item(index.row(), index.column());
    auto menu = item->data().value<MenuItem>();
    _dataContext->itemClick(menu);
  }
}

void MenuWidget::on_backButton_clicked()
{
  if (_dataContext == nullptr) return;
  if (_dataContext->getPreDataContext() == nullptr) return;
  _dataContext->quit();
  _dataContext->getPreDataContext()->show();
}

void MenuWidget::currentItemChange(const QModelIndex &current, const QModelIndex &previous)
{
  auto item = _model.item(current.row(), current.column());
  if (item == nullptr) return;
  MenuItem menu = item->data().value<MenuItem>();
  item->setIcon(QIcon(menu.getIconSelected()));
  item = _model.item(previous.row(), previous.column());
  if (item != nullptr) {
    menu = item->data().value<MenuItem>();
    item->setIcon(QIcon(menu.getIcon()));
  }
}

void MenuWidget::itemAdd(const MenuItem &menu)
{
  int row = _model.rowCount();
  _model.insertRows(row, 0);
  QIcon icon(menu.getIcon());
  QStandardItem *item = new QStandardItem(icon, menu.getText());
  item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
  item->setData(QVariant::fromValue<MenuItem>(menu));
  _model.setItem(row, 0, item);
}

void MenuWidget::itemClr()
{
  _model.removeRows(0, _model.rowCount());
}

void MenuWidget::changeEvent(QEvent *event)
{
  if (event->type() == QEvent::LanguageChange) _ui.retranslateUi(this);
  else QWidget::changeEvent(event);
}

void MenuWidget::setDataContext(MenuPresenter *current)
{
  if (current == nullptr) return;
  if (_dataContext != nullptr) {
    _dataContext->disconnect(SIGNAL(itemClr()));
    _dataContext->disconnect(SIGNAL(itemAdd(MenuItem)));
  }
  _dataContext = current;
  connect(_dataContext, SIGNAL(itemClr()), this, SLOT(itemClr()));
  connect(_dataContext, SIGNAL(itemAdd(MenuItem)), this, SLOT(itemAdd(MenuItem)));
  if (_dataContext->getPreDataContext() != nullptr) {
    _ui.backButton->setEnabled(true);
  } else {
    _ui.backButton->setEnabled(false);
  }
  _dataContext->preparePage();
  _selectionModel.setCurrentIndex(_model.index(0, 0), QItemSelectionModel::SelectCurrent);
}

MenuPresenter *MenuWidget::getDataContext()
{
  return _dataContext;
}
