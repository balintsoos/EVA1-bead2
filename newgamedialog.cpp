#include "newgamedialog.h"

NewGameDialog::NewGameDialog(QWidget *parent) :
    QDialog(parent)
{
    // Widget
    setFixedSize(300, 180);
    setWindowTitle(trUtf8("New Game"));
    setModal(true); // előugró ablak, rögtön megkapja a fókuszt

    // Elements
    _gridSizeLabel = new QLabel(trUtf8("Gameboard size: "));
    _gridSizeSpinBox = new QSpinBox();
    _gridSizeSpinBox->setRange(11, 21);
    _gridSizeSpinBox->setSingleStep(1);

    _numberOfChasersLabel = new QLabel(trUtf8("Number of Chasers: "));
    _numberOfChasersSpinBox = new QSpinBox();
    _numberOfChasersSpinBox->setRange(2, 10);
    _numberOfChasersSpinBox->setSingleStep(2);
    _numberOfChasersSpinBox->setEnabled(false); // disable spinbox

    _numberOfMinesLabel = new QLabel(trUtf8("Number of Mines: "));
    _numberOfMinesSpinBox = new QSpinBox();
    _numberOfMinesSpinBox->setRange(1, 10);
    _numberOfMinesSpinBox->setSingleStep(1);
    _numberOfMinesSpinBox->setValue(5);
    _numberOfMinesSpinBox->setEnabled(false); // disable spinbox

    // Buttons
    _startGameButton = new QPushButton(trUtf8("Start game"));
    _startGameButton->setFixedSize(100, 25); // a gombok mérete rögzített
    connect(_startGameButton, SIGNAL(clicked()), this, SLOT(sendGameData())); // elfogadás állapota

    _cancelButton = new QPushButton(trUtf8("Cancel"));
    _cancelButton->setFixedSize(75, 25);
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(reject())); // elvetés állapota

    // Layout
    gridSizeLayout = new QHBoxLayout();
    gridSizeLayout->addWidget(_gridSizeLabel);
    gridSizeLayout->addWidget(_gridSizeSpinBox);

    chasersLayout = new QHBoxLayout();
    chasersLayout->addWidget(_numberOfChasersLabel);
    chasersLayout->addWidget(_numberOfChasersSpinBox);

    minesLayout = new QHBoxLayout();
    minesLayout->addWidget(_numberOfMinesLabel);
    minesLayout->addWidget(_numberOfMinesSpinBox);

    buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(_startGameButton);
    buttonLayout->addWidget(_cancelButton);

    mainLayout = new QVBoxLayout();
    mainLayout->addLayout(gridSizeLayout);
    mainLayout->addLayout(chasersLayout);
    mainLayout->addLayout(minesLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

void NewGameDialog::sendGameData()
{
    GameData gameData;
    gameData.setBoard(_gridSizeSpinBox->value());
    gameData.setChasers(_numberOfChasersSpinBox->value());
    gameData.setMines(_numberOfMinesSpinBox->value());

    emit startNewGame(gameData);
    this->close();
}
