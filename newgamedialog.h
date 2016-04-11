#ifndef NEWGAMEDIALOG_H
#define NEWGAMEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class NewGameDialog : public QDialog
{
    Q_OBJECT
public:
    explicit NewGameDialog(QWidget *parent = 0);
    int getGridSize() { return _spinBox->value(); }

private:
    // Elements
    QLabel *_label;
    QSpinBox *_spinBox;

    // Buttons
    QPushButton *_startGameButton;
    QPushButton *_cancelButton;

    // Layout
    QHBoxLayout *upperLayout;
    QHBoxLayout *lowerLayout;
    QVBoxLayout *mainLayout;
};

#endif // NEWGAMEDIALOG_H
