#ifndef MINEFIELDMODEL_H
#define MINEFIELDMODEL_H

#include <QObject>
#include <QGenericMatrix>

#include "gamedata.h"
#include "coordinate.h"

class MinefieldModel : public QObject
{
    Q_OBJECT
public:
    enum Field { Empty, Player, Chaser, Mine };

    MinefieldModel(QObject *parent = 0);

    void newGame(GameData gameData);
    void saveGame();
    void loadGame();

    Field getField(int x, int y);

signals:
    void gameWon();
    void gameLost();

private:
    Field** createGameBoard(int boardSize);
    int random(int barrier);
    Coordinate* generateValidRandom(int barrier);

    int _boardSize;
    Field** _gameBoard;

};

#endif // MINEFIELDMODEL_H
