#include "TroubleCodePresenter.h"

TroubleCodePresenter::TroubleCodePresenter(QObject *parent)
  : QObject(parent)
{

}

void TroubleCodePresenter::setWidget(TroubleCodeWidget *widget)
{
  _widget = widget;
}

void TroubleCodePresenter::show()
{
  emit sendShow(_widget);
}
