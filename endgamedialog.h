#ifndef ENDGAMEDIALOG_H
#define ENDGAMEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class EndGameDialog : public QDialog
{
    Q_OBJECT
public:
    explicit EndGameDialog(QString message = "Game Over", QWidget *parent = 0);
    void setLabel(QString message);

signals:
    void newGame();
    void quitGame();

private:
    // Elements
    QString _message;
    QLabel *_label;

    // Buttons
    QPushButton *_newGameButton;
    QPushButton *_quitButton;

    // Layout
    QVBoxLayout *upperLayout;
    QHBoxLayout *lowerLayout;
    QVBoxLayout *mainLayout;
};

#endif // ENDGAMEDIALOG_H
