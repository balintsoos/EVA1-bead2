#ifndef MINEFIELDMODEL_H
#define MINEFIELDMODEL_H

#include <QObject>

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

    void movePlayer(int x, int y);
    int getBoardSize() { return _boardSize; }

    //Field getField(int x, int y);

signals:
    void gameWon();
    void gameLost();
    void refresh();

private:
    Field** createGameBoard(int boardSize);
    void setPlayer(int x, int y);
    int random(int barrier);
    Coordinate* generateValidRandom(int barrier);

    int _boardSize;
    Coordinate* _player;
    Field** _gameBoard;

};

#endif // MINEFIELDMODEL_H
