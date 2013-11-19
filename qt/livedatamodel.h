#ifdef _MSC_VER
#pragma once
#endif

#ifndef __LIVEDATA_MODEL_H__
#define __LIVEDATA_MODEL_H__

#include <QAbstractTableModel>
#include <DNTLiveDataList.h>

class LiveDataModel : public QAbstractTableModel
{
  Q_OBJECT
private:
  DNTLiveDataList _lds;
  QString _shortNameHeader;
  QString _contentHeader;
  QString _valueHeader;
  QString _unitHeader;
  QString _dftValueHeader;
public:
  explicit LiveDataModel(QObject *parent = 0);
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
  Qt::ItemFlags flags(const QModelIndex &index) const;
  void setData(int index, const QString &value);
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
  void clear();
  void update(const DNTLiveDataList &lds);
};

#endif // __LIVEDATA_MODEL_H__
