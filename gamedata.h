#ifndef GAMEDATA_H
#define GAMEDATA_H

struct GameData
{
public:
    GameData() :
        _boardSize(0),
        _numberOfChasers(0),
        _numberOfMines(0) {}

    GameData(int board, int chasers, int mines) :
        _boardSize(board),
        _numberOfChasers(chasers),
        _numberOfMines(mines) {}

    int getBoard() { return _boardSize; }
    int getChasers() { return _numberOfChasers; }
    int getMines() { return _numberOfMines; }

    void setBoard(int board) { _boardSize = board; }
    void setChasers(int chasers) { _numberOfChasers = chasers; }
    void setMines(int mines) { _numberOfMines = mines; }

private:
    int _boardSize;
    int _numberOfChasers;
    int _numberOfMines;
};

#endif // GAMEDATA_H
