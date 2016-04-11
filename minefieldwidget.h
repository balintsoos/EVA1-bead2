#ifndef MINEFIELDWIDGET_H
#define MINEFIELDWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>

#include "newgamedialog.h"
#include "endgamedialog.h"
#include "gamedata.h"
#include "minefieldmodel.h"

class MinefieldWidget : public QWidget
{
    Q_OBJECT

public:
    MinefieldWidget(QWidget *parent = 0);
    ~MinefieldWidget();

private slots:
    void newGame(GameData gameData);
    void saveGame();
    void loadGame();
    void quitGame();

    //void model_gameWon(MinefieldModel::Cell cell);
    //void model_gameOver();
    //void model_fieldChanged(int x, int y, MinefieldModel::Cell cell);

private:
    // Model
    MinefieldModel* _model;

    // Dialogs
    NewGameDialog* _newGameDialog;
    EndGameDialog* _endGameDialog;

    // Buttons
    QPushButton* _newGameButton;
    QPushButton* _saveGameButton;
    QPushButton* _loadGameButton;
    QPushButton* _quitButton;

    // Layout
    QGridLayout* _gridLayout;
    QVBoxLayout* _vBoxLayout;
};

#endif // MINEFIELDWIDGET_H
