#include "minefieldmodel.h"

MinefieldModel::MinefieldModel(QObject *parent)
    : QObject(parent)
{

}

void MinefieldModel::newGame(GameData gameData)
{
    _boardSize = gameData.getBoard();
    _gameBoard = createGameBoard(_boardSize);

    _player = new Coordinate(1, (int)_boardSize / 2);
    setPlayer(_player->x(), _player->y());

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
        for (int j = 1; j <= boardSize; ++j)
        {
            board[i][j] = Empty;
        }
    }

    return board;
}

void MinefieldModel::movePlayer(int x, int y)
{
    int newX = _player->x() + x;
    int newY = _player->y() + y;

    if (newX >= 1 && newX <= _boardSize &&
        newY >= 1 && newY <= _boardSize)
    {
        setPlayer(newX, newY);
    }
}

void MinefieldModel::setPlayer(int x, int y)
{
    _gameBoard[_player->x()][_player->y()] = Empty;
    _player->x(x);
    _player->y(y);
    _gameBoard[_player->x()][_player->y()] = Player;
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
