#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <QSlider>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <vector>
#include <iostream>
#include <iterator>
#include <functional>
#include <algorithm>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <climits>
#include <stack>
#include <map>
#include <QMessageBox>
#include <QString>
#include <QKeyEvent>
#include <QTimer>
#include <QPlainTextEdit>

using namespace std;

struct punkt{
    double x;
    double y;
    double z;
};

struct tekstura{
    punkt lewy[3];
    punkt prawy[3];
};

class Cube{
public:
    punkt wspolrzedne[8];
    tekstura t;
    int nr;
};

struct Kolor{
    int r;
    int g;
    int b;
};

struct State {
    int board[4][4];
    int x, y;

    bool operator==(const State &rhs) {
        if (!(x == rhs.x && y == rhs.y)){
            return false;
        }
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                if (board[i][j] != rhs.board[i][j]){
                    return false;
                }
            }
        }
        return true;
    }

    bool operator<(const State &rhs) const{
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++) {
                if (board[i][j] < rhs.board[i][j])
                {
                    return true;
                }
                else if (board[i][j] > rhs.board[i][j])
                {
                    return false;
                }
            }
        }
        if (x < rhs.x || (x == rhs.x && y < rhs.y)){
            return true;
        }
        return false;
    }
};

class Macierz{
public:
    Macierz(){
        for(int i=0 ;i<4;i++){
            for(int j=0;j<4;j++){
                double k=0.0;
                if(i==j)
                {
                    k=1.0;
                }
                macierz[i][j]=k;
            }
        }
    }

    Macierz operator *(const Macierz &v )
        {
            Macierz wynik;

            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    wynik.macierz[i][j] = macierz[i][0]*v.macierz[0][j] + macierz[i][1]*v.macierz[1][j] + macierz[i][2]*v.macierz[2][j] + macierz[i][3]*v.macierz[3][j];
                }
            }
            return wynik;
        }

public:
    double macierz[4][4] ;
};


class MyWindow : public QWidget{
    Q_OBJECT
public:
    MyWindow(QWidget *parent = 0);
    ~MyWindow();

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
    Cube punkty[16];
    Cube punkty2[16];
    tekstura punktyTekstura[16];
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
    double tablicaOswietlenie[25];
    int szer;
    int wys;
    int nrImage;
    int pusty;
    int nrMat;
    int board[16];
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
    int findXPosition(int puzzle[4][4]);
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
