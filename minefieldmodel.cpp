#include "minefieldmodel.h"

MinefieldModel::MinefieldModel(QObject *parent)
    : QObject(parent)
{
    qsrand(QTime::currentTime().msec());
    _timer = new QTimer();
    connect(_timer, SIGNAL(timeout()), this, SLOT(moveChasers()));
}

void MinefieldModel::newGame(GameData gameData)
{   
    if (_timer->isActive())
    {
        _timer->stop();
    }

    _boardSize = gameData.getBoard();
    _gameBoard = createGameBoard(_boardSize);

    int numberOfMines = gameData.getMines();
    int lastRow = _boardSize - 1;
    int lastColumn = _boardSize - 1;

    _player = new Coordinate(0, qCeil(lastColumn / 2.0));
    setPlayer(_player->x(), _player->y());

    _gameBoard[lastRow][0] = Chaser;
    _gameBoard[lastRow][lastColumn] = Chaser;

    for (int i = 1; i <= numberOfMines; i++) {
        Coordinate* mine = generateValidRandom(_boardSize);
        _gameBoard[mine->x()][mine->y()] = Mine;
    }

    _timer->start(1000);
}

void MinefieldModel::saveGame()
{

}

void MinefieldModel::loadGame()
{

}

Field** MinefieldModel::createGameBoard(int boardSize)
{
    Field** board = new Field*[boardSize];

    for (int i = 0; i < boardSize; ++i)
    {
        board[i] = new Field[boardSize];
        for (int j = 0; j < boardSize; ++j)
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

    if (newX >= 0 && newX < _boardSize &&
        newY >= 0 && newY < _boardSize)
    {
        if (_gameBoard[newX][newY] != Empty)
        {
            if(_timer->isActive())
            {
                _timer->stop();
            }
            emit gameLost();
            return;
        }
        else
        {
            setPlayer(newX, newY);
        }

    }

    emit refresh();
}

void MinefieldModel::setPlayer(int x, int y)
{
    _gameBoard[_player->x()][_player->y()] = Empty;
    _player->x(x);
    _player->y(y);
    _gameBoard[_player->x()][_player->y()] = Player;
}

void MinefieldModel::moveChasers()
{
    QVector<Coordinate*> chasers = getChasers();
    QVector<Coordinate*> mines = getMines();

    if (chasers.length() == 0)
    {
        if(_timer->isActive())
        {
            _timer->stop();
        }
        emit gameWon();
        return;
    }

    foreach (Coordinate* chaser, chasers) {
        int x = chaser->x();
        int y = chaser->y();
        int newX = x;
        int newY = y;

        if (x > _player->x()) {
            newX = x - 1;
        }
        if (x < _player->x()) {
            newX = x + 1;
        }
        if (y > _player->y()) {
            newY = y - 1;
        }
        if (y < _player->y()) {
            newY = y + 1;
        }

        chaser->x(newX);
        chaser->y(newY);
    }

    checkCollisions(chasers, mines);

    foreach (Coordinate* chaser, chasers) {
        delete chaser;
    }
    chasers.clear();

    foreach (Coordinate* mine, mines) {
        delete mine;
    }
    mines.clear();

    emit refresh();
}

void MinefieldModel::checkCollisions(QVector<Coordinate*> chasers, QVector<Coordinate*> mines)
{
    for (int i = 0; i < chasers.length(); i++)
    {
        int x = chasers[i]->x();
        int y = chasers[i]->y();

        if (x == _player->x() && y == _player->y())
        {
            if(_timer->isActive())
            {
                _timer->stop();
            }
            emit gameLost();
            return;
        }

        bool isCollide = false;

        foreach (Coordinate* mine, mines)
        {
            if (x == mine->x() && y == mine->y())
            {
                isCollide = true;
            }
        }

        for (int j = 0; j < chasers.length(); j++)
        {
            if (j != i && x == chasers[j]->x() && y == chasers[j]->y())
            {
                isCollide = true;
            }
        }

        if (!isCollide)
        {
            _gameBoard[x][y] = Chaser;
        }
    }
}

QVector<Coordinate*> MinefieldModel::getChasers()
{
    QVector<Coordinate*> chasers;

    for (int x = 0; x < _boardSize; ++x)
    {
        for (int y = 0; y < _boardSize; ++y)
        {
            if (_gameBoard[x][y] == Chaser)
            {
                chasers.push_back(new Coordinate(x, y));
                _gameBoard[x][y] = Empty;
            }
        }
    }

    return chasers;
}

QVector<Coordinate*> MinefieldModel::getMines()
{
    QVector<Coordinate*> mines;

    for (int x = 0; x < _boardSize; ++x)
    {
        for (int y = 0; y < _boardSize; ++y)
        {
            if (_gameBoard[x][y] == Mine)
            {
                mines.push_back(new Coordinate(x, y));
            }
        }
    }

    return mines;
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
    return (qrand() % barrier);
}
