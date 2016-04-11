#include "minefieldmodel.h"

MinefieldModel::MinefieldModel(QObject *parent)
    : QObject(parent)
{

}

void MinefieldModel::newGame(GameData gameData)
{
    _boardSize = gameData.getBoard();
    _gameBoard = createGameBoard(_boardSize);
    _gameBoard[1][(int)_boardSize / 2] = Player;

    int numberOfChasers = gameData.getChasers();
    int numberOfMines = gameData.getMines();

    int lastRow = _boardSize + 1;
    int lastColumn = _boardSize;

    for (int i = 1; i <= (int)numberOfChasers / 2; i++) {
        _gameBoard[lastRow - i][1] = Chaser;
        _gameBoard[lastRow - i][lastColumn] = Chaser;
    }

    for (int i = 1; i <= numberOfMines; i++) {
        Coordinate* mine = generateValidRandom(_boardSize);
        _gameBoard[mine->x()][mine->y()] = Mine;
    }
}

void MinefieldModel::saveGame()
{

}

void MinefieldModel::loadGame()
{

}

MinefieldModel::Field** MinefieldModel::createGameBoard(int boardSize)
{
    Field** board = new Field*[boardSize];

    for (int i = 1; i <= boardSize; ++i)
    {
        board[i] = new Field[boardSize];
    }

    return board;
}

Coordinate* MinefieldModel::generateValidRandom(int barrier)
{
    int x = random(barrier);
    int y = random(barrier);

    if (_gameBoard[x][y] != Empty )
    {
        return generateValidRandom(barrier);
    }
    else
    {
        return new Coordinate(x, y);
    }
}

int MinefieldModel::random(int barrier)
{
    return (qrand() % barrier) + 1;
}
