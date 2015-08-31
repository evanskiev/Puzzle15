#include "mymodel.h"
#include <QDebug>
#include "QtAlgorithms"
#include <QModelIndex>

MyModel::MyModel(QObject *parent) : QAbstractListModel(parent)
{
    getMix();
}

int MyModel::rowCount(const QModelIndex &parent) const
{
    return listOfTiles.size();
}

QHash<int, QByteArray> MyModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[ValueRole] = "value";
    roles[StateRole] = "status";
    return roles;
}

void MyModel::getMix()
{
    do {
        clearGameGrid();

        int temp;
        QVector<int> randomNumbers;

        while (listOfTiles.size() < 15)
        {
            temp = rand() % 15 + 1;

            if (!randomNumbers.contains(temp))
            {
                randomNumbers.append(temp);
                Tile tile(temp, true);
                listOfTiles.append(tile);
            }
        }
    } while (!checkForSolvability());

    listOfTiles.append(Tile(0, false));

    fillGameGrid();
}

void MyModel::printModel()
{
    qDebug() << "*******************";
    qDebug() << listOfTiles[0].value() << " " << listOfTiles[1].value() << " " << listOfTiles[2].value() << " " <<listOfTiles[3].value();
    qDebug() << listOfTiles[4].value() << " " << listOfTiles[5].value() << " " << listOfTiles[6].value() << " " <<listOfTiles[7].value();
    qDebug() << listOfTiles[8].value() << " " << listOfTiles[9].value() << " " << listOfTiles[10].value() << " " <<listOfTiles[11].value();
    qDebug() << listOfTiles[12].value() << " " << listOfTiles[13].value() << " " << listOfTiles[14].value() << " " <<listOfTiles[15].value();
    qDebug() << "*******************";
}

void MyModel::fillGameGrid()
{
    beginInsertRows(QModelIndex(), 0, 15);
    endInsertRows();
}

void MyModel::clearGameGrid()
{
    listOfTiles.clear();

    beginRemoveRows(QModelIndex(), 0, 15);
    endRemoveRows();
}

void MyModel::checkForVictory()
{
    int counter = 1;

    for(int i = 0; i < 15; i++)
    {
        if (listOfTiles[i].value() != counter)
        {
            return;
        }
        counter += 1;
    }
    if (counter == 16)
    {
        emit victory();
    }
}

bool MyModel::checkForSolvability()
{
    int n = 0;
    int e = 4;

    for (int i = 0; i < 15; i++)
    {
        for (int j = i + 1; j < 15; j++)
        {
            if (listOfTiles[i].value() > listOfTiles[j].value())
            {
                n += 1;
            }
        }
    }
    n += e;

    if (n%2 == 0)
    {
        qDebug() << "1";
        return true;
    }
    qDebug() << "0";
    return false;
}

QVariant MyModel::data(const QModelIndex &index, int role) const {
    if(!index.isValid())
    {
        return QVariant();
    }
    const Tile& t = listOfTiles[index.row()];

    if(role == ValueRole)
    {
        return t.value();
    }
    if (role == StateRole)
    {
        return t.status();
    }
    return QVariant();
}

void MyModel::move(int from, int to)
{
    if (to > from)
    {
        beginMoveRows(QModelIndex(), from, from, QModelIndex(), to+1);
    }
    else
    {
        beginMoveRows(QModelIndex(), from, from, QModelIndex(), to);
    }

    qSwap(listOfTiles[from], listOfTiles[to]);
    endMoveRows();
}

void MyModel::activate(int cIndex) {
    if(cIndex < 0 || cIndex >= listOfTiles.size()) {
        return;
    }

    if (cIndex+1 < listOfTiles.size() && listOfTiles[cIndex+1].value() == 0)
    {
        if (cIndex/4 == (cIndex+1)/4)
        {
            move(cIndex, cIndex+1);
            //            printModel();
            checkForVictory();
            return;
        }

    }

    if (cIndex-1 >= 0 && listOfTiles[cIndex-1].value() == 0)
    {
        if (cIndex/4 == (cIndex-1)/4)
        {
            move(cIndex, cIndex-1);
            //            printModel();
            checkForVictory();
            return;
        }
    }

    if (cIndex-4 >= 0 && listOfTiles[cIndex-4].value() == 0)
    {
        for (int i = 0; i < 4; i++)
        {
            move(cIndex, cIndex-1);
            cIndex -= 1;
        }
        cIndex += 1;

        for (int i = 0; i < 3; i++)
        {
            move(cIndex, cIndex+1);
            cIndex += 1;
        }
        //        printModel();
        checkForVictory();
        return;
    }

    if (cIndex+4 < listOfTiles.size() && listOfTiles[cIndex+4].value() == 0)
    {
        for (int i = 0; i < 4; i++)
        {
            move(cIndex, cIndex+1);
            cIndex += 1;
        }
        cIndex -= 1;

        for (int i = 0; i < 3; i++)
        {
            move(cIndex, cIndex-1);
            cIndex -= 1;
        }
        //        printModel();
        checkForVictory();
        return;
    }
}


