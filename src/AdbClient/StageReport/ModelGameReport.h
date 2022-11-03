#ifndef MODELGAMEREPORT_H
#define MODELGAMEREPORT_H

#include <QAbstractTableModel>

class ModelGameReport : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ModelGameReport(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // MODELGAMEREPORT_H
