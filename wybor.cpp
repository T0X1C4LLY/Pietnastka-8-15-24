#include "wybor.h"
#include <QApplication>

Wybor::Wybor(QWidget *parent) : QWidget(parent){
    setWindowTitle("8/15/24");
    resize(300,100);

    do24 = new QPushButton("5x5");
    do15 = new QPushButton("4x4");
    do8 = new QPushButton("3x3");

    QLabel *label = new QLabel("\tWybierz poziom trudnosci");

    grupa = new QGroupBox("",this);
    grupa->setGeometry(QRect(0,5,300,95));

    QVBoxLayout *boxLayout = new QVBoxLayout;
    QHBoxLayout *boxLayout2 = new QHBoxLayout;

    boxLayout->addWidget(label);
    boxLayout2->addWidget(do8);
    boxLayout2->addWidget(do15);
    boxLayout2->addWidget(do24);

    boxLayout->addLayout(boxLayout2);

    grupa->setLayout(boxLayout);

    connect(do24,SIGNAL(released()),this,SLOT(graj24()));
    connect(do15,SIGNAL(released()),this,SLOT(graj15()));
    connect(do8,SIGNAL(released()),this,SLOT(graj8()));
}

Wybor::~Wybor(){

}

void Wybor::graj15(){
    m = new MyWindow();
    m->show();
    this->close();
}

void Wybor::graj8(){
    m2 = new MyWindow2();
    m2->show();
    this->close();
}

void Wybor::graj24(){
    m3 = new MyWindow3();
    m3->show();
    this->close();
}
