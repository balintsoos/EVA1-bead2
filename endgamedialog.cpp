#include "endgamedialog.h"

EndGameDialog::EndGameDialog(QString message, QWidget *parent) :
    _message(message), QDialog(parent)
{
    setFixedSize(300,120);
    setWindowTitle(trUtf8("You Won!"));
    setModal(true);

    _label = new QLabel();
    updateLabel();

    _newGameButton = new QPushButton(trUtf8("New Game"));
    _newGameButton->setFixedSize(100, 25); // a gombok mérete rögzített
    _quitButton = new QPushButton(trUtf8("Quit"));
    _quitButton->setFixedSize(75, 25);

    connect(_newGameButton, SIGNAL(clicked()), this, SLOT(accept())); // elfogadás állapota
    connect(_quitButton, SIGNAL(clicked()), this, SLOT(reject())); // elvetés állapota

    QVBoxLayout *upperLayout = new QVBoxLayout();
    upperLayout->addWidget(_label, 0, Qt::AlignHCenter);

    QHBoxLayout *lowerLayout = new QHBoxLayout();
    lowerLayout->addWidget(_newGameButton);
    lowerLayout->addWidget(_quitButton);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(upperLayout);
    mainLayout->addLayout(lowerLayout);

    setLayout(mainLayout);
}

void EndGameDialog::setLabel(QString message)
{
    _message = message;
    updateLabel();
}

void EndGameDialog::updateLabel()
{
    _label->setText(_message);
}

void EndGameDialog::start()
{
    exec();
}
