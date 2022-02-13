#ifndef WYBOR_H
#define WYBOR_H

#include <QAbstractItemModel>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include "mainwindow2.h"
#include "mainwindow3.h"

class Wybor : public QWidget{
    Q_OBJECT

public:
    Wybor(QWidget *parent = 0);
    ~Wybor();

private:
    QPushButton *do24;
    QPushButton *do15;
    QPushButton *do8;
    QGroupBox *grupa;
    MyWindow *m;
    MyWindow2 *m2;
    MyWindow3 *m3;

private slots:
    void graj24();
    void graj15();
    void graj8();
};

#endif // WYBOR_H
