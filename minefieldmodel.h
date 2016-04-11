#ifndef MINEFIELDMODEL_H
#define MINEFIELDMODEL_H

#include <QObject>
#include <QVector>

#include "gamedata.h"
#include "coordinate.h"

class MinefieldModel : public QObject
{
    Q_OBJECT
public:
    MinefieldModel(QObject *parent = 0);
    ~MinefieldModel();

    void newGame(GameData gameData);
    void saveGame();
    void loadGame();

signals:
    void gameWon();
    void gameLost();

private:
    void resetGame();

    int _boardSize;
    Coordinate _player;
    QVector<Coordinate> _chasers;
    QVector<Coordinate> _mines;

};

#endif // MINEFIELDMODEL_H
