#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MENU_WIDGET_H__
#define __MENU_WIDGET_H__

#include <QWidget>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include "MenuItem.h"
#include "MenuPresenter.h"
#include "ui_MenuWidget.h"

class MenuWidget : public QWidget
{
  Q_OBJECT
private:
  Ui::MenuWidget _ui;
  QStandardItemModel _model;
  QItemSelectionModel _selectionModel;
  MenuPresenter *_dataContext;
protected:
  void changeEvent(QEvent *event);
public:
  explicit MenuWidget(QWidget *parent = 0);
  MenuPresenter* getDataContext();
private slots:
  void on_listView_doubleClicked(const QModelIndex &index);
  void on_backButton_clicked();
  void currentItemChange(const QModelIndex &current, const QModelIndex &previous);
public slots:
  void setDataContext(MenuPresenter *current);
  void itemAdd(const MenuItem &menu);
  void itemClr();
signals:
  void backButtonClick();
};

#endif // __MENU_WIDGET_H__
