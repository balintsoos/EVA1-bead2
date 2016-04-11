#ifndef MINEFIELDWIDGET_H
#define MINEFIELDWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>

#include <QVector>

#include "minefieldmodel.h"
#include "gridsizedialog.h"
#include "endgamedialog.h"

class MinefieldWidget : public QWidget
{
    Q_OBJECT

public:
    MinefieldWidget(QWidget *parent = 0);
    ~MinefieldWidget();

private slots:
    //void step();
    //void resizeGrid();
    //void setGridSize();

    //void model_gameWon(MinefieldModel::Cell cell);
    //void model_gameOver();
    //void model_fieldChanged(int x, int y, MinefieldModel::Cell cell);

private:
    int _gridSize;

    QGridLayout* _gridLayout;
    QVBoxLayout* _vBoxLayout;

    GridSizeDialog* _gridSizeDialog; // méretbeállító ablak
    EndGameDialog* _endGameDialog;

    QPushButton* _newGameButton;
    QPushButton* _saveGameButton;
    QPushButton* _loadGameButton;
    QPushButton* _settingsButton; // átméretező gomb
    QPushButton* _quitButton;

    void setGridSize();
    void resizeGrid();

    //MinefieldModel _model;

};

#endif // MINEFIELDWIDGET_H
