#include "endgamedialog.h"

EndGameDialog::EndGameDialog(QWidget *parent) :
    QDialog(parent)
{
    // Widget
    setFixedSize(300,120);
    setWindowTitle("Game Over");
    setModal(true);

    // Elements
    _label = new QLabel();

    // Buttons
    _newGameButton = new QPushButton(trUtf8("New Game"));
    _newGameButton->setFixedSize(100, 25); // a gombok mérete rögzített
    connect(_newGameButton, SIGNAL(clicked()), this, SLOT(start()));

    _loadGameButton = new QPushButton(trUtf8("Load"));
    _loadGameButton->setFixedSize(75, 25);
    connect(_loadGameButton, SIGNAL(clicked()), this, SLOT(load()));

    _quitButton = new QPushButton(trUtf8("Quit"));
    _quitButton->setFixedSize(75, 25);
    connect(_quitButton, SIGNAL(clicked()), this, SLOT(quit()));

    // Layout
    upperLayout = new QVBoxLayout();
    upperLayout->addWidget(_label, 0, Qt::AlignHCenter);

    lowerLayout = new QHBoxLayout();
    lowerLayout->addWidget(_newGameButton);
    lowerLayout->addWidget(_loadGameButton);
    lowerLayout->addWidget(_quitButton);

    mainLayout = new QVBoxLayout();
    mainLayout->addLayout(upperLayout);
    mainLayout->addLayout(lowerLayout);

    setLayout(mainLayout);
}

void EndGameDialog::won()
{
    _label->setText("You won the game");
    exec();
}

void EndGameDialog::lost()
{
    _label->setText("You lost the game");
    exec();
}

void EndGameDialog::start()
{
    emit newGame();
    close();
}

void EndGameDialog::load()
{
    emit loadGame();
    close();
}

void EndGameDialog::quit()
{
    emit quitGame();
    close();
}
