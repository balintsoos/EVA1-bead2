#include "minefieldwidget.h"
#include <QApplication>

MinefieldWidget::MinefieldWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(trUtf8("Minefield Game"));

    _gridSize = 11;
    _gridSizeDialog = new GridSizeDialog();
    connect(_gridSizeDialog, SIGNAL(accepted()), this, SLOT(setGridSize()));

    _endGameDialog = new EndGameDialog();
    connect(_endGameDialog, SIGNAL(accepted()), this, SLOT(resizeGrid()));
    connect(_endGameDialog, SIGNAL(rejected()), QApplication::instance(), SLOT(quit()));

    _newGameButton = new QPushButton(trUtf8("New Game"));
    connect(_newGameButton, SIGNAL(clicked()), this, SLOT(resizeGrid()));

    _saveGameButton = new QPushButton(trUtf8("Save"));

    _loadGameButton = new QPushButton(trUtf8("Load"));

    _settingsButton = new QPushButton(trUtf8("Settings"));
    connect(_settingsButton, SIGNAL(clicked()), _gridSizeDialog, SLOT(exec()));

    _quitButton = new QPushButton(trUtf8("Quit"));
    connect(_quitButton, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));

    _vBoxLayout = new QVBoxLayout();
    _vBoxLayout->addWidget(_newGameButton);
    _vBoxLayout->addWidget(_settingsButton);
    _vBoxLayout->addWidget(_quitButton);

    _gridLayout = new QGridLayout();
    _vBoxLayout->addLayout(_gridLayout);

    setLayout(_vBoxLayout);
}

MinefieldWidget::~MinefieldWidget()
{
    delete _gridSizeDialog;
    delete _endGameDialog;
}

void MinefieldWidget::setGridSize()
{
   _gridSize = _gridSizeDialog->getGridSize();
   resizeGrid();
}

void MinefieldWidget::resizeGrid()
{
    //TODO
}
