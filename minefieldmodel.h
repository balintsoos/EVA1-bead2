#ifndef MINEFIELDMODEL_H
#define MINEFIELDMODEL_H

#include <QObject>
#include <QVector>
#include <QTime>
#include <QtMath>

#include "gamedata.h"
#include "coordinate.h"
#include "field.h"

class MinefieldModel : public QObject
{
    Q_OBJECT
public:
    MinefieldModel(QObject *parent = 0);

    void newGame(GameData gameData);
    void saveGame();
    void loadGame();
    int getBoardSize() { return _boardSize; }
    Field getField(int x, int y) { return _gameBoard[x][y]; }

signals:
    void gameWon();
    void gameLost();
    void refresh();

public slots:
    void movePlayer(int x, int y);
    void moveChasers();

private:
    QVector<Coordinate *> getChasers();
    QVector<Coordinate *> getMines();
    void checkCollisions(QVector<Coordinate*> chasers, QVector<Coordinate*> mines);
    Field** createGameBoard(int boardSize);
    Coordinate* generateValidRandom(int barrier);
    void setPlayer(int x, int y);

    // Helper functions
    int random(int barrier);

    int _boardSize;
    Coordinate* _player;
    Field** _gameBoard;
};

#endif // MINEFIELDMODEL_H
