#ifndef PROJECT3_FENCER_H
#define PROJECT3_FENCER_H

#include <string>
using namespace std;

struct Fencer {
    Fencer(string name, string club, string tW, string tL, string wR, string pW, string pL, string pWR, string dW, string dL, string dWR);
    string name;
    string club;
    string totalWins;
    string totalLoses;
    string winRatio;
    string poolWins;
    string poolLoses;
    string poolWinRatio;
    string deWins;
    string deLosses;
    string deWinRatio;
};

#endif //PROJECT3_FENCER_H
