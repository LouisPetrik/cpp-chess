//
//  Queen.cpp
//  cpp-chess
//
//  Created by Louis Petrik on 01.09.22.
//

#include <stdio.h>
#include "Linie.h"
#include "diagonale.h"
#include <vector>
#include <array>
#include <iostream>
#include "check.h"

using namespace std;

vector<array<int, 2>> angegriffeneFelderQueen(int ausgangsfeldKoord[2], char brettState[8][8], bool weißAmZug) {
  vector<array<int, 2>> felder;
  
  
  // alle angriffe auf den linien:
  
  for (array<int, 2> feld : linieFelder(brettState, ausgangsfeldKoord, "oben", "angriff", weißAmZug)) {
    felder.push_back({{ feld[0], feld[1] }});
  }
  
  for (array<int, 2> feld : linieFelder(brettState, ausgangsfeldKoord, "unten", "angriff", weißAmZug)) {
    felder.push_back({{ feld[0], feld[1] }});
  }
  
  for (array<int, 2> feld : linieFelder(brettState, ausgangsfeldKoord, "links", "angriff", weißAmZug)) {
    felder.push_back({{ feld[0], feld[1] }});
  }
  
  for (array<int, 2> feld : linieFelder(brettState, ausgangsfeldKoord, "rechts", "angriff", weißAmZug)) {
    felder.push_back({{ feld[0], feld[1] }});
  }
  
  
  // alle angriffe auf den diagonalen:
  
  for (array<int, 2> feld : diagonaleFelder(brettState, ausgangsfeldKoord, "oben-rechts", "angriff", weißAmZug)) {
    felder.push_back({{ feld[0], feld[1] }});
  }
  
  for (array<int, 2> feld : diagonaleFelder(brettState, ausgangsfeldKoord, "oben-links", "angriff", weißAmZug)) {
    felder.push_back({{ feld[0], feld[1] }});
  }
  
  for (array<int, 2> feld : diagonaleFelder(brettState, ausgangsfeldKoord, "unten-rechts", "angriff", weißAmZug)) {
    felder.push_back({{ feld[0], feld[1] }});
  }
  
  for (array<int, 2> feld : diagonaleFelder(brettState, ausgangsfeldKoord, "unten-links", "angriff", weißAmZug)) {
    felder.push_back({{ feld[0], feld[1] }});
  }
  
  
  
  return felder;
}


vector<array<int, 2>> moeglicheZuegeQueen(int ausgangsfeldKoord[2], char brettState[8][8], bool weißAmZug) {
  vector<array<int, 2>> zuege;
  
  // alle felder auf den linien:
  
  for (array<int, 2> feld : linieFelder(brettState, ausgangsfeldKoord, "oben", "zuege", weißAmZug)) {
    zuege.push_back({{ feld[0], feld[1] }});
  }
  
  for (array<int, 2> feld : linieFelder(brettState, ausgangsfeldKoord, "unten", "zuege", weißAmZug)) {
    zuege.push_back({{ feld[0], feld[1] }});
  }
  
  for (array<int, 2> feld : linieFelder(brettState, ausgangsfeldKoord, "rechts", "zuege", weißAmZug)) {
    zuege.push_back({{ feld[0], feld[1] }});
  }
  
  for (array<int, 2> feld : linieFelder(brettState, ausgangsfeldKoord, "links", "zuege", weißAmZug)) {
    zuege.push_back({{ feld[0], feld[1] }});
  }
  
  
  // alle felder auf den diagonalen:
  
  for (array<int, 2> feld : diagonaleFelder(brettState, ausgangsfeldKoord, "oben-rechts", "zuege", weißAmZug)) {
    zuege.push_back({{ feld[0], feld[1] }});
  }
  
  for (array<int, 2> feld : diagonaleFelder(brettState, ausgangsfeldKoord, "oben-links", "zuege", weißAmZug)) {
    zuege.push_back({{ feld[0], feld[1] }});
  }
  
  for (array<int, 2> feld : diagonaleFelder(brettState, ausgangsfeldKoord, "unten-rechts", "zuege", weißAmZug)) {
    zuege.push_back({{ feld[0], feld[1] }});
  }
  
  for (array<int, 2> feld : diagonaleFelder(brettState, ausgangsfeldKoord, "unten-links", "zuege", weißAmZug)) {
    zuege.push_back({{ feld[0], feld[1] }});
  }
  
  // hier alle züge auch schachlich korrekt überprüfen:
   // dieser teil muss quasi genauso für alle anderen figuren übernommen werden.
  vector<array<int, 2>> legitimeZuege;
  
  char figurZeichen = weißAmZug ? 'Q' : 'q';
  
  for (auto zug : zuege) {
    if (zugSchachlichLegitim(zug, ausgangsfeldKoord, brettState, figurZeichen, weißAmZug)) {
      
      legitimeZuege.push_back({{ zug[0], zug[1] }});
      
    } else {
      cout << "Der Zug: " << zug[0] << ", " << zug[1] << " ist nicht legitim!" << endl;
    }
  }
  
  return legitimeZuege;
}
