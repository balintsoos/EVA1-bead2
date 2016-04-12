#include "minefieldwidget.h"
#include <QApplication>

// for testing purposes
#include <iostream>

MinefieldWidget::MinefieldWidget(QWidget *parent)
    : QWidget(parent)
{
    // Widget
    setWindowTitle(trUtf8("Minefield Game"));
    setMinimumWidth(350);

    // Dialogs
    _newGameDialog = new NewGameDialog();
    connect(_newGameDialog, SIGNAL(startNewGame(GameData)), this, SLOT(newGame(GameData)));

    _endGameDialog = new EndGameDialog();
    connect(_endGameDialog, SIGNAL(newGame()), _newGameDialog, SLOT(show()));
    connect(_endGameDialog, SIGNAL(newGame()), this, SLOT(loadGame()));
    connect(_endGameDialog, SIGNAL(quitGame()), this, SLOT(quitGame()));

    // Buttons
    _newGameButton = new QPushButton(trUtf8("New Game"));
    _newGameButton->setFocusPolicy(Qt::NoFocus);
    connect(_newGameButton, SIGNAL(clicked()), _newGameDialog, SLOT(show()));

    _saveGameButton = new QPushButton(trUtf8("Save"));
    _saveGameButton->setFocusPolicy(Qt::NoFocus);
    _saveGameButton->setEnabled(false); // disable button
    connect(_saveGameButton, SIGNAL(clicked()), this, SLOT(saveGame()));

    _loadGameButton = new QPushButton(trUtf8("Load"));
    _loadGameButton->setFocusPolicy(Qt::NoFocus);
    connect(_loadGameButton, SIGNAL(clicked()), this, SLOT(loadGame()));

    _quitButton = new QPushButton(trUtf8("Quit"));
    _quitButton->setFocusPolicy(Qt::NoFocus);
    connect(_quitButton, SIGNAL(clicked()), this, SLOT(quitGame()));

    // Gameboard
    _gameBoardLayout = new QGridLayout();

    // Model
    _model = new MinefieldModel();
    connect(_model, SIGNAL(gameWon()), _endGameDialog, SLOT(won()));
    connect(_model, SIGNAL(gameLost()), _endGameDialog, SLOT(lost()));
    connect(_model, SIGNAL(refresh()), this, SLOT(refreshGameBoard()));
    connect(this, SIGNAL(keypress(int, int)), _model, SLOT(movePlayer(int, int)));

    // Layout
    _vBoxLayout = new QVBoxLayout();
    _vBoxLayout->addWidget(_newGameButton);
    _vBoxLayout->addWidget(_saveGameButton);
    _vBoxLayout->addWidget(_loadGameButton);
    _vBoxLayout->addWidget(_quitButton);
    _vBoxLayout->addLayout(_gameBoardLayout);

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

    createGameBoard(_model->getBoardSize());
    _saveGameButton->setEnabled(true);
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

void MinefieldWidget::createGameBoard(int boardSize)
{   
    _gameBoard.clear();
    _gameBoard.resize(boardSize);

    for (int i = 0; i < boardSize; ++i)
    {
        _gameBoard[i].clear();
        _gameBoard[i].resize(boardSize);
        for (int j = 0; j < boardSize; ++j)
        {
            _gameBoard[i][j]= new QPushButton(this);
            _gameBoard[i][j]->setFocusPolicy(Qt::NoFocus);
            _gameBoard[i][j]->setText(getFieldValue(i + 1, j + 1));
            _gameBoard[i][j]->setMinimumWidth(30);
            _gameBoard[i][j]->setMinimumHeight(30);
            _gameBoard[i][j]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

            _gameBoardLayout->addWidget(_gameBoard[i][j], i, j); // gombok felvétele az elhelyezésbe
        }
    }
}

void MinefieldWidget::refreshGameBoard()
{
    int boardSize = _model->getBoardSize();

    for (int i = 0; i < boardSize; ++i)
    {
        for (int j = 0; j < boardSize; ++j)
        {
            _gameBoard[i][j]->setText(getFieldValue(i + 1, j + 1));
        }
    }
}

QString MinefieldWidget::getFieldValue(int x, int y)
{
    Field field = _model->getField(x, y);

    switch(field)
    {
    case Empty :
        return QString::fromStdString("");
        break;
    case Player :
        return QString::fromStdString("P");
        break;
    case Chaser :
        return QString::fromStdString("C");
        break;
    case Mine :
        return QString::fromStdString("M");
        break;
    }
}

void MinefieldWidget::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
    case Qt::Key_Up :
        emit keypress(-1, 0);
        break;
    case Qt::Key_Right :
        emit keypress(0, 1);
        break;
    case Qt::Key_Down :
        emit keypress(1, 0);
        break;
    case Qt::Key_Left :
        emit keypress(0, -1);
        break;
    }
}
