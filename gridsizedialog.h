#ifndef GRIDSIZEDIALOG_H
#define GRIDSIZEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class GridSizeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit GridSizeDialog(QWidget *parent = 0);
    int getGridSize() { return _spinBox->value(); }

private:
    QHBoxLayout *upperLayout;
    QVBoxLayout *mainLayout;

    QLabel *_label;
    QSpinBox *_spinBox;
    QPushButton *_okButton;
    QPushButton *_cancelButton;
};

#endif // GRIDSIZEDIALOG_H
