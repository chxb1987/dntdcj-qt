#ifdef _MSC_VER
#pragma once
#endif

#ifndef __LIVEDATA_DELEGATE_H__
#define __LIVEDATA_DELEGATE_H__

#include <QItemDelegate>
#include <DNTLiveDataList.h>

class LiveDataDelegate : public QItemDelegate
{
  Q_OBJECT
private:
  DNTLiveDataList::Elements _lds;
public:
  explicit LiveDataDelegate(QObject *parent = 0);
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  void setLiveData(const DNTLiveDataList::Elements &lds);
};

#endif // __LIVEDATA_DELEGATE_H__
