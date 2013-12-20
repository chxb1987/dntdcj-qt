#include "LiveDataDelegate.h"

LiveDataDelegate::LiveDataDelegate(QObject *parent)
  : QItemDelegate(parent)
  , _lds()
{

}

void LiveDataDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  if (!_lds.isEmpty()) {
    if (_lds[index.row()].isEnabled() &&
        _lds[index.row()].isShowed()) {
      editor->setGeometry(option.rect);
      return;
    }
  }
  QItemDelegate::updateEditorGeometry(editor, option, index);
}

void LiveDataDelegate::setLiveData(const RLiveDataList::Elements &lds)
{
  _lds = lds;
}
