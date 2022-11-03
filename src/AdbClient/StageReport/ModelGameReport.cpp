#include "ModelGameReport.h"

ModelGameReport::ModelGameReport(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant ModelGameReport::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

int ModelGameReport::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int ModelGameReport::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant ModelGameReport::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
