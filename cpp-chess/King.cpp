//
//  King.cpp
//  cpp-chess
//
//  Created by Louis Petrik on 01.09.22.
//

#include <stdio.h>
#include <vector>
#include <array>
#include <iostream>
#include "Util.h"


const char schwarzeFiguren[6] = {'p', 'r', 'q', 'b', 'n', 'k'};
const char weißeFiguren[6] = {'P', 'R', 'Q', 'B', 'N', 'K'};

using namespace std;


bool koordAufBrett(int iVariation, int jVariation) {
  if (iVariation < 0 || iVariation > 7 || jVariation < 0 || jVariation > 7) {
    return false;
  } else {
    return true;
  }
}

// angriffeWeiß und angriffeSchwarz werden als Array mit visueller repräsentation übergeben, also 'A' für angriffe eingezeichnet.
bool zielfeldLegitim(int iVariation, int jVariation, char brettState[8][8], bool weißAmZug, char angriffeWeiß[8][8], char angriffeSchwarz[8][8]) {
  if (
        iVariation < 0 ||
        iVariation > 7 ||
        jVariation < 0 ||
        jVariation > 7
      ) {
        return false;
      } else {
        if (
            // sollte jetzt funktionieren 
            (weißAmZug && istWeißeFigur(brettState[iVariation][jVariation])) ||
            (!weißAmZug && istSchwarzeFigur(brettState[iVariation][jVariation]))
            ) {
              cout << "könig durch eigene figur geblockt " << endl;
              return false;
            }
        
        if ((weißAmZug && angriffeSchwarz[iVariation][jVariation] == 'A') || (!weißAmZug && angriffeWeiß[iVariation][jVariation] == 'A')) {
          return false;
        }
          
      }
  
  return true;
}


vector<array<int, 2>> angegriffeneFelderKing(int ausgangsfeldKoord[2], char brettState[8][8], bool weißAmZug) {
  vector<array<int, 2>> felder;
  
  const int i = ausgangsfeldKoord[0];
  const int j = ausgangsfeldKoord[1];
  
  
  if (koordAufBrett(i - 1, j)) {
    felder.push_back({{i - 1, j}});
  }

  if (koordAufBrett(i - 1, j + 1)) {
    felder.push_back({{i - 1, j + 1}});
  }

  if (koordAufBrett(i, j + 1)) {
    felder.push_back({{i, j + 1}});
  }

  if (koordAufBrett(i + 1, j + 1)) {
    felder.push_back({{i + 1, j + 1}});
  }

  if (koordAufBrett(i + 1, j)) {
    felder.push_back({{i + 1, j }});
  }

  if (koordAufBrett(i + 1, j - 1)) {
    felder.push_back({{i + 1, j - 1}});
  }

  if (koordAufBrett(i, j - 1)) {
    felder.push_back({{i, j - 1}});
  }
  
  if (koordAufBrett(i - 1, j - 1)) {
    felder.push_back({{i - 1, j - 1}});
  }
  
  return felder;
  
}


vector<array<int, 2>> moeglicheZuegeKing(int ausgangsfeldKoord[2], char brettState[8][8], bool weißAmZug, char angriffeWeiße[8][8], char angriffeSchwarz[8][8]) {
  vector<array<int, 2>> zuege;
  
  const int i = ausgangsfeldKoord[0];
  const int j = ausgangsfeldKoord[1];
  
  // zielfeldLegitim(int iVariation, int jVariation, char brettState[8][8], bool weißAmZug, char angriffeSchwarz[8][8], char angriffeWeiß[8][8])
  
  if (zielfeldLegitim(i - 1, j, brettState, weißAmZug, angriffeWeiße, angriffeSchwarz)) {
    zuege.push_back({{i - 1, j}});
  }

  if (zielfeldLegitim(i - 1, j + 1, brettState, weißAmZug, angriffeWeiße, angriffeSchwarz)) {
    zuege.push_back({{i - 1, j + 1}});
  }

  if (zielfeldLegitim(i, j + 1, brettState, weißAmZug, angriffeWeiße, angriffeSchwarz)) {
    zuege.push_back({{i, j + 1}});
  }

  if (zielfeldLegitim(i + 1, j + 1, brettState, weißAmZug, angriffeWeiße, angriffeSchwarz)) {
    zuege.push_back({{i + 1, j + 1}});
  }

  if (zielfeldLegitim(i + 1, j, brettState, weißAmZug, angriffeWeiße, angriffeSchwarz)) {
    zuege.push_back({{i + 1, j}});
  }

  if (zielfeldLegitim(i + 1, j - 1, brettState, weißAmZug, angriffeWeiße, angriffeSchwarz)) {
    zuege.push_back({{i + 1, j - 1}});
  }

  if (zielfeldLegitim(i, j - 1, brettState, weißAmZug, angriffeWeiße, angriffeSchwarz)) {
    zuege.push_back({{i, j - 1}});
  }
  if (zielfeldLegitim(i - 1, j - 1, brettState, weißAmZug, angriffeWeiße, angriffeSchwarz)) {
    zuege.push_back({{i - 1, j - 1}});
  }
  
  return zuege;
  
}
