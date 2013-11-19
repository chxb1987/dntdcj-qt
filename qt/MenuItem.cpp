#include "MenuItem.h"

MenuItem::MenuItem()
  : _text()
  , _icon()
  , _iconSelected()
{

}

MenuItem::MenuItem(const QString &text, const QString &icon, const QString &iconSelected)
  : _text(text)
  , _icon(icon)
  , _iconSelected(iconSelected)
{

}

MenuItem::~MenuItem()
{

}

const QString &MenuItem::getText() const
{
  return _text;
}

const QString &MenuItem::getIcon() const
{
  return _icon;
}

const QString &MenuItem::getIconSelected() const
{
  return _iconSelected;
}
