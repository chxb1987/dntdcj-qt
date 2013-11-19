#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MENU_ITEM_H__
#define __MENU_ITEM_H__

#include <QtGlobal>
#include <QString>
#include <QMetaType>

class MenuItem
{
private:
  QString _text;
  QString _icon;
  QString _iconSelected;
public:
  MenuItem();
  MenuItem(const QString &text,
           const QString &icon,
           const QString &iconSelected);
  ~MenuItem();
  const QString &getText() const;
  const QString &getIcon() const;
  const QString &getIconSelected() const;
};

Q_DECLARE_METATYPE(MenuItem)

#endif // __MENU_ITEM_H__
