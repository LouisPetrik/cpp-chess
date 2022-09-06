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
#include <vector>
#include "Util.h"
#include "Pawn.h"
#include "Knight.h"
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Queen.h"
#include "Castle.h"

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

// Wird auch immer auf 0, 0 zurückgesetzt, da irgendwie auf NULL oder mit delete nicht funktioniert.
int enPassantBauer[2] = {0, 0};

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


// füllt die beiden angriffe<Farbe> arrays mit dem standard wert.
void angriffeZuruecksetzen() {
  for (int i = 0; i < 8; i++) {
    fill_n(angriffeWeiß[i], 8, '.');
    fill_n(angriffeSchwarz[i], 8, '.');
  }
}

void moeglicheAngriffeZuruecksetzen() {
  for (int i = 0; i < 8; i++) {
    fill_n(moeglicheAngriffeWeiß[i], 8, '.');
    fill_n(moeglicheAngriffeSchwarz[i], 8, '.');
  }
}
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


void zugMachen(string zugNotation)
{
  
  
  cout << "-------------------------------" << endl;
  cout << "Zug: " << halbzugNummer << endl;



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
  
  cout << "Übergebene zug notation: " << zugNotation << endl;
  string ausgangsfeld = zugNotation.substr(0, 2);
  string zielfeld = zugNotation.substr(3);
  

  // könnte vielleicht anstatt zwei mal function call einmalig in array gespeichert und dann daraus entnommen werden. 
  int iAusgangsfeld = feldbezeichnungZuKoord(ausgangsfeld)[0];
  int jAusgangsfeld = feldbezeichnungZuKoord(ausgangsfeld)[1];
  

  
  int iZielfeld = feldbezeichnungZuKoord(zielfeld)[0];
  int jZielfeld = feldbezeichnungZuKoord(zielfeld)[1];
  
  
  char figurZeichen = brettState[iAusgangsfeld][jAusgangsfeld];
  
  // nötig um es den einzelnen figuren für die möglichen Züge als Ausgangslage zu übergeben.
  int ausgangsfeldKoord[2] = {iAusgangsfeld, jAusgangsfeld};
  
  
  // die möglichen Züge der Figur. Als vektor, damit geadded werden kann
  vector<array<int, 2>> moeglicheZuege;
  // erstmal zur zum testen
  vector<array<int, 2>> angegriffeneFelder;
  

  
  
  switch (figurZeichen) {
    
    case 'P':
    case 'p':

      // bekommt ausgangsfeldKoord, brettState, weißAmZug, enPassantBauer.
      // typ des returns: vector<array<int, 2>>
      moeglicheZuege = moeglicheZuegePawn(ausgangsfeldKoord, brettState, weißAmZug, enPassantBauer);
      
      moeglicheZuegeAusgeben(moeglicheZuege, "Bauer");
      
      
      // hier testen, ob der bauern-zug zufällig ein nehmen via. en-passant war:
      
      if (enPassantBauer[0] != 0 && enPassantBauer[1] != 0) {
        if (weißAmZug) {
          if (iZielfeld == enPassantBauer[0] - 1 && jZielfeld == enPassantBauer[1]) {
            cout << "Weiß hat Bauer auf " << enPassantBauer[0] << " " << enPassantBauer[1] << " en-passant genommmen" << endl;
            
            // übernehmen, dass per en passant geschlagen wurde:
            // könnte auch ein scope höher, da sonst redundant mit der variante für schwarz.
            brettState[enPassantBauer[0]][enPassantBauer[1]] = '.';
          }
        }
        // selbes spiel für schwarz:
        if (!weißAmZug) {
          if (iZielfeld == enPassantBauer[0] + 1 && jZielfeld == enPassantBauer[1]) {
            cout << "Schwarz hat Bauer auf " << enPassantBauer[0] << " " << enPassantBauer[1] << " en-passant genommmen" << endl;
            
            // übernehmen, dass per en passant geschlagen wurde:
            brettState[enPassantBauer[0]][enPassantBauer[1]] = '.';
          }
        }
      }

      
      // hier immer erstmal den en-passant bauern zurücksetzen.
      enPassantBauer[0] = 0;
      enPassantBauer[1] = 0;
      
      
      // abfangen, wenn ein bauer zwei Schritte aus Grundstellung kommt, und damit en-passant schlagbar ist:
      if (weißAmZug && iZielfeld == 4 && iAusgangsfeld == 6) {
        cout << "Weißer Bauer Doppelschritt!" << endl;
        enPassantBauer[0] = iZielfeld;
        enPassantBauer[1] = jZielfeld;
      }
      
      // wieso klappt hier nicht, doppelschritt auszugeben?
      if (!weißAmZug && iZielfeld == 3 && iAusgangsfeld == 1) {
        cout << "Schwarzer Bauer Doppelschritt!" << endl;
        enPassantBauer[0] = iZielfeld;
        enPassantBauer[1] = jZielfeld;
      }
      
      
      break;
    
    case 'N':
    case 'n':
      
      moeglicheZuege = moeglicheZuegeKnight(ausgangsfeldKoord, brettState, weißAmZug);
      
      moeglicheZuegeAusgeben(moeglicheZuege, "Springer");
      
      angegriffeneFelder = angegriffeneFelderKnight(ausgangsfeldKoord);
      
      //angegriffeneFelderAusgeben(angegriffeneFelder, "Springer");
      
      break;
      
      
    case 'R':
    case 'r':
      moeglicheZuege = moeglicheZuegeRook(ausgangsfeldKoord, brettState, weißAmZug);
      // int ausgangsfeldKoord[2], char brettState[8][8], bool weißAmZug
      
      angegriffeneFelder = angegriffeneFelderRook(ausgangsfeldKoord, brettState, weißAmZug);
      
      moeglicheZuegeAusgeben(moeglicheZuege, "Turm");
      //angegriffeneFelderAusgeben(angegriffeneFelder, "Turm");
      
      
      break;
      
      
    case 'B':
    case 'b':
      cout << "Bishop wurde bewegt!" << endl;
      moeglicheZuege = moeglicheZuegeBishop(ausgangsfeldKoord, brettState, weißAmZug);
      
      angegriffeneFelder = angegriffeneFelderBishop(ausgangsfeldKoord, brettState, weißAmZug);
      
      moeglicheZuegeAusgeben(moeglicheZuege, "Läufer");
      //angegriffeneFelderAusgeben(angegriffeneFelder, "Läufer");
      
      break;
      
    case 'Q':
    case 'q':
      moeglicheZuege = moeglicheZuegeQueen(ausgangsfeldKoord, brettState, weißAmZug);
      
      angegriffeneFelder = angegriffeneFelderQueen(ausgangsfeldKoord, brettState, weißAmZug);
      
      moeglicheZuegeAusgeben(moeglicheZuege, "Queen");
      //angegriffeneFelderAusgeben(angegriffeneFelder, "Queen");
      
      break;
      
    
    case 'K':
    case 'k':
      // moeglicheZuegeKing(int ausgangsfeldKoord[2], char brettState[8][8], bool weißAmZug, char angriffeWeiße[8][8], char angriffeSchwarz[8][8])
      moeglicheZuege = moeglicheZuegeKing(ausgangsfeldKoord, brettState, weißAmZug, angriffeWeiß, angriffeSchwarz);
      // angegriffeneFelderKing(int ausgangsfeldKoord[2], char brettState[8][8], bool weißAmZug)
      angegriffeneFelder = angegriffeneFelderKing(ausgangsfeldKoord, brettState, weißAmZug);
      
      moeglicheZuegeAusgeben(moeglicheZuege, "König");
      
      break;
      
  }
  
  // über den vector von möglichen zügen iterieren:
  

  
  
  //

  
  // den zug einfach testweise mal durchführen:
  brettState[iAusgangsfeld][jAusgangsfeld] = '.';
  brettState[iZielfeld][jZielfeld] = figurZeichen;
  
  // testen, ob einer der beiden könige im schach steht:
  
  
  // andere seite ist wieder am zug:
  
  weißAmZug = !weißAmZug;
  
  

 
};


// führt direkt einen zug auf dem brett state aus:
// Funktion für Maxi, wird in diesem Code hier nicht genutzt und dient dazu, zug direkt in brett state zu bringen.
void zugAusfuehren(string zugNotation) {
  
  string ausgangsfeld = zugNotation.substr(0, 2);
  string zielfeld = zugNotation.substr(3);
  
  int iAusgangsfeld = feldbezeichnungZuKoord(ausgangsfeld)[0];
  int jAusgangsfeld = feldbezeichnungZuKoord(ausgangsfeld)[1];
  
  int iZielfeld = feldbezeichnungZuKoord(zielfeld)[0];
  int jZielfeld = feldbezeichnungZuKoord(zielfeld)[1];
  
  char figurZeichen = brettState[iAusgangsfeld][jAusgangsfeld];
  
  brettState[iAusgangsfeld][jAusgangsfeld] = '.';
  brettState[iZielfeld][jZielfeld] = figurZeichen;
  
}

int main(int argc, const char * argv[]) {
  
  
  // muss irgendwie gechanged werden, weil keine string to char conversion möglich
  // zugMachen("e2-e4");
 
  zugMachen("e2-e4");
  zugMachen("e7-e5");
  zugMachen("e1-e2");
  
  
  
  
  
  // testen der ware-eröffnung für den turm
  
  
  
  
  // testen mit dem bishop opening:
  
  
  
  /*
  
  zugMachen("e2-e4");
  zugMachen("e7-e5");
  zugMachen("f1-c4");
  zugMachen("g8-f6");
  zugMachen("c4-d5");
  
  */
  
  
  

  
  
  // vorher:
  /*
   ---------------
   . . . . . . . .
   . . . . . . . .
   . . . . . . . .
   . . . . . . . .
   . . . . . . . .
   . . . . . . . .
   . . . . X . X .
   . . . . . X . .
   --------------- */
  

  
  /*
   En passant testen:
   
   */

  
  
  brettAusgeben();

  
  
  angriffeZuruecksetzen();
  
  
  
  
  return 0;
}
