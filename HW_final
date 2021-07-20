#define _CRT_SECURE_NO_WARNINGS_
#include<iostream>
#include<vector>
using namespace std;
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

int TOTAL = 2000,WORLD=30;
double LETHAL = 100., MUTATION = 0.01;

class cHuman {
private:
    double virus = 0;
    bool infect = 0;
    bool die = 0;
    int date_die = 0;
    int date = -1;
    int WORLD=30;
public:
    bool IsInfected();
    bool IsDead();
    void muta();
    void MakeInfected(int day);
    double VirusLevel(int day);
    bool Died(int day);
    bool InfectAnother(cHuman *person1, int day);
    double A = 0;
    double B = 0;
    double STRENGTH = 0;
    int xcoo;
    int ycoo;
    void makep(double A2, double B2, double STR2) {
        A = A2; B = B2; STRENGTH = STR2;
    }
};
class cCountry :public vector<cHuman> {
private:
    int p = sizeof(TOTAL);
    int today=0;
    int WORLD;
public:
    void f() {
        cHuman a;
        int i;
        for (i = 0; i < TOTAL; i++)
        {
            push_back(a);
            at(i).xcoo=0;
            at(i).ycoo=0;
        }
    }
    cCountry() {
        f();
        today = 0;
        at(0).MakeInfected(0);
        at(0).makep(0.5, 1.05, 0.6);
    }
    void Tomorrow();
    void RandomInfect();
    int healthy = TOTAL;
    int sick = 0;
    int dead = 0;
    double mutaA = 0;
    double mutaB = 0;
    double mutaSTR = 0;
    void makep(int i, double A, double B, double STR) { at(i).makep(A, B, STR); };
};


int main()
{
    int i, n, m = 0;
    class cCountry c;
    srand(1234);

    for (i = 0; i < 300; i++)
    {
        c.RandomInfect();
        c.Tomorrow();
        c.mutaA += c.at(i).A;
        c.mutaB += c.at(i).B;
        c.mutaSTR += c.at(i).STRENGTH;
        for (n = 0; n < TOTAL; n++)
            if (c.at(i).IsInfected())m++;
    }
    double Aavg = c.mutaA / m,
        Bavg = c.mutaB / m,
        STRavg = c.mutaSTR / m;

    for (n = 0; n < 2000; n++)
    {
        if (c.at(n).IsInfected())
            c.sick += 1;
        if (c.at(n).IsDead())
        {
            c.dead += 1;
            c.sick -= 1;
        }
        c.healthy = TOTAL - c.dead - c.sick;
        printf("(%d,%d)\n",c.at(n).xcoo,c.at(n).ycoo);
    }
    
    printf("Total=%d\n", TOTAL);
    printf("Healthy=%d\n", c.healthy);
    printf("Died=%d\n", c.dead);
    printf("Sick=%d\n", c.sick);
    cout << "MUTATION=" << MUTATION << endl;
    cout << "Average A=" << Aavg << " <initial=0.5>" << endl;
    cout << "Average B=" << Bavg << " <initial=1.05>" << endl;
    cout << "Average Strength=" << STRavg << " <initial=0.9>" << endl;

    return(0);
}
bool cHuman::IsInfected() { return(infect == 1 ? true : false); }
bool cHuman::IsDead() { return(die == 1 ? true : false); }
double cHuman::VirusLevel(int today)
{
    if (date == -1)return(0);
    else {
        if ((A*pow(B, today - date)) >= LETHAL)
        {
            die = 1;
            date_die = today;
            virus = LETHAL;
            return(virus);
        }
        else return(virus = A*pow(B, today - date));
    };

}
bool cHuman::Died(int today)
{
    if (die==1)return(false);
    else {
        VirusLevel(today);
        if (virus >= LETHAL) {
            die = 1;
            return(true);
        }
        else return(false);
    }
}
bool cHuman::InfectAnother(cHuman *person2, int day)
{
    if (infect == 1 && (*person2).infect == 1)return(false);
    if (infect == 0 && (*person2).infect == 0)return(false);
    VirusLevel(day);
    double odds = STRENGTH*virus;
    if (odds >= 1)odds = 1;
    if (rand() / (double)RAND_MAX < odds) return(true);
    else return(false);
}
void cHuman::MakeInfected(int day)
{
    infect = 1;
    date = day;
}
double Myrand() { return(rand() % TOTAL); }
void cCountry::Tomorrow() {
    today++;
    int i;
    for (i = 0; i < TOTAL; i++) {
        at(i).muta();
        at(i).Died(today);
        mutaA += at(i).A;
        mutaB += at(i).B;
        mutaSTR += at(i).STRENGTH;
        at(i).xcoo = (at(i).xcoo + WORLD + rand() % 3 - 1) % 30;
        at(i).ycoo = (at(i).ycoo + WORLD + rand() % 3 - 1) % 30;
        if (at(i).xcoo == -1)at(i).xcoo = 29; if (at(i).ycoo == -1)at(i).ycoo = -29;
        if (at(i).xcoo == 30)at(i).xcoo = 0; if (at(i).ycoo == 30)at(i).ycoo = 0;
    }
}
void cCountry::RandomInfect() {
    int x, y;
    for (x = 0; x < (TOTAL-1); x++)
    {
        for (y = x + 1; y < TOTAL; y++) {
            if (at(x).xcoo == at(y).xcoo&&at(x).ycoo== at(y).ycoo) {
                if (at(x).InfectAnother(&at(y), today)) {
                    at(y).MakeInfected(today);
                    makep(y, at(x).A, at(x).B, at(x).STRENGTH);
                }
                if (at(y).InfectAnother(&at(x), today)) {
                    at(x).MakeInfected(today);
                    makep(x, at(y).A, at(y).B, at(y).STRENGTH);
                }
            }
        }
    }
}
void cHuman::muta() {
    if (infect == 1 || die == 0) {
        double r = 1 + rand() / (double)RAND_MAX*(MUTATION * 2) - MUTATION;
        A = A*r;
        r = 1 + rand() / (double)RAND_MAX*(MUTATION * 2) - MUTATION;
        B = B*r;
        r = 1 + rand() / (double)RAND_MAX*(MUTATION * 2) - MUTATION;
        STRENGTH = STRENGTH*r;
    }
}
