#ifndef MINEFIELDMODEL_H
#define MINEFIELDMODEL_H

#include <QObject>

class MinefieldModel : public QObject
{
    Q_OBJECT
public:
    enum Cell { Empty, Player, Chaser, Mine };

    MinefieldModel(QObject *parent = 0);

    //void newGame();
    //void step();
    //Cell getCell(int x, int y);

signals:
    //void gameWon();
    //void gameOver();
    //void cellChanged(int x, int y, Cell cell);

private:
    //Cell** gameTable;
};

#endif // MINEFIELDMODEL_H
