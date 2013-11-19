#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QMainWindow>
#include <QMessageBox>
#include <QToolBar>
#include <QAction>
#include <QStackedWidget>
#include "MenuWidget.h"
#include "MikuniWidget.h"
#include "GW250Widget.h"
#include "MainMenuPresenter.h"
#include "HJ125T_10Presenter.h"
#include "HJ125T_16APresenter.h"
#include "HJ125T_16CPresenter.h"
#include "GW250Presenter.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT
private:
  QMessageBox *_msgBox;
  QStackedWidget *_stackedWidget;
  MenuWidget *_mainMenu;
  MikuniWidget *_mikuni;
  GW250Widget *_gw250Widget;
  HJ125T_16APresenter *_hj125t_16a;
  HJ125T_16CPresenter *_hj125t_16c;
  HJ125T_10Presenter *_hj125t_10;
  GW250Presenter *_gw250;
  MainMenuPresenter *_mainMenuPresenter;
private:
  void initPresenter(MenuPresenter *p);
public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  QMessageBox *msgBox() const;
public slots:
  void showStatus(const QString &text);
  void hideStatus();
  void showCritical(const QString &text);
  void showInfo(const QString &text);
  void switchPage(QWidget *page);
};

#endif // __MAINWINDOW_H__
