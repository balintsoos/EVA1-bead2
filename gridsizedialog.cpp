#include "gridsizedialog.h"

GridSizeDialog::GridSizeDialog(QWidget *parent) :
    QDialog(parent)
{
    setFixedSize(300,100);
    setWindowTitle(trUtf8("Settings"));
    setModal(true); // előugró ablak, rögtön megkapja a fókuszt

    _label = new QLabel(trUtf8("Number of rows and colums: "));
    _spinBox = new QSpinBox();
    _spinBox->setRange(11, 21);
    _spinBox->setSingleStep(1);

    _okButton = new QPushButton(trUtf8("OK"));
    _okButton->setFixedSize(75, 25); // a gombok mérete rögzített
    _cancelButton = new QPushButton(trUtf8("Cancel"));
    _cancelButton->setFixedSize(75, 25);

    connect(_okButton, SIGNAL(clicked()), this, SLOT(accept())); // elfogadás állapota
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(reject())); // elvetés állapota

    QHBoxLayout *upperLayout = new QHBoxLayout();
    upperLayout->addWidget(_label);
    upperLayout->addWidget(_spinBox);

    QHBoxLayout *lowerLayout = new QHBoxLayout();
    lowerLayout->addWidget(_okButton);
    lowerLayout->addWidget(_cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(upperLayout);
    mainLayout->addLayout(lowerLayout);

    setLayout(mainLayout);
}
