#include "minefieldwidget.h"
#include <QApplication>

// for testing purposes
#include <iostream>

MinefieldWidget::MinefieldWidget(QWidget *parent)
    : QWidget(parent)
{
    // Widget
    setWindowTitle(trUtf8("Minefield Game"));

    // Dialogs
    _newGameDialog = new NewGameDialog();
    connect(_newGameDialog, SIGNAL(startNewGame(GameData)), this, SLOT(newGame(GameData)));

    _endGameDialog = new EndGameDialog();
    connect(_endGameDialog, SIGNAL(newGame()), _newGameDialog, SLOT(exec()));
    connect(_endGameDialog, SIGNAL(quitGame()), this, SLOT(quitGame()));

    // Buttons
    _newGameButton = new QPushButton(trUtf8("New Game"));
    connect(_newGameButton, SIGNAL(clicked()), _newGameDialog, SLOT(exec()));

    _saveGameButton = new QPushButton(trUtf8("Save"));
    _saveGameButton->setEnabled(false); // disable button
    connect(_saveGameButton, SIGNAL(clicked()), this, SLOT(saveGame()));

    _loadGameButton = new QPushButton(trUtf8("Load"));
    connect(_loadGameButton, SIGNAL(clicked()), this, SLOT(loadGame()));

    _quitButton = new QPushButton(trUtf8("Quit"));
    connect(_quitButton, SIGNAL(clicked()), this, SLOT(quitGame()));

    // Model
    _model = new MinefieldModel();
    connect(_model, SIGNAL(gameWon()), _endGameDialog, SLOT(won()));
    connect(_model, SIGNAL(gameLost()), _endGameDialog, SLOT(lost()));

    // Layout
    _vBoxLayout = new QVBoxLayout();
    _vBoxLayout->addWidget(_newGameButton);
    _vBoxLayout->addWidget(_saveGameButton);
    _vBoxLayout->addWidget(_loadGameButton);
    _vBoxLayout->addWidget(_quitButton);

    _gridLayout = new QGridLayout();
    _vBoxLayout->addLayout(_gridLayout);

    setLayout(_vBoxLayout);
}

MinefieldWidget::~MinefieldWidget()
{
    delete _newGameDialog;
    delete _endGameDialog;
}

void MinefieldWidget::newGame(GameData gameData)
{
    _model->newGame(gameData);
}

void MinefieldWidget::saveGame()
{
    _model->saveGame();
}

void MinefieldWidget::loadGame()
{
    _model->loadGame();
}

void MinefieldWidget::quitGame()
{
    QApplication::quit();
}

void MinefieldWidget::resetGame()
{

}

void MinefieldWidget::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
    case Qt::Key_Up :
        _model->movePlayer(-1, 0);
        break;
    case Qt::Key_Right :
        _model->movePlayer(0, 1);
        break;
    case Qt::Key_Down :
        _model->movePlayer(1, 0);
        break;
    case Qt::Key_Left :
        _model->movePlayer(0, -1);
        break;
    }
}
