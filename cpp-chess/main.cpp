//
//  main.cpp
//  cpp-chess
//
//  Created by Louis Petrik on 25.08.22.
//

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cstring>
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


// klappt wunderbar
void brettAusgeben() {
  cout << "---------------" << endl;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      cout << brettState[i][j] << " ";
    }
    cout << endl;
  }
  cout << "---------------" << endl;
}


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

  // versuchen die position des weißen Königs aktuell zu finden:
  //int posWeißerKing[2][2] = *figurFinden("k", brettState);

  // ich hoffe das geht alles auch einfacher, ohne dass man jedes mal eigenen pointer braucht. 
  int* ptrWeißerKingPos = figurFinden('K', brettState);
  posWeißerKing[0] = ptrWeißerKingPos[0];
  posWeißerKing[1] = ptrWeißerKingPos[1];
  
  int* ptrSchwarzerKingPos = figurFinden('k', brettState);
  posSchwarzerKing[0] = ptrSchwarzerKingPos[0];
  posSchwarzerKing[1] = ptrSchwarzerKingPos[1];
  

 
};

int main(int argc, const char * argv[]) {
  
  
  // muss irgendwie gechanged werden, weil keine string to char conversion möglich
  // zugMachen("e2-e4");
  
  
  

  
  brettAusgeben();

  
  
  
  return 0;
}
