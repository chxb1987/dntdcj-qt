#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MENU_PRESENTER_H__
#define __MENU_PRESENTER_H__

#include <QObject>
#include <QHash>
#ifndef Q_MOC_RUN
#include <boost/function.hpp>
#endif
#include "MenuItem.h"

class MenuWidget;
class MenuPresenter : public QObject
{
  Q_OBJECT
public:
  typedef boost::function<void ()> ProtocolFunc;
protected:
  QHash<QString, ProtocolFunc> _funcSelected;
  QWidget *_widget;
  MenuPresenter *_preDataContext;
public:
  explicit MenuPresenter(QObject *parent = 0);
  ~MenuPresenter();
  void setWidget(QWidget *widget);
  void setPreDataContext(MenuPresenter *d);
  MenuPresenter* getPreDataContext();
  virtual void preparePage() = 0;
  virtual void quit() = 0;
  virtual void show();
public slots:
  void itemClick(const MenuItem &item);
signals:
  void itemAdd(const MenuItem &item);
  void itemClr();
  void switchPage(QWidget *widget);
  void showStatus(const QString &text);
  void hideStatus();
  void showCritical(const QString &text);
  void showInfo(const QString &text);
};

#endif // __MENU_PRESENTER_H__
