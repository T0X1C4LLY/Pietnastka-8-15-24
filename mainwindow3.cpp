//Źródło kodu z algorytmem IDA*: https://github.com/quantumelixir/1524

#include "mainwindow3.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTest>

using namespace std;

MyWindow3::MyWindow3(QWidget *parent) : QWidget(parent){
    setWindowTitle("24");
    szer = 720;
    wys = 720;
    resize(szer+300,wys);
    img = new QImage(szer,wys,QImage::Format_RGB32);
    img2 = new QImage(szer,wys,QImage::Format_RGB32);

    //obrazy - ukladane obrazki, boki - "material" klockow
    obrazy[0] = new QImage(":/img/Images/1.jpg");
    obrazy[1] = new QImage(":/img/Images/2.jpg");
    obrazy[2] = new QImage(":/img/Images/3.jpg");
    boki[0] = new QImage(":/img/Images/side1.jpg");
    boki[1] = new QImage(":/img/Images/side2.jpg");
    boki[2] = new QImage(":/img/Images/side3.jpg");
    setMouseTracking(true);

    grupa = new QGroupBox("Sterowanie",this);
    grupa2 = new QGroupBox("Podglad",this);
    grupa3 = new QGroupBox("Opcje",this);
    grupa4 = new QGroupBox("Pomoc",this);
    grupa5 = new QGroupBox("Wynik",this);

    grupa->setGeometry(QRect(szer,5,300,65));
    grupa2->setGeometry(QRect(szer,70,300,65));
    grupa3->setGeometry(QRect(szer,140,300,165));
    grupa4->setGeometry(QRect(szer,320,300,110));
    grupa5->setGeometry(QRect(szer,430,300,110));

    QHBoxLayout *boxLayout = new QHBoxLayout;
    QVBoxLayout *boxLayout2 = new QVBoxLayout;
    QVBoxLayout *boxLayout3 = new QVBoxLayout;
    QVBoxLayout *boxLayout4 = new QVBoxLayout;
    QVBoxLayout *boxLayout5 = new QVBoxLayout;

    QHBoxLayout *boxLayoutH1 = new QHBoxLayout;
    QHBoxLayout *boxLayoutH2 = new QHBoxLayout;

    label1 = new QLabel("Czas");
    label2 = new QLabel("Ruchy");
    labelTime = new QLabel("0:0");
    labelMove = new QLabel("0");

    timeText = new QPlainTextEdit();
    moveText = new QPlainTextEdit();

    podglad = new QSlider(Qt::Horizontal);

    QIcon up_icon(":/img/Images/up_arrow.png");
    QSize pom = up_icon.availableSizes().constFirst();
    up = new QPushButton();
    up->setFixedSize(pom);
    up->setIcon(up_icon);
    up->setIconSize(pom);

    QIcon down_icon(":/img/Images/down_arrow.png");
    down = new QPushButton();
    down->setFixedSize(pom);
    down->setIcon(down_icon);
    down->setIconSize(pom);

    QIcon left_icon(":/img/Images/left_arrow.png");
    left = new QPushButton();
    left->setFixedSize(pom);
    left->setIcon(left_icon);
    left->setIconSize(pom);

    QIcon right_icon(":/img/Images/right_arrow.png");
    right = new QPushButton();
    right->setFixedSize(pom);
    right->setIcon(right_icon);
    right->setIconSize(pom);

    losuj = new QPushButton("Mieszaj");
    zmien = new QPushButton("Zmien obraz");
    zmien2 = new QPushButton("Zmien material");
    uloz = new QPushButton("Rozwiaz");
    pomoc = new QPushButton("Ogolne informacje");
    pomoc2 = new QPushButton("Jak ulozyc?");

    podglad->setRange(0,100);
    podglad->setValue(0);

    boxLayout->addWidget(left);
    boxLayout->addWidget(up);
    boxLayout->addWidget(down);
    boxLayout->addWidget(right);

    boxLayout2->addWidget(podglad);
    boxLayout3->addWidget(losuj);
    boxLayout3->addWidget(zmien);
    boxLayout3->addWidget(zmien2);
    boxLayout3->addWidget(uloz);

    boxLayout4->addWidget(pomoc);
    boxLayout4->addWidget(pomoc2);

    boxLayoutH1->addWidget(label1);
    boxLayoutH1->addWidget(label2);

    boxLayoutH2->addWidget(labelTime);
    boxLayoutH2->addWidget(labelMove);

    boxLayout5->addLayout(boxLayoutH1);
    boxLayout5->addLayout(boxLayoutH2);

    grupa->setLayout(boxLayout);
    grupa2->setLayout(boxLayout2);
    grupa3->setLayout(boxLayout3);
    grupa4->setLayout(boxLayout4);
    grupa5->setLayout(boxLayout5);

    message = new QMessageBox();

    message->setWindowTitle("Zwyciestwo");
    message->setText("GRATULACJE !!!");

    message2 = new QMessageBox();
    message2->setWindowTitle("Ogolne informacje");
    message2->setText("ZASADY: \nGra polega na ulozeniu ukladanki w jak najmniejszej liczbie krokow\n"
    "Przy pomocy przyciskow ze strzalakami poruszamy klocki w odpowiednim kierunku. Przesuwac mozna jedynie na puste pole,"
    "co oznacza, ze np. klikniecie przycisku ze strzalka w lewo (odpowiednio klawisza A) sprawi, ze klocek po prawej od pustego \n"
    "zostanie przesuniety w lewo a nie ze \"pusty\" klocek zostanie przesuniety w lewo.\n"
    "\n\nSTEROWANIE:\nPrzyciski ze strzalkami: pozwalaja przesuwac klocki\n"
    "Mozliwe jest takze poruszanie przy pomocy klawiszy: W A S D.\n"
    "\n\nDODATKOWE OPCJE:\nSuwak z sekcji podglad: pozwala podejrzec ukladany obraz, mozliwe jest jednoczesne podgladanie obrazka i ukladanie klockow\n"
    "\nMieszaj: rozpoczyna nowa rozgrywke ustawiajac klocki w losowych miejscach\n"
    "\nZmien obraz: pozwala zmienic ukladany obraz jednoczesnie rozpoczynajac nowa rozgrywke\n"
    "\nZmien material: pozwala zmienic material z jakiego sa zbudowane klocki, nie rozpoczyna to rozgrywki na nowo\n"
    "\nRozwiaz: rozwiazuje ukladanke.\n"
    "\nUwaga: Mozliwe jest ulozenie ukladanki w rozny sposob (w mniejszej lub wiekszej ilosci ruchow), zaprezentowane rozwiazanie "
    "NIE jest optymalne - wykonywanych jest wiecej ruchow niz jest to w praktyce konieczne");

    message3 = new QMessageBox();
    message3->setWindowTitle("Jak ulozyc?");
    message3->setText("METODA 1: najpierw wiersze potem kolumny\n"
    "1. Ustawiamy pierwszy, drugi i trzeci klocek pierwszego wiersza na swoich miejscach\n"
    "2. Ustawiamy klocek czwarty na miejscu piatego a piaty na miejscu dziewiatego\n"
    "(lub klocek piaty na miejscu czwartego a czwarty na miejscu osmego)"
    "i manewrujemy tak by ulozyc je na swoje miejsca\n"
    "3. Punkty 1 i 2 powtarzamy na drugiego i trzeciego wiersza\n"
    "4. Teraz ustawiamy pierwsza, druga i trzecia kolumne do konca\n"
    "5. Manewrujemy az ulozymy obrazek\n\n"
    "METODA 2: wiersz-kolumna\n"
    "1. Ustawiamy pierwszy wiersz na takich samych zasadach jak w pierwszej metodzie.\n"
    "2. Teraz zamiast ukladac drugi wiersz ukladamy pierwsza kolumne tak by zredukowac puzzle do ukladu 4x4."
    " Przy ustawianiu ostatnich klockow mozna zastosowac sztuczke z punktu 2 metody 1 (oczywiscie odpowiednio zmodyfikowana)\n"
    "3. Powtazramy punkt 1 i 2 dla drugiego wiersza i drugiej kolumny a nastepnie dla trzeciego wiersza i trzeciej kolumny\n"
    "4. Manewrujemy klockami az ulozymy obrazek");

    timer = new QTimer();
    timer->setInterval(1000);

    connect(podglad,SIGNAL(valueChanged(int)),this,SLOT(Wartosc(int)));
    connect(up,SIGNAL(released()),this,SLOT(upWrapper()));
    connect(down,SIGNAL(released()),this,SLOT(downWrapper()));
    connect(left,SIGNAL(released()),this,SLOT(leftWrapper()));
    connect(right,SIGNAL(released()),this,SLOT(rightWrapper()));
    connect(zmien,SIGNAL(clicked()),this,SLOT(zmianaObrazu()));
    connect(zmien2,SIGNAL(clicked()),this,SLOT(zmianaMaterialu()));
    connect(losuj,SIGNAL(clicked()),this,SLOT(losujWrapper()));
    connect(uloz,SIGNAL(clicked()),this,SLOT(rozwiaz()));
    connect(pomoc,SIGNAL(clicked()),this,SLOT(pomocWrapper()));
    connect(pomoc2,SIGNAL(clicked()),this,SLOT(pomoc2Wrapper()));
    connect(timer,SIGNAL(timeout()),this,SLOT(timerWrapper()));

    sekundy = 0;
    minuty = 0 ;
    zegar = false;
    timer->start();

    //Poczatkowe ustawienie klockow 5x5
    int p=157;
    punkty2[0].wspolrzedne[0].x = 0;
    punkty2[0].wspolrzedne[0].y = p;
    punkty2[0].wspolrzedne[0].z = 3*p;

    punkty2[0].wspolrzedne[1].x = p;
    punkty2[0].wspolrzedne[1].y = p;
    punkty2[0].wspolrzedne[1].z = 3*p;

    punkty2[0].wspolrzedne[2].x = p;
    punkty2[0].wspolrzedne[2].y = 0;
    punkty2[0].wspolrzedne[2].z = 3*p;

    punkty2[0].wspolrzedne[3].x = 0;
    punkty2[0].wspolrzedne[3].y = 0;
    punkty2[0].wspolrzedne[3].z = 3*p;

    punkty2[0].wspolrzedne[4].x = 0;
    punkty2[0].wspolrzedne[4].y = p;
    punkty2[0].wspolrzedne[4].z = 4*p;

    punkty2[0].wspolrzedne[5].x = p;
    punkty2[0].wspolrzedne[5].y = p;
    punkty2[0].wspolrzedne[5].z = 4*p;

    punkty2[0].wspolrzedne[6].x = p;
    punkty2[0].wspolrzedne[6].y = 0;
    punkty2[0].wspolrzedne[6].z = 4*p;

    punkty2[0].wspolrzedne[7].x = 0;
    punkty2[0].wspolrzedne[7].y = 0;
    punkty2[0].wspolrzedne[7].z = 4*p;

    for(int i=1;i<5;i++){
        for(int j=0;j<8;j++){
            punkty2[i].wspolrzedne[j].x = punkty2[i-1].wspolrzedne[j].x+p;
            punkty2[i].wspolrzedne[j].y = punkty2[i-1].wspolrzedne[j].y;
            punkty2[i].wspolrzedne[j].z = punkty2[i-1].wspolrzedne[j].z;
        }
    }
    for(int i=5;i<25;i++){
        for(int j=0;j<8;j++){
            punkty2[i].wspolrzedne[j].x = punkty2[i-5].wspolrzedne[j].x;
            punkty2[i].wspolrzedne[j].y = punkty2[i-5].wspolrzedne[j].y+p;
            punkty2[i].wspolrzedne[j].z = punkty2[i-5].wspolrzedne[j].z;
        }
    }

    losowanie();

    int pomoc=144;
    for(int i=0;i<25;i++){
        punktyTekstura[i].lewy[0].x=(i%5)*pomoc;
        punktyTekstura[i].lewy[0].y=(i/5)*pomoc;

        punktyTekstura[i].lewy[1].x= punktyTekstura[i].lewy[0].x;
        punktyTekstura[i].lewy[1].y= punktyTekstura[i].lewy[0].y + pomoc;

        punktyTekstura[i].lewy[2].x= punktyTekstura[i].lewy[1].x + pomoc;
        punktyTekstura[i].lewy[2].y= punktyTekstura[i].lewy[1].y;

        punktyTekstura[i].prawy[0].x= punktyTekstura[i].lewy[0].x + pomoc;
        punktyTekstura[i].prawy[0].y= punktyTekstura[i].lewy[0].y;

        punktyTekstura[i].prawy[1].x= punktyTekstura[i].lewy[2].x;
        punktyTekstura[i].prawy[1].y= punktyTekstura[i].lewy[2].y;

        punktyTekstura[i].prawy[2].x= punktyTekstura[i].lewy[0].x;
        punktyTekstura[i].prawy[2].y= punktyTekstura[i].lewy[0].y;
    }

    rotacjaX.macierz[1][1] = (double)cos(30 * M_PI / 180.0);
    rotacjaX.macierz[1][2] = (double)sin(30 * M_PI / 180.0);
    rotacjaX.macierz[2][1] = (double)-sin(30 * M_PI / 180.0);
    rotacjaX.macierz[2][2] = (double)cos(30 * M_PI / 180.0);

    przesuniecie.macierz[0][3]=-360;
    przesuniecie.macierz[1][3]=-400;

    nrImage=0;
    nrMat=0;
    recznie=1;
    ruchy = 0;
    licznik_pom = 0;
    wartoscAlfa = 0;

    for(int i=0;i<25;i++){
        przydzielTeksture(i);
    }


    //ustalenie oswietlenia we wszystkich wiercholkach ukladanego obrazka
    przerysuj();
    for(int i = 0;i<25;i++){
        for(int j=0; j<25; j++){
            if(board[i] == j){
                oswietlenieWierzcholki(punkty[j].wspolrzedne[3],punkty[j].wspolrzedne[0],punkty[j].wspolrzedne[1],true);
                if(i % 5 == 4){
                    oswietlenieWierzcholki(punkty[j].wspolrzedne[2],punkty[j].wspolrzedne[3],punkty[j].wspolrzedne[1],true);
                }
                break;
            }
        }
    }
    for(int i = 20; i<25;i++){
        for(int j=0; j<25; j++){
            if(board[i] == j){
                oswietlenieWierzcholki(punkty[j].wspolrzedne[0],punkty[j].wspolrzedne[1],punkty[j].wspolrzedne[3],true);
                if(i == 24){
                    oswietlenieWierzcholki(punkty[j].wspolrzedne[1],punkty[j].wspolrzedne[2],punkty[j].wspolrzedne[3],true);
                }
                break;
            }
        }
    }
    przerysuj();
    alfa();
}

MyWindow3::~MyWindow3(){
    delete img;
    delete img2;
    delete obrazy[0];
    delete obrazy[1];
    delete obrazy[2];
    delete boki[0];
    delete boki[1];
    delete boki[2];
}

void MyWindow3::keyPressEvent( QKeyEvent * event ){

    //Sterowanie WASD
    if( event->key() == Qt::Key_A ){
        left->click();
    }
    else if( event->key() == Qt::Key_D ){
        right->click();
    }
    else if( event->key() == Qt::Key_W ){
        up->click();
    }
    else if( event->key() == Qt::Key_S ){
        down->click();
    }
}

void MyWindow3::szescian(int index){
     //Nalozenie tekstur na sciany boczne

    //Prawa
    if(widoczna(punkty[index].wspolrzedne[1],punkty[index].wspolrzedne[5],punkty[index].wspolrzedne[2])){
        nalozTekstureBok(index,1);
    }
    //Lewa
    if(widoczna(punkty[index].wspolrzedne[4],punkty[index].wspolrzedne[0],punkty[index].wspolrzedne[7])){
        nalozTekstureBok(index,0);
    }
    //Dolna
    nalozTekstureBok(index,2);
}

void MyWindow3::paintEvent(QPaintEvent*){
    QPainter p(this);
    p.drawImage(0,0,*img2);
}

//losowanie ukladu
void MyWindow3::losowanie(){
    srand (time(NULL));
    int tab[25];
    bool flaga;
    do{
        for(int i=0;i<25;i++){
            flaga=1;
            while(flaga){
                flaga=0;
                tab[i] = rand() % 25;
                for(int j=0;j<i;j++){
                    if(tab[i]==tab[j]){
                        flaga=1;
                    }
                }
            }
        }
        for (int i=0; i<25;i++ ) {
            punkty[i].nr = tab[i];
        }
    }
    while(!rozwiazywalna());
    for(int i = 0; i < 25; i++){
        for(int j = 0; j < 25 ; j++){
            if(punkty[j].nr == i){
                board[i] = j;
            }
        }
    }
    pusty = tab[24];
}

//ustalanie nowych wspolrzednych klockow z uwzglednieniem persektywy i usatwienia z widowkiem 3D
void MyWindow3::przerysuj(){
    Macierz glowna;
    glowna=rotacjaX*przesuniecie;
    for(int i=0;i<25;i++){
        for(int j=0;j<8;j++){
            punkty[i].wspolrzedne[j].x=punkty2[punkty[i].nr].wspolrzedne[j].x*glowna.macierz[0][0] + punkty2[punkty[i].nr].wspolrzedne[j].y*glowna.macierz[0][1] + punkty2[punkty[i].nr].wspolrzedne[j].z *glowna.macierz[0][2] + glowna.macierz[0][3];
            punkty[i].wspolrzedne[j].y=punkty2[punkty[i].nr].wspolrzedne[j].x*glowna.macierz[1][0] + punkty2[punkty[i].nr].wspolrzedne[j].y*glowna.macierz[1][1] + punkty2[punkty[i].nr].wspolrzedne[j].z *glowna.macierz[1][2] + glowna.macierz[1][3];
            punkty[i].wspolrzedne[j].z=punkty2[punkty[i].nr].wspolrzedne[j].x*glowna.macierz[2][0] + punkty2[punkty[i].nr].wspolrzedne[j].y*glowna.macierz[2][1] + punkty2[punkty[i].nr].wspolrzedne[j].z *glowna.macierz[2][2] + glowna.macierz[2][3];
            punkty[i].wspolrzedne[j].x = (( punkty[i].wspolrzedne[j].x * 2000) / (punkty[i].wspolrzedne[j].z + 2000) )+330;
            punkty[i].wspolrzedne[j].y = (( punkty[i].wspolrzedne[j].y * 2000) / (punkty[i].wspolrzedne[j].z + 2000) )+125;
        }
    }
    plansza();
}

//blokowanie przyciskow do przesuwania klockow
void MyWindow3::blokada(bool stan){
    ruchy = 0;
    up->setEnabled(stan);
    down->setEnabled(stan);
    left->setEnabled(stan);
    right->setEnabled(stan);
}

//Zamalowanie planszy na czarno
void MyWindow3::zamaluj(){
    unsigned char *ptr;
    ptr = img->bits();
    for(int i=40;i<676;i++){
        for(int j=6;j<714;j++){
            ptr[szer*4*i + 4*j]=0;
            ptr[szer*4*i + 4*j + 1] = 0;
            ptr[szer*4*i + 4*j + 2] = 0;
        }
    }
}

//Sprawdzenia widocznosci planszy
bool MyWindow3::widoczna(punkt p1, punkt p2, punkt p3){
    punkt widz;
    widz.x = (400-p1.x);
    widz.y = (360-p1.y);
    widz.z = (-3000-p1.z);

    punkt w;
    w.x = (p2.x-p1.x);
    w.y = (p2.y-p1.y);
    w.z = (p2.z-p1.z);

    punkt v;
    v.x = (p3.x-p1.x);
    v.y = (p3.y-p1.y);
    v.z = (p3.z-p1.z);

    punkt iloczyn;
    iloczyn.x = (w.y*v.z)-(v.y*w.z);
    iloczyn.y = (v.x*w.z)-(w.x*v.z);
    iloczyn.z = (w.x*v.y)-(v.x*w.y);

    double wynik = (iloczyn.x * widz.x) + (iloczyn.y * widz.y) + (iloczyn.z * widz.z);

    return (wynik>0) ? true : false;
}

//Znajdowanie minimum/maksimum na x/y
int MyWindow3::znajdzMin(punkt p1, punkt p2, punkt p3){
    return min(p1.y,min(p2.y,p3.y));
}
int  MyWindow3::znajdzMax(punkt p1, punkt p2, punkt p3){
    return max(p1.y,max(p2.y,p3.y));
}

int MyWindow3::znajdzMinX(punkt p1, punkt p2, punkt p3){
    return min(p1.x,min(p2.x,p3.x));
}
int  MyWindow3::znajdzMaxX(punkt p1, punkt p2, punkt p3){
    return max(p1.x,max(p2.x,p3.x));
}

//nakladanie tekstury na kostke
void MyWindow3::teksturowanie(punkt p1, punkt p2, punkt p3, int index,bool flaga, QImage* obraz, bool przod){
    float W;
    float Ww;
    float Wv;
    int x;
    int y;
    float v;
    float w;
    float u;
    unsigned char *ptr;
    ptr = img->bits();
    unsigned char *ptr2;
    ptr2 = obraz->bits();
    tablica.clear();

    tablica.push_back(make_pair((int)p1.x,(int)p1.y));
    tablica.push_back(make_pair((int)p2.x,(int)p2.y));
    tablica.push_back(make_pair((int)p3.x,(int)p3.y));

    double os;
    double Id;
    double If;

    //Wyznaczenie oswietlenia na wiercholkach ktore nie znajduja się na ukladanym obrazku
    if(flaga && !przod){
        oswietlenieWierzcholki(p1,p2,p3,false);
        oswietlenieWierzcholki(p1,p2,p3,false);
    }
    else if(!flaga && !przod){
        oswietlenieWierzcholki(p1,p3,p2,false);
        oswietlenieWierzcholki(p1,p3,p2,false);
    }

    for(int i=znajdzMin(p1,p2,p3);i<=znajdzMax(p1,p2,p3);i++){
        W=(p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);

        //Znajdowanie przeciec danego y z krawedziami trojkata i wyzanczenie oswietlenia w tych miejscach
        znajdzPrzeciecia(i);
        if(flaga && przod){
            Id = oswietlenie2(p1,p2,p3,true,true,index);
            If = oswietlenie2(p1,p2,p3,false,true,index);
        }
        else if(!flaga && przod){
            Id = oswietlenie2(p1,p3,p2,true,false,index);
            If = oswietlenie2(p1,p3,p2,false,false,index);
        }
        else if(flaga && !przod){
            Id = oswietlenie(p1,p2,p3,true,true);
            If = oswietlenie(p1,p2,p3,false,true);
        }
        else if(!flaga){
            Id = oswietlenie(p1,p3,p2,true,false);
            If = oswietlenie(p1,p3,p2,false,false);
        }
        for(int j=znajdzMinX(p1,p2,p3);j<=znajdzMaxX(p1,p2,p3);j++){
            Wv=(j - p1.x)*(p3.y - p1.y)-(i - p1.y)*(p3.x - p1.x);
            Ww=(p2.x - p1.x)*(i - p1.y)-(p2.y - p1.y)*(j - p1.x);
            v=(Wv/W);
            w=(Ww/W);
            u=1-v-w;

            if(u>=0 && u<=1 && v>=0 && v<=1 && w>=0 && w<=1){
                if(flaga){
                    x=(u * punkty[index].t.lewy[1].x) + (v * punkty[index].t.lewy[2].x) + (w * punkty[index].t.lewy[0].x);
                    y=(u * punkty[index].t.lewy[1].y) + (v * punkty[index].t.lewy[2].y) + (w * punkty[index].t.lewy[0].y);
                }
                else{
                    x=(u * punkty[index].t.prawy[0].x) + (v * punkty[index].t.prawy[1].x) + (w * punkty[index].t.prawy[2].x);
                    y=(u * punkty[index].t.prawy[0].y) + (v * punkty[index].t.prawy[1].y) + (w * punkty[index].t.prawy[2].y);
                }

                os = oswietlenieWartosc(Id,If,j);

                ptr[szer*4*i + 4*j] = ptr2[szer*4*y + 4*x] * os;
                ptr[szer*4*i + 4*j + 1] = ptr2[szer*4*y + 4*x + 1] * os;
                ptr[szer*4*i + 4*j + 2] = ptr2[szer*4*y + 4*x + 2] * os;
            }
        }
    }
}

//blendowanie obrazow
void MyWindow3::alfa(){
    unsigned char *ptr;
    ptr = img->bits();
    unsigned char *ptr2;
    ptr2 = obrazy[nrImage]->bits();
    unsigned char *ptr3;
    ptr3 = img2->bits();
    Kolor fg;
    Kolor bg;
    unsigned char cr=0;
    unsigned char cg=0;
    unsigned char cb=0;
    for(int i=0;i<obrazy[nrImage]->width();i++){
        for(int j=0;j<obrazy[nrImage]->height();j++){
            bg.b=ptr[szer*4*i + 4*j];
            bg.g=ptr[szer*4*i + 4*j + 1];
            bg.r=ptr[szer*4*i + 4*j + 2];
            fg.b=ptr2[szer*4*i + 4*j];
            fg.g=ptr2[szer*4*i + 4*j + 1];
            fg.r=ptr2[szer*4*i + 4*j + 2];

            cr = wartoscAlfa*fg.r+(1-wartoscAlfa)*bg.r;
            cg = wartoscAlfa*fg.g+(1-wartoscAlfa)*bg.g;
            cb = wartoscAlfa*fg.b+(1-wartoscAlfa)*bg.b;

            ptr3[szer*4*i + 4*j] = cb;
            ptr3[szer*4*i + 4*j + 1] = cg;
            ptr3[szer*4*i + 4*j + 2] = cr;
        }
    }
}

//zmiana podgladu ukladanego obrazka
void MyWindow3::Wartosc(int wartosc){
    wartoscAlfa=wartosc/(100.0);
    alfa();
    repaint();
}

//Ustawianie planszy - teksturowanie klockow w odpowiedniej kolejnosci
void MyWindow3::plansza(){
    int pom[25];
    for(int i = 0; i < 25; i++){
        for(int j = 0; j < 25 ; j++){
            if(punkty[j].nr == i){
                pom[i] = j;
            }
        }
    }
    for(int i=0;i<25;i++){
        if(pom[i]!=24 && i %5 < 2){
            szescian(pom[i]);
            nalozTeksturePrzod(pom[i]);
        }
    }
    for(int i=0;i<25;i++){
        if(pom[i]!=24 && i %5 == 4){
            szescian(pom[i]);
            nalozTeksturePrzod(pom[i]);
        }
    }
    for(int i=0;i<25;i++){
        if(pom[i]!=24 && i %5 == 3){
            szescian(pom[i]);
            nalozTeksturePrzod(pom[i]);
        }
    }
    for(int i=0;i<25;i++){
        if(pom[i]!=24 && i %5 == 2){
            szescian(pom[i]);
            nalozTeksturePrzod(pom[i]);
        }
    }
    for(int i=0;i<24;i++){
        nalozTeksture(i);
    }
}

//Wyswietlenie wiadomosci z ogolnymi informacjami
void MyWindow3::pomocWrapper(){
    message2->exec();
}

//wyswietlenie wiadomosci ze sposoabmi ukladania puzzli
void MyWindow3::pomoc2Wrapper(){
    message3->exec();
}

//przesuwanie w gore
void MyWindow3::upWrapper(){
    if(pusty<20){
        zegar = true;
        up->setDisabled(true);
        przesun(0);
        up->setDisabled(false);
    }
}

//przesuwanie w dol
void MyWindow3::downWrapper(){
    if(pusty>4){
        zegar = true;
        down->setDisabled(true);
        przesun(1);
        down->setDisabled(false);
    }
}

//przesuwanie w lewo
void MyWindow3::leftWrapper(){
    if(pusty%5 != 4){
        zegar = true;
        left->setDisabled(true);
        przesun(3);
        left->setDisabled(false);
    }
}

//przesuwanie w prawo
void MyWindow3::rightWrapper(){
    if(pusty%5 != 0){
        zegar = true;
        right->setDisabled(true);
        przesun(2);
        right->setDisabled(false);
    }
}

//zmiana ukladanego obrazka
void MyWindow3::zmianaObrazu(){
    nrImage = (nrImage+1)%3;
    losujWrapper();
}

//przydzielanie klockom ich tekstur
void MyWindow3::przydzielTeksture(int index){

    punkty[index].t.lewy[0].x=punktyTekstura[index].lewy[0].x;
    punkty[index].t.lewy[0].y=punktyTekstura[index].lewy[0].y;

    punkty[index].t.lewy[1].x=punktyTekstura[index].lewy[1].x;
    punkty[index].t.lewy[1].y=punktyTekstura[index].lewy[1].y;

    punkty[index].t.lewy[2].x=punktyTekstura[index].lewy[2].x;
    punkty[index].t.lewy[2].y=punktyTekstura[index].lewy[2].y;

    punkty[index].t.prawy[0].x=punktyTekstura[index].prawy[0].x;
    punkty[index].t.prawy[0].y=punktyTekstura[index].prawy[0].y;

    punkty[index].t.prawy[1].x=punktyTekstura[index].prawy[1].x;
    punkty[index].t.prawy[1].y=punktyTekstura[index].prawy[1].y;

    punkty[index].t.prawy[2].x=punktyTekstura[index].prawy[2].x;
    punkty[index].t.prawy[2].y=punktyTekstura[index].prawy[2].y;

}

//nakladanie tekstury na gorna scianke
void MyWindow3::nalozTeksture(int index){
    teksturowanie(punkty[index].wspolrzedne[0],punkty[index].wspolrzedne[1],punkty[index].wspolrzedne[3],index,1,obrazy[nrImage],1);
    teksturowanie(punkty[index].wspolrzedne[2],punkty[index].wspolrzedne[1],punkty[index].wspolrzedne[3],index,0,obrazy[nrImage],1);
}

//nakladanie tekstury na boczne scianki
void MyWindow3::nalozTekstureBok(int index, int opcja){
    if(opcja == 0){
        teksturowanie(punkty[index].wspolrzedne[4],punkty[index].wspolrzedne[0],punkty[index].wspolrzedne[7],index,1,boki[nrMat],0);
        teksturowanie(punkty[index].wspolrzedne[3],punkty[index].wspolrzedne[0],punkty[index].wspolrzedne[7],index,0,boki[nrMat],0);
    }
    else{
        teksturowanie(punkty[index].wspolrzedne[1],punkty[index].wspolrzedne[5],punkty[index].wspolrzedne[2],index,1,boki[nrMat],0);
        teksturowanie(punkty[index].wspolrzedne[6],punkty[index].wspolrzedne[5],punkty[index].wspolrzedne[2],index,0,boki[nrMat],0);
    }
}

//nakladanie tekstury na przednia scianke
void MyWindow3::nalozTeksturePrzod(int index){
    teksturowanie(punkty[index].wspolrzedne[4],punkty[index].wspolrzedne[5],punkty[index].wspolrzedne[0],index,1,boki[nrMat],0);
    teksturowanie(punkty[index].wspolrzedne[1],punkty[index].wspolrzedne[5],punkty[index].wspolrzedne[0],index,0,boki[nrMat],0);
}

//losowanie nowego ukladu
void MyWindow3::losujWrapper(){
    sekundy = 0;
    minuty = 0;
    ruchy = 0;
    QString ru = QString::number(ruchy);
    labelMove->setText(ru);
    recznie = 1;
    blokada(true);
    zamaluj();
    losowanie();
    przerysuj();
    alfa();
    repaint();
}

//przesuwanie klockow na planszy
void MyWindow3::przesun(int numer){
    //0 - w gore
    //1 - w dol
    //2 - w prawo
    //3 - w lewo
    if(recznie){
        ruchy++;
        QString ru = QString::number(ruchy);
        labelMove->setText(ru);
    }
    QTest::qWait(200);
    int nr;
    int pierwsza;
    int druga;

    if(numer==0){
        nr = pusty + 5;
    }
    else if(numer == 1){
        nr = pusty - 5;
    }
    else if(numer == 2){
        nr = pusty - 1;
    }
    else{
        nr = pusty + 1;
    }
    for(int i=0;i<25;i++){
        if(punkty[i].nr == nr){
            druga = i ;
        }
        else if(punkty[i].nr == pusty){
            pierwsza = i ;
        }
    }
    swap(punkty[pierwsza].wspolrzedne,punkty[druga].wspolrzedne);
    swap(punkty[pierwsza].nr,punkty[druga].nr);
    pusty = nr;
    for(int i = 0; i < 25; i++){
        for(int j = 0; j < 25 ; j++){
            if(punkty[j].nr == i){
                board[i] = j;
            }
        }
    }
    zamaluj();
    plansza();
    alfa();
    repaint();
    if(winner() && recznie){
        zegar = false;
        QString pom = QString::number(ruchy);
        QString pom1 = QString::number(minuty);
        QString pom2 = QString::number(sekundy);
        blokada(false);
        message->setInformativeText("Udalo Ci sie ulozyc ukladanke w : " + pom +" krokach.\nZajelo Ci to: " + pom1+ ":" + pom2);
        message->exec();
    }
}

//sprawdzanie rozwiazywalnosci ukladu
bool MyWindow3::rozwiazywalna(){
    int pom[5][5];
    for(int i = 0; i < 25; i++){
        for(int j = 0; j < 25 ; j++){
            if(punkty[j].nr == i){
                pom[i/5][i%5] = j;
            }
        }
    }
    int invCount = getInvCount((int*)pom);
    return (invCount%2 == 0);
}

int MyWindow3::getInvCount(int arr[]){
    int inv_count = 0;
    for (int i = 0; i < 24; i++){
        for (int j = i + 1; j < 25; j++){
            if (arr[j] != 24 && arr[i] != 24 && arr[i] > arr[j]){
                inv_count++;
            }
        }
    }
    return inv_count;
}

//zmiana "materialu" klockow
void MyWindow3::zmianaMaterialu(){
    nrMat = (nrMat+1)%3;
    zamaluj();
    plansza();
    if(winner()){
        nalozTeksturePrzod(24);
        nalozTeksture(24);
    }
    alfa();
    repaint();
}

//sprawdzanie czy puzzle zostaly ulozone
bool MyWindow3::winner(){
    for(int i = 0; i < 25; i++){
        if(board[i] != i){
            return false;
        }
    }
    nalozTeksturePrzod(24);
    nalozTeksture(24);
    alfa();
    repaint();
    return true;
}

//rozwiazywanie ukladanki
void MyWindow3::rozwiaz(){
    recznie = 0;
    zegar = false;
    blokuj(false);
    blokada(false);
    solve();
    algorytm();
    blokuj(true);
}

//blokada przyciskow na czas ukladania puzzli
void MyWindow3::blokuj(bool stan){
    uloz->setEnabled(stan);
    losuj->setEnabled(stan);
    zmien->setEnabled(stan);
    zmien2->setEnabled(stan);
}

//Ustawianie pierwszego rzedu klockow + 3 z 2 i 3 rzedu w celu uproszczenia ukladanki
void MyWindow3::solve(){
    int sx;
    int sy;
    int kolumna;
    int wiersz;
    int miejsce;
    int pozycja = -1;;
    //Jesli klocek nie jest na swoim miejscu
    for(int i=0;i<=14;i++){
        int px = (pusty%5);
        int py = (pusty/5);
        if(i == 11){
            i = 15;
        }
        else if(i == 12){
            i = 20;
        }
        else if(i == 13){
            i = 11;
        }
        else if(i == 14){
            i = 12;
        }
        for(int j=0;j<25;j++){
            if(board[j] == i){
                pozycja = j;
                break;
            }
        }

        sx = (pozycja%5);
        sy = (pozycja/5);
        kolumna = (i % 5);
        wiersz = (i / 5);
        miejsce = i;
        if(i%5 == 3){
            miejsce += 2;
            wiersz++;
            kolumna = 0;
        }
        else if(i%5 == 4){
            miejsce -= 1;
            kolumna -= 1;
        }
        else if(i == 15){
            miejsce = 11;
            kolumna = 1;
            wiersz = 2;
        }
        else if(i == 20){
            miejsce = 15;
            kolumna = 0;
            wiersz = 3;
        }
        if(i%5 == 3 && board[i] == i && board[i+1] == i+1){
            i++;
            break;
        }
        else if(i == 15 && board[i] == i && board[20] == 20){
            i = 12;
            break;
        }
        if(board[miejsce] != i){
            //przesuwanie klocka w dol jesli to konieczne
            if(sy < wiersz){
                if(py == sy){
                    while(sy != wiersz){
                        while((sx+1) < kolumna){
                            przesun(3);
                            px++;
                        }
                        przesun(0);
                        przesun(3);
                        px++;
                        przesun(1);
                        sy++;
                        if(sy != wiersz){
                            przesun(2);
                            px--;
                            przesun(0);
                            py++;
                        }
                    }
                }
                else{
                    while(sy != wiersz){
                        while(px != sx){
                            przesun(3);
                            px++;
                        }
                        while(py != sy){
                            przesun(1);
                            py--;
                        }
                        sy++;
                        if(sy != wiersz){
                            przesun(2);
                            px--;
                            przesun(0);
                            py++;
                        }
                    }
                }
            }
            //Ustawianie klocka na wlasciwa kolumne - ustawic pusty na lewo od szukanego
            if(sx != kolumna){
                //Jesli trzeba przesunac w lewo
                if(kolumna < sx){
                    //Jesli pusty jest ponad szukanym
                    if(py < sy && px < sx){
                        //Jesli pusty jest ponad i po lewej od szukanego
                        //Przesuwamy pustym w dol az do odpowiedniego wiersza
                        while(py != sy){
                            przesun(0);
                            py++;
                        }
                        while(px != sx){
                            przesun(3);
                            px++;
                        }
                        sx--;
                    }
                    //Jesli pusty jest po prawej i ponad szukanym
                    else if(py < sy && px > sx){
                        while(py < sy){
                            przesun(0);
                            py++;
                        }
                        while((px-1) > sx){
                            przesun(2);
                            px--;
                        }
                    }
                    //Jesli pusty jest ponad i na rowni z szukanym
                    else if(py < sy && px == sx){
                        while((py+1) < sy){
                            przesun(0);
                            py++;
                        }
                        if(sx < 4 && sy < 4){
                            przesun(3);
                            przesun(0);
                            przesun(0);
                            przesun(2);
                            przesun(2);
                            przesun(1);
                            py++;
                            przesun(3);
                            sx--;

                        }
                        else{
                            przesun(2);
                            przesun(0);
                            py++;
                            przesun(3);
                            sx--;
                        }
                    }
                    //Jesli pusty jest pod szukanym i po lewej
                    else if(py > sy && px<sx){
                        //Jesli pusty jest pod i po lewej od szukanego
                        //Przesuwamy pustym w bok az do odpowiedniej kolumny
                        while((px+1) < sx){
                            przesun(3);
                            px++;
                        }
                        while(py != sy){
                            przesun(1);
                            py--;
                        }
                        przesun(3);
                        px++;
                        sx--;
                    }
                    //Jesli pusty jest po prawej i pod szukanym
                    else if(py > sy && px > sx){
                        while(py != sy){
                            przesun(1);
                            py--;
                        }
                        while((px-1) != sx){
                            przesun(2);
                            px--;
                        }
                    }
                    //Jesli pusty jest pod i na rowni z szukanym
                    else if(py > sy && px == sx){
                        while((py-1) > sy){
                            przesun(1);
                            py--;
                        }
                        przesun(2);
                        przesun(1);
                        py--;
                        przesun(3);
                        sx--;
                    }
                    //jesli pusty i szukany sa na tym samym wierszu
                    else if(py == sy && px < sx){
                        //Jesli pusty po lewej i w tym samym wierszu
                        while(px != sx){
                            przesun(3);
                            px++;
                        }
                        sx--;
                    }
                    //Jesli pusty po prawej i w tym samym wierszu
                    else{
                        while((px-1) != sx){
                            przesun(2);
                            px--;
                        }
                    }
                    //ustawianie klocka do wlasciwej kolumny
                    while(sx != kolumna){
                        //Jesli to mozliwe przesuwamy dolem
                        if(sy < 4){
                            przesun(0);
                            przesun(2);
                            przesun(2);
                            przesun(1);
                            przesun(3);
                            px--;
                            sx--;
                        }
                        else{
                            przesun(1);
                            przesun(2);
                            przesun(2);
                            przesun(0);
                            przesun(3);
                            px--;
                            sx--;
                        }
                    }
                }
                //Jesli trzeba przesunac w prawo
                //TUTAJ USTAWIAMY PUSTY PO LEWEJ SZUKANEGO
                    //Jesli pusty jest ponad szukanym
                    else if(py < sy && px < sx){
                        //Jesli pusty jest ponad i po lewej od szukanego
                        //Przesuwamy pustym w dol az do odpowiedniego wiersza
                        while(py != sy){
                            przesun(0);
                            py++;
                        }
                        while((px+1) != sx){
                            przesun(3);
                            px++;
                        }
                    }
                    //Jesli pusty jest po prawej i ponad szukanym
                    else if(py < sy && px > sx){
                        while(py < sy){
                            przesun(0);
                            py++;
                        }
                        while(px != sx){
                            przesun(2);
                            px--;
                        }
                        sx++;
                    }
                    //Jesli pusty jest ponad i na rowni z szukanym
                    else if (py < sy && px == sx){
                        while((py+1) < sy){
                            przesun(0);
                            py++;
                        }
                        przesun(3);
                        przesun(0);
                        py++;
                        przesun(2);
                        sx++;
                    }
                    //Jesli pusty jest pod szukanym
                    else if(py > sy && px < sx){
                        //Jesli pusty jest pod i po lewej od szukanego
                        //Przesuwamy pustym w bok az do odpowiedniej kolumny
                        while(px-1 != sx){
                            przesun(3);
                            px++;
                        }
                        while(py != sy){
                            przesun(1);
                            py--;
                        }
                        przesun(2);
                        px--;
                        sx++;
                    }
                    //Jesli pusty jest po prawej i pod szukanym
                    else if(py > sy && px > sx){
                        while(py != sy){
                            przesun(1);
                            py--;
                        }
                        while(px != sx){
                            przesun(2);
                            px--;
                        }
                        sx++;
                    }
                    //Jesli pusty jest pod i na rowni z szukanym
                    else if(py > sy && px == sx){
                        while((py-1) > sy){
                            przesun(1);
                            py--;
                        }
                        przesun(3);
                        przesun(1);
                        py--;
                        przesun(2);
                        sx++;
                    }
                    //jesli pusty i szukany sa na tym samym wierszu
                    else if(py == sy && px < sx){
                        //Jesli pusty po lewej i w tym samym wierszu
                        while(px+1 < sx){
                            przesun(3);
                            px++;
                        }
                    }
                    //Jesli pusty po prawej i w tym samym wierszu
                    else{
                        while(px != sx){
                            przesun(2);
                            px--;
                        }
                        sx++;
                    }
                //ustawianie klocka do wlasciwej kolumny
                while(sx != kolumna){
                    //Jesli to mozliwe przesuwamy dolem
                    if(sy < 4){
                        przesun(0);
                        przesun(3);
                        przesun(3);
                        przesun(1);
                        przesun(2);
                        px++;
                        sx++;
                    }
                    else{
                        przesun(1);
                        przesun(3);
                        przesun(3);
                        przesun(0);
                        przesun(2);
                        px++;
                        sx++;
                    }
                }
            }

            //JESLI KLOCEK ZNAJDUJE SIE W SWOJEJ KOLUMNIE
            //jesli sa w tej samej kolumnie to przesun sie pustym w prawo
            if(px == sx){
                przesun(3);
                px++;
            }
            //dopoki klocek nie trafi na swoje miejsce
            while(sy != wiersz){
                //Jesli pusty jest nad klockiem to przesuwaj tak zeby byl o jeden ponad nim
                if(py < sy){
                    //jesli pusty jest nad i po lewej
                    while(py != (sy-1)){
                        przesun(0);
                        py++;
                    }

                    if(px < sx){
                        while(px <= sx){
                            przesun(3);
                            px++;
                        }
                    }
                    //Jesli pusty nad i po prawej
                    else if(px > sx){
                        while(px > sx){
                            przesun(2);
                            px--;
                        }
                    }
                }
                //Jesli pusty jest pod klockiem to przesuwaj tak zeby byl o jeden ponad nim
                else if (py > sy){
                    //Jesli pusty pod i po lewej
                    if(px < sx){
                        while(px <= sx){
                            przesun(3);
                            px++;
                        }
                        przesun(1);
                        przesun(1);
                        py-=2;
                    }
                    //Jesli pusty pod i po prawej
                    else if((px-1) > sx){
                        przesun(2);
                        px--;
                    }
                    while(py != (sy-1)){
                        przesun(1);
                        py--;
                    }
                }
                else{
                    //Jesli pusty w tym samym wierszu i po lewej
                    if(px < sx){
                        while((px+1) < sx){
                            przesun(3);
                            px++;
                        }
                        if(sy < 4){
                            przesun(0);
                            przesun(3);
                            przesun(3);
                            px+=2;
                            przesun(1);
                            przesun(1);
                            py--;
                        }
                        else{
                            przesun(1);
                            py--;
                            przesun(3);
                            przesun(3);
                            px+=2;
                        }
                    }
                    //Jesli pusty w tym samym wierszu i po prawej
                    else{
                        while((px-1) > sx){
                            przesun(2);
                            px--;
                        }
                        przesun(1);
                        py--;
                    }
                }
                //przesuwaj pustym w lewo dopoki nie bedziemy w odpowiedniej kolumnie
                while(px != sx){
                    przesun(2);
                    px--;
                }
                //przesuwaj pustym w dol dopoki nie zamienimy sie z klockiem
                for(;py<sy;py++){
                    przesun(0);
                }
                sy--;
                if(sy != wiersz){
                    przesun(3);
                    px++;
                }
            }
        }
        //Ustawianie 2 ostatnich klockow w wierszu
        if((i%5 == 4)){
            //Jesli pusty znajduje sie po prawej
            if((pusty/5) == wiersz && px==4){
                przesun(0);
                przesun(2);
                py++;
                px--;
            }
            else if(px != 3 || py-1 != wiersz){
                while(px != 3){
                    przesun(3);
                    px++;
                }
                while((py-1) != wiersz){
                    przesun(1);
                    py--;
                }
            }
            przesun(2);
            przesun(2);
            przesun(2);
            przesun(0);
            przesun(3);
            przesun(3);
            przesun(1);
            przesun(2);
            przesun(0);
            przesun(3);
            przesun(3);
            przesun(1);
            przesun(2);
            przesun(0);
            przesun(3);
            przesun(3);
            przesun(1);
            przesun(1);
            przesun(2);
            przesun(0);
        }

        //Ustawianie 2 ostatnich klockow w kolumnie
        if(i == 20){
            //Jesli pusty znajduje sie po prawej
            if((pusty / 5) == wiersz+1 && px == 0){
                przesun(3);
                przesun(1);
                py--;
                px++;
            }
            else if(px != 1 || py > wiersz){
                while(px != 1){
                    przesun(2);
                    px--;
                }
                while(py != wiersz){
                    przesun(1);
                    py--;
                }
            }
            else if(px != 1 || py < wiersz){
                while(px != 1){
                    przesun(2);
                    px--;
                }
                while(py != wiersz){
                    przesun(0);
                    py++;
                }
            }
            przesun(1);
            przesun(3);
            przesun(0);
            przesun(0);
            przesun(2);
            przesun(2);
            przesun(1);
            przesun(3);
        }
        if(i == 15){
            i = 11;
        }
        else if(i == 20){
            i = 12;
        }
        else if(i == 11){
            i = 13;
        }
        else if(i == 12){
            i = 14;
        }
    }
}

int MyWindow3::h(State &s) {
    int ret = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++) {
            if (s.x == i && s.y == j) {
                continue;
            }
            int v = s.board[i][j];
            int x = (v - 1)/4, y = (v - 1)%4;
            ret += abs(x-i) + abs(y-j);
        }
    }
    return ret;
}

bool MyWindow3::dfs(int depth) {
    int currcost = depth + h(node);
    if (currcost > costbound) {
        exceed = min(exceed, currcost);
        return false;
    }
    if (node == goal || nongoals.count(node) > 0) {
        return true;
    }

    visited.insert(node);

    for (map<pair<int, int>, char>::iterator it = moves.begin(); it != moves.end(); it++) {
        int dx = it->first.first, dy = it->first.second;
        if (0 <= node.x + dx && node.x + dx < 4 && 0 <= node.y + dy && node.y + dy < 4) {
            swap(node.board[node.x][node.y],
            node.board[node.x + dx][node.y + dy]);
            node.x += dx; node.y += dy;
            if (visited.count(node) == 0) {
                prefix.push_back(it->second);
                if (dfs(depth + 1)){
                    return true;
                }
                else{
                    prefix.pop_back();
                }
            }
            node.x -= dx; node.y -= dy;
            swap(node.board[node.x][node.y],
            node.board[node.x + dx][node.y + dy]);
        }
    }
    visited.erase(node);
    return false;
}

void MyWindow3::solve_idastar(State &start) {
    costbound = h(start);
    bool success;
    do {
        exceed = INT_MAX;
        prefix.clear();
        visited.clear();
        node = start;
        success = dfs(0);
        costbound = exceed;
    } while (!success);
    for(int i=0; i<(int)prefix.size();i++){
        przesun((int)(prefix[i]- '0'));
    }
}

void MyWindow3::algorytm() {
    moves[make_pair(0, -1)] = '2'; moves[make_pair(0, +1)] = '3';
    moves[make_pair(-1, 0)] = '1'; moves[make_pair(+1, 0)] = '0';
    State start;
    int board2[4][4];
    for(int i = 0; i < 4 ; i++){
        board2[0][i] = board[i+6];
    }
    for(int i = 0; i < 4 ; i++){
        board2[1][i] = board[i+11];
    }
    for(int i = 0; i < 4 ; i++){
        board2[2][i] = board[i+16];
    }
    for(int i = 0; i < 4 ; i++){
        board2[3][i] = board[i+21];
    }
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(board2[i][j] < 11){
                board2[i][j] -= 6;
            }
            else if(board2[i][j] < 16){
                board2[i][j] -= 7;
            }
            else if(board2[i][j] < 21){
                board2[i][j] -= 8;
            }
            else{
                board2[i][j] -= 9;
            }
        }
    }
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++) {
            goal.board[i][j] = nongoal.board[i][j] = 4*i + j + 1;
            start.board[i][j] = board2[i][j] +1;
            if(board2[i][j] == 15){
                start.board[i][j] = 0;
            }
            if (start.board[i][j] == 0) {
                start.x = i; start.y = j;
            }
        }
    }
    goal.board[3][3] = nongoal.board[3][3] = 0;
    goal.x = nongoal.x = 3; goal.y = nongoal.y = 3;

    swap(nongoal.board[3][2], nongoal.board[3][1]);
    nongoals.insert(nongoal);
    swap(nongoal.board[3][2], nongoal.board[3][1]);

    swap(nongoal.board[0][0], nongoal.board[0][1]);
    nongoals.insert(nongoal);
    swap(nongoal.board[0][0], nongoal.board[0][1]);

    solve_idastar(start);
}

//wyznaczanie oswietlenia w punktach przeciecia z krawedziami trojkata
double MyWindow3::oswietlenie(punkt p1, punkt p2, punkt p3,bool flaga, bool trojkat){
    double Id;
    double If;
    if(trojkat){
        Id = wynikA * (( p1.y - przeciecia[0].second ) / ( p1.y - p3.y )) + wynikB * ((przeciecia[0].second - p3.y) / ( p1.y - p3.y ));
        If = wynikA * (( p2.y - przeciecia[1].second ) / ( p2.y - p3.y )) + wynikC * ((przeciecia[1].second - p3.y) / ( p2.y - p3.y ));
    }
    else{
        Id = wynikA * (( p1.y - przeciecia[0].second ) / ( p1.y - p3.y )) + wynikC * ((przeciecia[0].second - p3.y) / ( p1.y - p3.y ));
        If = wynikA * (( p2.y - przeciecia[1].second ) / ( p2.y - p3.y )) + wynikB * ((przeciecia[1].second - p3.y) / ( p2.y - p3.y ));
    }
    return flaga ? Id : If;
}

//ustalanie oswietlenia w punktach przeciecia z krawedziami trojkata dla gornej sciany
double MyWindow3::oswietlenie2(punkt p1, punkt p2, punkt p3,bool flaga, bool trojkat, int id){
    double Id;
    double If;
    int index;
    for(int i = 0; i<25; i++){
        if(board[i] == id){
            index = i;
        }
    }

    if(trojkat){
        Id = tablicaOswietlenie[(index/5)*6 + (index%5)] * (( p1.y - przeciecia[0].second ) / ( p1.y - p3.y )) + tablicaOswietlenie[(index/5)*6 + (index%5)+6] * ((przeciecia[0].second - p3.y) / ( p1.y - p3.y ));
        If = tablicaOswietlenie[(index/5)*6 + (index%5)] * (( p2.y - przeciecia[1].second ) / ( p2.y - p3.y )) + tablicaOswietlenie[(index/5)*6 + (index%5)+7] * ((przeciecia[1].second - p3.y) / ( p2.y - p3.y ));
    }
    else{
        Id = tablicaOswietlenie[(index/5)*6 + (index%5) +7] * (( p1.y - przeciecia[0].second ) / ( p1.y - p3.y )) + tablicaOswietlenie[(index/5)*6 + (index%5) ] * ((przeciecia[0].second - p3.y) / ( p1.y - p3.y ));
        If = tablicaOswietlenie[(index/5)*6 + (index%5) +7] * (( p2.y - przeciecia[1].second ) / ( p2.y - p3.y )) + tablicaOswietlenie[(index/5)*6 + (index%5) +1] * ((przeciecia[1].second - p3.y) / ( p2.y - p3.y ));
    }
    return flaga ? Id : If;
}

//wyliczanie oswietlenia dla wiercholkow trojkata
void MyWindow3::oswietlenieWierzcholki(punkt p1, punkt p2, punkt p3, bool flaga){
    punkt swiatlo;
    double dlugosc;
    punkt w;
    w.x = (p2.x-p1.x);
    w.y = (p2.y-p1.y);
    w.z = (p2.z-p1.z);

    punkt v;
    v.x = (p3.x-p1.x);
    v.y = (p3.y-p1.y);
    v.z = (p3.z-p1.z);

    punkt iloczynB;
    iloczynB.x = (w.y*v.z)-(v.y*w.z);
    iloczynB.y = (v.x*w.z)-(w.x*v.z);
    iloczynB.z = (w.x*v.y)-(v.x*w.y);

    dlugosc=sqrt(iloczynB.x*iloczynB.x + iloczynB.y*iloczynB.y + iloczynB.z*iloczynB.z);
    iloczynB.x /= dlugosc;
    iloczynB.y /= dlugosc;
    iloczynB.z /= dlugosc;

    w.x = (p3.x-p2.x);
    w.y = (p3.y-p2.y);
    w.z = (p3.z-p2.z);

    v.x = (p1.x-p2.x);
    v.y = (p1.y-p2.y);
    v.z = (p1.z-p2.z);

    punkt iloczynC;
    iloczynC.x = (w.y*v.z)-(v.y*w.z);
    iloczynC.y = (v.x*w.z)-(w.x*v.z);
    iloczynC.z = (w.x*v.y)-(v.x*w.y);

    dlugosc=sqrt(iloczynC.x*iloczynC.x + iloczynC.y*iloczynC.y + iloczynC.z*iloczynC.z);

    iloczynC.x /= dlugosc;
    iloczynC.y /= dlugosc;
    iloczynC.z /= dlugosc;

    w.x = (p1.x-p3.x);
    w.y = (p1.y-p3.y);
    w.z = (p1.z-p3.z);

    v.x = (p2.x-p3.x);
    v.y = (p2.y-p3.y);
    v.z = (p2.z-p3.z);

    punkt iloczynA;
    iloczynA.x = (w.y*v.z)-(v.y*w.z);
    iloczynA.y = (v.x*w.z)-(w.x*v.z);
    iloczynA.z = (w.x*v.y)-(v.x*w.y);
    dlugosc=sqrt(iloczynA.x*iloczynA.x + iloczynA.y*iloczynA.y + iloczynA.z*iloczynA.z);

    iloczynA.x /= dlugosc;
    iloczynA.y /= dlugosc;
    iloczynA.z /= dlugosc;

    swiatlo.x = (400-p1.x);
    swiatlo.y = (1200-p1.y);
    swiatlo.z = (-2160-p1.z);
    dlugosc = sqrt(swiatlo.x*swiatlo.x + swiatlo.y*swiatlo.y + swiatlo.z*swiatlo.z);
    swiatlo.x/=dlugosc;
    swiatlo.y/=dlugosc;
    swiatlo.z/=dlugosc;

    wynikB = (iloczynB.x * swiatlo.x) + (iloczynB.y * swiatlo.y) + (iloczynB.z * swiatlo.z);

    swiatlo.x = (400-p2.x);
    swiatlo.y = (1200-p2.y);
    swiatlo.z = (-2160-p2.z);
    dlugosc = sqrt(swiatlo.x*swiatlo.x + swiatlo.y*swiatlo.y + swiatlo.z*swiatlo.z);
    swiatlo.x/=dlugosc;
    swiatlo.y/=dlugosc;
    swiatlo.z/=dlugosc;

    wynikC = (iloczynC.x * swiatlo.x) + (iloczynC.y * swiatlo.y) + (iloczynC.z * swiatlo.z);

    swiatlo.x = (400-p3.x);
    swiatlo.y = (1200-p3.y);
    swiatlo.z = (-2160-p3.z);
    dlugosc = sqrt(swiatlo.x*swiatlo.x + swiatlo.y*swiatlo.y + swiatlo.z*swiatlo.z);
    swiatlo.x/=dlugosc;
    swiatlo.y/=dlugosc;
    swiatlo.z/=dlugosc;

    wynikA = (iloczynA.x * swiatlo.x) + (iloczynA.y * swiatlo.y) + (iloczynA.z * swiatlo.z);

    //w przypadku gdy wyliczamy wartosc dla trojkata na gornej sciance zapisujemy jego wartosc
    if(flaga){
        tablicaOswietlenie[licznik_pom] = wynikA;
        licznik_pom++;
    }
}

//wartosc oswietlenia w konkretnym punkcie
double MyWindow3::oswietlenieWartosc(double Id,double If, int x){
    return Id * ( przeciecia[1].first - x ) / ( przeciecia[1].first - przeciecia[0].first ) + If * (x - przeciecia[0].first) / ( przeciecia[1].first - przeciecia[0].first );
}

//znajdowanie przeciec z krawedziami trojkata
void MyWindow3::znajdzPrzeciecia(double y){
    przeciecia.clear();
    double x=0;
    for(int i=0;i<2;i++){
        if((tablica[i].second>y && tablica[i+1].second<=y)||(tablica[i].second<=y && tablica[i+1].second>y)){
            if(tablica[i+1].second-tablica[i].second!=0){
                x = tablica[i].first+(y-tablica[i].second)*((tablica[i+1].first-tablica[i].first)/(tablica[i+1].second-tablica[i].second));
                przeciecia.push_back(make_pair(x,y));
            }
        }
    }
    if((tablica[0].second>y && tablica[2].second<=y)||(tablica[0].second<=y && tablica[2].second>y)){
        if(tablica[2].second-tablica[0].second!=0){
            x = tablica[0].first+(y-tablica[0].second)*((tablica[2].first-tablica[0].first)/(tablica[2].second-tablica[0].second));
            przeciecia.push_back(make_pair(x,y));
        }
    }
    sort(przeciecia.begin(),przeciecia.end());
}

void MyWindow3::timerWrapper(){
    if(zegar){
        sekundy++;
        if(sekundy==60){
            sekundy=0;
            minuty++;
        }
    }
    QString mi = QString::number(minuty);
    QString se = QString::number(sekundy);
    labelTime->setText(mi + ":" + se);
}
