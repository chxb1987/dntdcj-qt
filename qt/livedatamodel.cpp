#include "LiveDataModel.h"
#include "App.h"

LiveDataModel::LiveDataModel(QObject *parent)
  : QAbstractTableModel(parent)
  , _lds()
  , _shortNameHeader(DNTSystemDB::queryText("ShortName"))
  , _contentHeader(DNTSystemDB::queryText("Content"))
  , _valueHeader(DNTSystemDB::queryText("Value"))
  , _unitHeader(DNTSystemDB::queryText("Unit"))
  , _dftValueHeader(DNTSystemDB::queryText("Default Value"))
{

}

int LiveDataModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  if (!_lds.isEmpty())
    return _lds.size();
  return 0;
}

int LiveDataModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return 5;
}

QVariant LiveDataModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid()) return QVariant();
  if (_lds.isEmpty()) return QVariant();

  auto i = index.row();
  if (role == Qt::DisplayRole) {
    switch (index.column()) {
    case 0:
      return _lds[i].shortName();
    case 1:
      return _lds[i].content();
    case 2:
      return QVariant(_lds[i].value());
    case 3:
      return _lds[i].unit();
    case 4:
      return _lds[i].defaultValue();
    }
  }
  return QVariant();
}

void LiveDataModel::setData(int index, const QString &value)
{
  setData(this->index(index, 2), value);
}

bool LiveDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  Q_UNUSED(value);
  if (!index.isValid())
    return false;

  if (role == Qt::EditRole) {
    switch (index.column()) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
      emit dataChanged(index, index);
      return true;
    }
  }
  return false;
}

Qt::ItemFlags LiveDataModel::flags(const QModelIndex &index) const
{
  if (index.column() == 0)
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
  return QAbstractTableModel::flags(index);
}

QVariant LiveDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role != Qt::DisplayRole)
    return QVariant();
  if (orientation == Qt::Horizontal) {
    switch (section) {
    case 0:
      return _shortNameHeader;
    case 1:
      return _contentHeader;
    case 2:
      return _valueHeader;
    case 3:
      return _unitHeader;
    case 4:
      return _dftValueHeader;
    }
  }
  return QAbstractTableModel::headerData(section, orientation, role);
}

void LiveDataModel::clear()
{
  if (!_lds.isEmpty()) {
    beginRemoveRows(QModelIndex(), 0, _lds.size() - 1);
    endRemoveRows();
  }
}

void LiveDataModel::update(const DNTLiveDataList::Elements &lds)
{
  clear();
  _lds = lds;
  if (_lds.isEmpty()) return;
  beginInsertRows(QModelIndex(), 0, _lds.size() - 1);
  endInsertRows();
}

