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
#include "remis.h"
#include "EngineUtil.h"


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
  {'.', '.', '.', '.', '.', '.', '.', '.'},
  {'.', '.', '.', '.', '.', '.', '.', '.'},
  {'.', 'K', '.', '.', '.', '.', '.', '.'},
  {'.', '.', '.', '.', '.', 'Q', '.', '.'},
  {'.', '.', '.', '.', '.', '.', 'Q', '.'},
  {'.', '.', '.', '.', '.', '.', '.', '.'},
  {'.', '.', '.', '.', '.', '.', '.', 'b'},
  {'.', '.', '.', '.', '.', '.', '.', 'k'},
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



// für die Rochade, und auch die damen umwandlung. Rochade ist erstmals nur für Weiß implementiert.
void sonderzugMachen(string zugNotation) {
  if (zugNotation == "O-O" && weißAmZug) {
    // rochadeMoeglich(string typ, bool weißAmZug, char brettState[8][8], char angriffeWeiß[8][8], char angriffeSchwarz);
    if (weißRochadeKurzMoeglich && rochadeMoeglich("kurz", weißAmZug, brettState, angriffeWeiß, angriffeSchwarz)) {
      // rochade auf dem brett ausführen:
      brettState[7][4] = '.';
      brettState[7][6] = 'K';
      brettState[7][7] = '.';
      brettState[7][5] = 'R';
      
      weißAmZug = !weißAmZug;
    } else {
      cout << "Kurze, weiße Rochade nicht möglich" << endl;
    }
  }
  
  if (zugNotation == "O-O-O" && weißAmZug) {
    if (weißRochadeLangMoeglich && rochadeMoeglich("lang", weißAmZug, brettState, angriffeWeiß, angriffeSchwarz)) {
      // rochade auf dem brett ausführen:
      brettState[7][4] = '.';
      brettState[7][2] = 'K';

      brettState[7][0] = '.';
      brettState[7][3] = 'R';
      
      weißAmZug = !weißAmZug;
    } else {
      cout << "Lange, weiße Rochade nicht möglich" << endl;
    }
  }
  
  // bauernverwandelung. Syntax: e7-e8=Q, auf e8 wird zu einer Dame verwandelt, weiß macht das. Wichtig ist, das abgefangen wird, ob dieser Zug
  // eigenem König Schach gibt und ob der Bauer auf dem Rang überhaupt berechtigt ist.
  // wenn die Zug Notation an 5. Stelle ein "=" enthält, handelt es sich um eine Verwandelung.
  if (zugNotation[5] == '=') {
    cout << "Verwandelung von Bauer zu" << zugNotation[6] << endl;
    
    char wunschFigur = zugNotation[6];
    
    string ausgangsfeld = zugNotation.substr(0, 2);
    cout << "ausgangsfeld der verwandelung: " << ausgangsfeld << endl;
    
    int iAusgangsfeld = feldbezeichnungZuKoord(ausgangsfeld)[0];
    int jAusgangsfeld = feldbezeichnungZuKoord(ausgangsfeld)[1];
    
    // insofern die verwandelung legitim ist:
    
    // bauern auf dem feld entfernen:
    brettState[iAusgangsfeld][jAusgangsfeld] = '.';
    
    // Figur, die erwünscht ist, auf den rang davor bringen:
    if (weißAmZug) {
      // im Fall von weiß wird i dekrementiert:
      brettState[iAusgangsfeld - 1][jAusgangsfeld] = wunschFigur;
      
    } else {
      // im Fall von schwarz wird i inkrementiert:
      brettState[iAusgangsfeld + 1][jAusgangsfeld] = wunschFigur;
    }
    
  }
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
  // hält die angriffe der beiden seiten: angegriffeneFelder.weiß und angegriffeneFelder.schwarz.
  angriffeType angegriffeneFelder;
  
  // nur für die angriffe durch eine einzelne figur, nur zum testen:
  vector<array<int, 2>> angegriffeneFelderFigur;
  

  
  
  switch (figurZeichen) {
    
    case 'P':
    case 'p':

      // bekommt ausgangsfeldKoord, brettState, weißAmZug, enPassantBauer.
      // typ des returns: vector<array<int, 2>>
      moeglicheZuege = moeglicheZuegePawn(ausgangsfeldKoord, brettState, weißAmZug, enPassantBauer);
      
      //moeglicheZuegeAusgeben(moeglicheZuege, "Bauer");
      
      
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
      
      //moeglicheZuegeAusgeben(moeglicheZuege, "Springer");
      
      angegriffeneFelderFigur = angegriffeneFelderKnight(ausgangsfeldKoord);
      
      //angegriffeneFelderAusgeben(angegriffeneFelder, "Springer");
      
      break;
      
      
    case 'R':
    case 'r':
      moeglicheZuege = moeglicheZuegeRook(ausgangsfeldKoord, brettState, weißAmZug);
      // int ausgangsfeldKoord[2], char brettState[8][8], bool weißAmZug
      
      angegriffeneFelderFigur = angegriffeneFelderRook(ausgangsfeldKoord, brettState, weißAmZug);
      
      //moeglicheZuegeAusgeben(moeglicheZuege, "Turm");
      //angegriffeneFelderAusgeben(angegriffeneFelder, "Turm");
      
      
      break;
      
      
    case 'B':
    case 'b':
      cout << "Bishop wurde bewegt!" << endl;
      moeglicheZuege = moeglicheZuegeBishop(ausgangsfeldKoord, brettState, weißAmZug);
      
      angegriffeneFelderFigur = angegriffeneFelderBishop(ausgangsfeldKoord, brettState, weißAmZug);
      
      //moeglicheZuegeAusgeben(moeglicheZuege, "Läufer");
      //angegriffeneFelderAusgeben(angegriffeneFelder, "Läufer");
      
      break;
      
    case 'Q':
    case 'q':
      moeglicheZuege = moeglicheZuegeQueen(ausgangsfeldKoord, brettState, weißAmZug);
      
      angegriffeneFelderFigur = angegriffeneFelderQueen(ausgangsfeldKoord, brettState, weißAmZug);
      
      moeglicheZuegeAusgeben(moeglicheZuege, "Queen");
      //angegriffeneFelderAusgeben(angegriffeneFelder, "Queen");
      
      break;
      
    
    case 'K':
    case 'k':
      // moeglicheZuegeKing(int ausgangsfeldKoord[2], char brettState[8][8], bool weißAmZug, char angriffeWeiße[8][8], char angriffeSchwarz[8][8])
      moeglicheZuege = moeglicheZuegeKing(ausgangsfeldKoord, brettState, weißAmZug, angriffeWeiß, angriffeSchwarz);
      // angegriffeneFelderKing(int ausgangsfeldKoord[2], char brettState[8][8], bool weißAmZug)
      angegriffeneFelderFigur = angegriffeneFelderKing(ausgangsfeldKoord, brettState, weißAmZug);
      
      moeglicheZuegeAusgeben(moeglicheZuege, "König");
      
      angegriffeneFelderAusgeben(angegriffeneFelderFigur, "König");
      
      break;
      
  }
  
  // hier testen, ob der zug überhaupt legitim ist:
  
  
  // den zug aufs brett bringen:
  brettState[iAusgangsfeld][jAusgangsfeld] = '.';
  brettState[iZielfeld][jZielfeld] = figurZeichen;
  
  
  // angriffe der beiden farben ermitteln:
  angegriffeneFelder = angriffeFinden(brettState, weißAmZug);
  
  // hier den bisherigen stand der angriffe für beide farben zurücksetzen:
  angriffeZuruecksetzen();
  
  // alle angriffe von weiß einzeichnen:
  for (array<int, 2> felder : angegriffeneFelder.weiß) {
    int i = felder[0];
    int j = felder[1];
    
    angriffeWeiß[i][j] = 'A';
  }
  
  
  // alle angriffe von schwarz einzeichnen:
  for (array<int, 2> felder : angegriffeneFelder.schwarz) {
    int i = felder[0];
    int j = felder[1];
    
    angriffeSchwarz[i][j] = 'A';
  }

  
  // testen, ob einer der beiden könige im schach steht:
  if (angriffeSchwarz[posWeißerKing[0]][posWeißerKing[1]] == 'A') {
    weißerKingImSchach = true;
    cout << "weißer king steht im schach" << endl;
  }
  
  if (angriffeWeiß[posSchwarzerKing[0]][posSchwarzerKing[1]] == 'A') {
    schwarzerKingImSchach = true;
    cout << "schwarzer king steht im schach" << endl;
  }
  
  // jetzt testen, ob irgendeine der beiden seiten matt steht:
  
  
  // testen, ob die position ein remis ist:
  if (!weißerKingImSchach && !schwarzerKingImSchach) {
    // farbeStehtImPatt(char brettState[8][8], bool weißAmZug, char angriffeWeiß[8][8], char angriffeSchwarz[8][8], int enPassantBauer[2], int posWeißerKing[2], int posSchwarzerKing[2])
    bool istPatt = farbeStehtImPatt(brettState, weißAmZug, angriffeWeiß, angriffeSchwarz, enPassantBauer, posWeißerKing, posSchwarzerKing);
    cout << "patt: " << istPatt << endl;
    
  }
    
    
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
  
  
  zugMachen("f5-f3");

  
  
  
  /*
  cout << "Angriffe von weiß: " << endl;
  cout << "-----------------------" << endl;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      cout << angriffeWeiß[i][j] << " ";
    }
    cout << endl;
  }*/

  
  
  brettAusgeben();
  
  
  

  

  angriffeZuruecksetzen();
  
  
  
  
  return 0;
}
