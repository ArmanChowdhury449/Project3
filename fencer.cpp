#include "fencer.h"

Fencer::Fencer(string name, string club, string tW, string tL, string wR, string pW, string pL, string pWR, string dW, string dL, string dWR)
{
    this->name = name;
    this->club = club;
    totalWins = tW;
    totalLoses = tL;
    winRatio = wR;
    poolWins = pW;
    poolLoses = pL;
    poolWinRatio = pWR;
    deWins = dW;
    deLosses = dL;
    deWinRatio = dWR;
}
