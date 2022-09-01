//
//  Bishop.cpp
//  cpp-chess
//
//  Created by Louis Petrik on 01.09.22.
//

#include "diagonale.h"
#include <stdio.h>
#include <vector>
#include <array>
#include <iostream>

using namespace std;

vector<array<int, 2>> angegriffeneFelderBishop(int ausgangsfeldKoord[2], char brettState[8][8], bool weißAmZug) {
  vector<array<int, 2>> felder;
  
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


vector<array<int, 2>> moeglicheZuegeBishop(int ausgangsfeldKoord[2], char brettState[8][8], bool weißAmZug) {
  vector<array<int, 2>> zuege;
  
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
  
  return zuege;
}
