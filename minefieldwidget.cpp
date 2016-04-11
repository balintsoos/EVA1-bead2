#include "minefieldwidget.h"
#include <QApplication>

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
    _saveGameButton->setEnabled(false);

    _loadGameButton = new QPushButton(trUtf8("Load"));

    _quitButton = new QPushButton(trUtf8("Quit"));
    connect(_quitButton, SIGNAL(clicked()), this, SLOT(quitGame()));

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

void MinefieldWidget::quitGame()
{
    QApplication::quit();
}

void MinefieldWidget::newGame(GameData gameData)
{
    _newGameButton->setText(QString::number(gameData.getBoard()));
}
