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
    explicit EndGameDialog(QString message = "You won the game", QWidget *parent = 0);
    void setLabel(QString message);
    void start();

private:
    void updateLabel();

    QString _message;
    QLabel *_label;
    QPushButton *_newGameButton;
    QPushButton *_quitButton;
};

#endif // ENDGAMEDIALOG_H
