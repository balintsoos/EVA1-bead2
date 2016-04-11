#ifndef MINEFIELDWIDGET_H
#define MINEFIELDWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
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
    void resetGame();

    void movePlayer(int direction);

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

    // Keypress handler
    void keyPressEvent(QKeyEvent* event);
};

#endif // MINEFIELDWIDGET_H
