#include "newgamedialog.h"

NewGameDialog::NewGameDialog(QWidget *parent) :
    QDialog(parent)
{
    // Widget
    setFixedSize(300,100);
    setWindowTitle(trUtf8("New Game"));
    setModal(true); // előugró ablak, rögtön megkapja a fókuszt

    // Elements
    _label = new QLabel(trUtf8("Number of rows and colums: "));
    _spinBox = new QSpinBox();
    _spinBox->setRange(11, 21);
    _spinBox->setSingleStep(1);

    // Buttons
    _startGameButton = new QPushButton(trUtf8("OK"));
    _startGameButton->setFixedSize(75, 25); // a gombok mérete rögzített
    connect(_startGameButton, SIGNAL(clicked()), this, SLOT(accept())); // elfogadás állapota

    _cancelButton = new QPushButton(trUtf8("Cancel"));
    _cancelButton->setFixedSize(75, 25);
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(reject())); // elvetés állapota

    // Layout
    upperLayout = new QHBoxLayout();
    upperLayout->addWidget(_label);
    upperLayout->addWidget(_spinBox);

    lowerLayout = new QHBoxLayout();
    lowerLayout->addWidget(_startGameButton);
    lowerLayout->addWidget(_cancelButton);

    mainLayout = new QVBoxLayout();
    mainLayout->addLayout(upperLayout);
    mainLayout->addLayout(lowerLayout);

    setLayout(mainLayout);
}
