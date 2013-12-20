#include "TroubleCodeModel.h"
#include "App.h"
#include <QtDebug>

using namespace std;

TroubleCodeModel::TroubleCodeModel(QObject *parent)
  : QAbstractTableModel(parent)
  , _tcs()
  , _codeHeader(RSystemDB::queryText("Code"))
  , _contentHeader(RSystemDB::queryText("Content"))
{

}

int TroubleCodeModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return _tcs.size();
}

int TroubleCodeModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return 2;
}

QVariant TroubleCodeModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  if (_tcs.empty())
    return QVariant();

  if (role == Qt::DisplayRole) {
    if (index.column() == 0) {
      return _tcs[index.row()].getCode();
    } else if (index.column() == 1) {
      return _tcs[index.row()].getContent();
    }
  }

  return QVariant();
}

QVariant TroubleCodeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role != Qt::DisplayRole) return QAbstractTableModel::headerData(section, orientation, role);

  if (orientation == Qt::Horizontal) {
    if (section == 0) return QVariant(_codeHeader);
    else if (section == 1) return QVariant(_contentHeader);
  }
  return QAbstractTableModel::headerData(section, orientation, role);
}

void TroubleCodeModel::clear()
{
  if (_tcs.size() > 0) {
    beginRemoveRows(QModelIndex(), 0, _tcs.size() - 1);
    endRemoveRows();
  }
}

void TroubleCodeModel::update(const RTroubleCodeVector &tcs)
{
  clear();
  _tcs = tcs;
  if (_tcs.size() == 0) return;
  beginInsertRows(QModelIndex(), 0, _tcs.size() - 1);
  endInsertRows();
}
