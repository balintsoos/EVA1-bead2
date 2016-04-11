#ifndef MINEFIELDWIDGET_H
#define MINEFIELDWIDGET_H

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include <QGridLayout>

class MinefieldWidget : public QWidget
{
    Q_OBJECT

public:
    MinefieldWidget(QWidget *parent = 0);
    ~MinefieldWidget();
};

#endif // MINEFIELDWIDGET_H
