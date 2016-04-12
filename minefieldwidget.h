#ifndef MINEFIELDWIDGET_H
#define MINEFIELDWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVector>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QKeyEvent>

#include "newgamedialog.h"
#include "endgamedialog.h"
#include "minefieldmodel.h"
#include "gamedata.h"

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

    QVector<QVector<QPushButton*>> _gameBoard;

    // Layout
    QVBoxLayout* _vBoxLayout;
    QGridLayout* _gameBoardLayout;

    void createGameBoard(int boardSize);

    // Keypress handler
    void keyPressEvent(QKeyEvent* event);
};

#endif // MINEFIELDWIDGET_H
