#include "mainwindow2.h"

using namespace std;

class MyWindow3 : public QWidget{
    Q_OBJECT
public:
    MyWindow3(QWidget *parent = 0);
    ~MyWindow3();

private:
    QImage *img;
    QImage *img2;
    QImage *obrazy[3];
    QImage *boki[3];
    QGroupBox *grupa;
    QGroupBox *grupa2;
    QGroupBox *grupa3;
    QGroupBox *grupa4;
    QGroupBox *grupa5;
    QSlider *podglad;
    QPushButton *up;
    QPushButton *down;
    QPushButton *left;
    QPushButton *right;
    QPushButton *losuj;
    QPushButton *zmien;
    QPushButton *zmien2;
    QPushButton *uloz;
    QPushButton *pomoc;
    QPushButton *pomoc2;
    QMessageBox *message;
    QMessageBox *message2;
    QMessageBox *message3;
    QTimer *timer;
    QPlainTextEdit *timeText;
    QPlainTextEdit *moveText;
    QLabel *label1;
    QLabel *label2;
    QLabel *labelTime;
    QLabel *labelMove;
    Macierz rotacjaX;
    Macierz przesuniecie;
    Cube punkty[25];
    Cube punkty2[25];
    tekstura punktyTekstura[25];
    vector< pair <double,double> > przeciecia;
    vector< pair <double,double> > tablica;
    vector<char> prefix;
    map<pair<int, int>, char> moves;
    set<State> nongoals;
    set<State> visited;
    State goal;
    State nongoal;
    State node;
    double wartoscAlfa;
    double wynikA;
    double wynikB;
    double wynikC;
    double tablicaOswietlenie[36];
    int szer;
    int wys;
    int nrImage;
    int pusty;
    int nrMat;
    int board[25];
    int licznik_pom;
    int ruchy;
    int exceed;
    int costbound;
    int sekundy;
    int minuty;
    bool recznie;
    bool zegar;

    void keyPressEvent(QKeyEvent * event );
    void paintEvent(QPaintEvent*);
    void przerysuj();
    void szescian(int index);
    void zamaluj();
    void teksturowanie(punkt p1, punkt p2, punkt p3, int index, bool flaga, QImage* obraz, bool przod);
    void alfa();
    void plansza();
    void przydzielTeksture(int index);
    void nalozTeksture(int index);
    void nalozTekstureBok(int index, int opcja);
    void nalozTeksturePrzod(int index);
    void losowanie();
    void solve();
    void przesun(int numer);
    void blokada(bool stan);
    void blokuj(bool stan);
    void algorytm();
    void solve_idastar(State &start);
    void oswietlenieWierzcholki(punkt p1, punkt p2, punkt p3, bool flaga);
    void znajdzPrzeciecia(double y);
    bool widoczna(punkt p1, punkt p2, punkt p3);
    bool rozwiazywalna();
    bool winner();
    bool dfs(int depth);
    int getInvCount(int arr[]);
    int znajdzMin(punkt p1, punkt p2, punkt p3);
    int znajdzMax(punkt p1, punkt p2, punkt p3);
    int znajdzMinX(punkt p1, punkt p2, punkt p3);
    int znajdzMaxX(punkt p1, punkt p2, punkt p3);
    int h(State &s);
    double oswietlenie(punkt p1, punkt p2, punkt p3, bool flaga, bool trojkat);
    double oswietlenie2(punkt p1, punkt p2, punkt p3, bool flaga, bool trojkat, int id);
    double oswietlenieWartosc(double Id,double If, int x);

private slots:
    void Wartosc(int wartosc);
    void upWrapper();
    void downWrapper();
    void leftWrapper();
    void rightWrapper();
    void losujWrapper();
    void pomocWrapper();
    void pomoc2Wrapper();
    void zmianaObrazu();
    void zmianaMaterialu();
    void rozwiaz();
    void timerWrapper();
};
