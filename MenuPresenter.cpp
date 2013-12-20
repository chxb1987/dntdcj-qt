#include "MenuPresenter.h"
#include "App.h"

MenuPresenter::MenuPresenter(QObject *parent)
  : QObject(parent)
  , _funcSelected()
  , _widget(nullptr)
  , _preDataContext(nullptr)
{

}

MenuPresenter::~MenuPresenter()
{

}

void MenuPresenter::itemClick(const MenuItem &item)
{
  if (_funcSelected.contains(item.getText())) {
    _funcSelected[item.getText()]();
  }
}

void MenuPresenter::setWidget(QWidget *widget)
{
  _widget = widget;
}

void MenuPresenter::setPreDataContext(MenuPresenter *d)
{
  _preDataContext = d;
}

MenuPresenter *MenuPresenter::getPreDataContext()
{
  return _preDataContext;
}

void MenuPresenter::show()
{
  emit switchPage(_widget);
}
