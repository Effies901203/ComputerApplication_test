#define _CRT_SECURE_NO_WARNINGS_
#include<iostream>
#include<vector>
using namespace std;
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

int TOTAL = 2000, WORLD=30;
double LETHAL = 100., MUTATION = 0.01;

class cHuman {
private:
    double virus = 0;
    bool infect = 0;
    bool die = 0;
    int date_die = 0;
    int date = -1;
public:
    double A = 0;
    double B = 0;
    double STRENGTH = 0;
    int X_coordinate;
    int Y_coordinate;
    bool IsInfected();
    bool IsDead();
    void ChangeMutation();
    void MakeInfected(int day);
    double VirusLevel(int day);
    bool Died(int day);
    bool InfectAnother(cHuman *person1, int day);
    void MakeParameter(double A2, double B2, double STR2) {
        A = A2; B = B2; STRENGTH = STR2;
    }
};
class cCountry :public vector<cHuman> {
private:
    int today=0;
public:
    int healthy = TOTAL;
    int sick = 0;
    int dead = 0;
    double MutationA = 0;
    double MutationB = 0;
    double MutationSTR = 0;
    void f() {
        cHuman a;
        int i;
        for (i = 0; i < TOTAL; i++)
        {
            push_back(a);
            at(i).X_coordinate=rand()%30;
            at(i).Y_coordinate=rand()%30;
        }
    }
    cCountry() {
        f();
        today = 0;
        at(0).MakeInfected(0);
        at(0).MakeParameter(0.5, 1.05, 0.6);
    }
    void Tomorrow();
    void RandomInfect();
};


int main(){
    
    int i, n, m = 0;
    class cCountry c;
    srand(1234);

    for (i = 0; i < 300; i++)
    {
        c.RandomInfect();
        c.Tomorrow();
        c.MutationA += c.at(i).A;
        c.MutationB += c.at(i).B;
        c.MutationSTR += c.at(i).STRENGTH;
        for (n = 0; n < TOTAL; n++)
            if (c.at(i).IsInfected())m++;
    }
    double Aavg = c.MutationA / m,
        Bavg = c.MutationB / m,
        STRavg = c.MutationSTR / m;

    for (n = 0; n < TOTAL; n++){
        if (c.at(n).IsInfected())
            c.sick += 1;
        if (c.at(n).IsDead())
        {
            c.dead += 1;
            c.sick -= 1;
        }
        c.healthy = TOTAL - c.dead - c.sick;
    }
    
    cout << "Total=" << TOTAL << endl;
    cout << "Healthy=" << c.healthy << endl;
    cout << "Died=" << c.dead << endl;
    cout << "Sick=" << c.sick << endl;
    cout << "MUTATION=" << MUTATION << endl;
    cout << "Average A=" << Aavg << " <initial=0.5>" << endl;
    cout << "Average B=" << Bavg << " <initial=1.05>" << endl;
    cout << "Average Strength=" << STRavg << " <initial=0.9>" << endl;

    return(0);
}
bool cHuman::IsInfected() { return(infect == 1 ? true : false); }
bool cHuman::IsDead() { return(die == 1 ? true : false); }
double cHuman::VirusLevel(int today) {
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
bool cHuman::Died(int today) {
    if (die==1) return(false);
    else {
        VirusLevel(today);
        if (virus >= LETHAL) {
            die = 1;
            return(true);
        }
        else return(false);
    }
}
bool cHuman::InfectAnother(cHuman *person2, int day) {
    if (infect == 1 && (*person2).infect == 1) return(false);
    if (infect == 0 && (*person2).infect == 0) return(false);
    VirusLevel(day);
    double odds = STRENGTH*virus;
    if (odds >= 1)odds = 1;
    if (rand() / (double)RAND_MAX < odds) return(true);
    else return(false);
}
void cHuman::MakeInfected(int day) {
    infect = 1;
    date = day;
}
void cCountry::Tomorrow() {
    today++;
    int i;
    for (i = 0; i < TOTAL; i++) {
        at(i).ChangeMutation();
        at(i).Died(today);
        MutationA += at(i).A;
        MutationB += at(i).B;
        MutationSTR += at(i).STRENGTH;
        at(i).X_coordinate = (at(i).X_coordinate + WORLD + rand() % 3 - 1) % 30;
        at(i).Y_coordinate = (at(i).Y_coordinate + WORLD + rand() % 3 - 1) % 30;
        if (at(i).X_coordinate == -1) at(i).X_coordinate = 29;
        if (at(i).Y_coordinate == -1) at(i).Y_coordinate = 29;
        if (at(i).X_coordinate == 30) at(i).X_coordinate = 0;
        if (at(i).Y_coordinate == 30) at(i).Y_coordinate = 0;
    }
}
void cCountry::RandomInfect() {
    int x, y;
    for (x = 0; x < (TOTAL-1); x++)
    {
        for (y = x + 1; y < TOTAL; y++) {
            if (at(x).X_coordinate == at(y).X_coordinate && at(x).Y_coordinate== at(y).Y_coordinate) {
                if (at(x).InfectAnother(&at(y), today)) {
                    at(y).MakeInfected(today);
                    at(y).MakeParameter(at(x).A, at(x).B, at(x).STRENGTH);
                }
                if (at(y).InfectAnother(&at(x), today)) {
                    at(x).MakeInfected(today);
                    at(x).MakeParameter(at(y).A, at(y).B, at(y).STRENGTH);;
                }
            }
        }
    }
}
void cHuman::ChangeMutation() {
    if (infect == 1 || die == 0) {
        double r = 1 + rand() / (double)RAND_MAX*(MUTATION * 2) - MUTATION;
        A = A*r;
        r = 1 + rand() / (double)RAND_MAX*(MUTATION * 2) - MUTATION;
        B = B*r;
        r = 1 + rand() / (double)RAND_MAX*(MUTATION * 2) - MUTATION;
        STRENGTH = STRENGTH*r;
    }
}
