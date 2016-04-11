#ifndef NEWGAMEDIALOG_H
#define NEWGAMEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "gamedata.h"

class NewGameDialog : public QDialog
{
    Q_OBJECT
public:
    explicit NewGameDialog(QWidget *parent = 0);

signals:
    void startNewGame(GameData gameData);

private slots:
    void sendGameData();

private:
    // Elements
    QLabel *_gridSizeLabel;
    QSpinBox *_gridSizeSpinBox;

    QLabel *_numberOfChasersLabel;
    QSpinBox *_numberOfChasersSpinBox;

    QLabel *_numberOfMinesLabel;
    QSpinBox *_numberOfMinesSpinBox;

    // Buttons
    QPushButton *_startGameButton;
    QPushButton *_cancelButton;

    // Layout
    QHBoxLayout *gridSizeLayout;
    QHBoxLayout *chasersLayout;
    QHBoxLayout *minesLayout;
    QHBoxLayout *buttonLayout;
    QVBoxLayout *mainLayout;
};

#endif // NEWGAMEDIALOG_H
