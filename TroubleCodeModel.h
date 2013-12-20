#ifdef _MSC_VER
#pragma once
#endif

#ifndef __TROUBLECODE_MODEL_H__
#define __TROUBLECODE_MODEL_H__

#include <QAbstractTableModel>
#include <DNTTroubleCodeVector.h>

class TroubleCodeModel : public QAbstractTableModel
{
  Q_OBJECT
private:
  RTroubleCodeVector _tcs;
  QString _codeHeader;
  QString _contentHeader;
public:
  explicit TroubleCodeModel(QObject *parent = 0);
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
  void update(const RTroubleCodeVector &tcs);
  void clear();
};

#endif // __TROUBLECODE_MODEL_H__
