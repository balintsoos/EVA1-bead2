#ifndef MINEFIELDMODEL_H
#define MINEFIELDMODEL_H

#include <QObject>

class MinefieldModel : public QObject
{
    Q_OBJECT
public:
    explicit MinefieldModel(QObject *parent = 0);
    virtual ~MinefieldModel();
    void newGame();

signals:
    void gameWon();
    void gameOver();

private:
    int** gameTable;
};

#endif // MINEFIELDMODEL_H
