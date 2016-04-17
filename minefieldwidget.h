#ifndef MINEFIELDWIDGET_H
#define MINEFIELDWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVector>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QKeyEvent>
#include <QTimer>

#include "newgamedialog.h"
#include "endgamedialog.h"
#include "minefieldmodel.h"
#include "gamedata.h"
#include "field.h"

class MinefieldWidget : public QWidget
{
    Q_OBJECT

public:
    MinefieldWidget(QWidget *parent = 0);
    ~MinefieldWidget();

signals:
    void keypress(int x, int y);
    void moveChasers();

private slots:
    void newGame(GameData gameData);
    void saveGame();
    void loadGame();
    void quitGame();
    void won();
    void lost();
    void pauseHandler();
    void refreshGameBoard();

private:
    void pauseGame();
    void resumeGame();
    void createGameBoard(int boardSize);
    QString getFieldValue(int x, int y);

    // Keypress handler
    void keyPressEvent(QKeyEvent* event);

    // Model
    MinefieldModel* _model;

    // Dialogs
    NewGameDialog* _newGameDialog;
    EndGameDialog* _endGameDialog;

    // Chasers' timer
    QTimer* _timer;

    // Pause
    bool _gamePaused = false;

    // Buttons
    QPushButton* _newGameButton;
    QPushButton* _saveGameButton;
    QPushButton* _loadGameButton;
    QPushButton* _quitButton;
    QPushButton* _pauseButton;

    QVector<QVector<QPushButton*> > _gameBoard;

    // Layout
    QVBoxLayout* _vBoxLayout;
    QGridLayout* _gameBoardLayout;
};

#endif // MINEFIELDWIDGET_H
