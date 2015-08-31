#ifndef MYMODEL_H
#define MYMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QModelIndex>
#include <QVariant>
#include <QHash>
#include <QByteArray>
#include <QVector>
#include <QString>
#include "tile.h"

class MyModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MyModel(QObject *parent = 0);

    enum Roles {
        ValueRole = Qt::UserRole + 1,
        StateRole = Qt::UserRole + 2,
    };

    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void activate(int i);

signals:
    void victory();

public slots:
    void getMix();

private:
    QVector<Tile> listOfTiles;

    void move(int from, int to);
    void printModel();
    void clearGameGrid();
    void fillGameGrid();
    void checkForVictory();
    bool checkForSolvability();
};

#endif // MYMODEL_H
