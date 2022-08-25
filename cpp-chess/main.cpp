//
//  main.cpp
//  cpp-chess
//
//  Created by Louis Petrik on 25.08.22.
//

#include <iostream>
#include "Util.h"



using namespace std;


bool weißAmZug = true;

int posWeißerKing[2] = {7, 4};
int posSchwarzerKing[2] = {0, 4};

bool weißHatRochiert = false;
bool schwarzHatRochiert = false;

bool weißRochadeKurzMoeglich = true;
bool weißRochadeLangMoeglich = true;

bool schwarzRochadeKurzMoeglich = true;
bool schwarzRochadeLangMoeglich = true;

bool weißerKingImSchach = false;
bool schwarzerKingImSchach = false;

// if(!enPassantBauer) geht?
int enPassantBauer[2] = {};

int halbzugNummer = 1;

char brettState[8][8] = {
    {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
};

char angriffeWeiß[8][8] = {
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
};

char angriffeSchwarz[8][8] = {
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
};

char moeglicheAngriffeSchwarz[8][8] = {
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
};

char moeglicheAngriffeWeiß[8][8] = {
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
};


void zugMachen(char *zugNotation)
{

  cout << "Uebergeben: " << endl;
  cout << zugNotation << endl;

  if (halbzugNummer % 2 == 0)
  {
    cout << "Schwarz ist am Zug" << endl;
  }
  else
  {
    cout << "Weiß ist am Zug" << endl;
  }

  // wird eigentlich erst später inkrementiert, wenn der zug auch legitim war:
  halbzugNummer++;

  // Zurücksetzen, da eventuell nur im Laufe der Funktion auf true gesetzt werden muss
  weißerKingImSchach = false;
  schwarzerKingImSchach = false;

  // testen, ob wir funktion aus anderer Datei importieren können:
};

int main(int argc, const char * argv[]) {
  
  
  // muss irgendwie gechanged werden, weil keine string to char conversion möglich
  // zugMachen("e2-e4");
  
  cout << "Hello World" << endl;
  
  sayHello();
  
  return 0;
}
