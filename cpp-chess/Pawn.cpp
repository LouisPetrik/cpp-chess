//
//  Pawn.cpp
//  cpp-chess
//
//  Created by Louis Petrik on 26.08.22.
//

#include "Pawn.h"
#include <vector>
#include <stdio.h>
#include <iostream>
#include <array>
#include <algorithm>


using namespace std; 


// Listen der Zeichen der einzelnen Figuren, zur Erkennung von eigenen/gegnerischen Figuren auf dem Feld.
const char schwarzeFiguren[6] = {'p', 'r', 'q', 'b', 'n', 'k'};
const char weißeFiguren[6] = {'P', 'R', 'Q', 'B', 'N', 'K'};


vector<array<int, 2>> moeglicheZuegePawn(int ausgangsfeldKoord[2], char brettState[8][8], bool weißAmZug, int enPassantBauer[2]) {
  
  vector<array<int, 2>> zuege;

  const int i = ausgangsfeldKoord[0];
  const int j = ausgangsfeldKoord[1];
  
  cout << "Position des Bauerns: ";
  cout << "i: " << i << " j: " << j << endl; 
  
  if (weißAmZug) {
    if (brettState[i - 1][j] == '.') {
      // hier muss irgendwie ein anonymer array erstellt werden.
      // es gibt hoffentlich eine bessere lösung als diese komische syntax
      array<int, 2> zug { {i - 1, j} };
      zuege.push_back(zug);
      
      if (brettState[i + 2][j] == '.' && i == 1) {
        // bin mir nicht sicher, ob das zuverlässig funktioniert da "zug" schon existiert.
        array<int, 2> zug { {i + 2, j } };
        
        zuege.push_back(zug);
    
        
      }
    }g
    
    // Im folgenden code wird std::find genutzt, welches true returnt, wenn ein wert (letzter parameter) im definierten spektrum liegt
    // testen, ob weiß nach rechts-oben schlagen kann. Dafür muss getestet werden, ob brettState eine von mehreren chars an einer stelle enthält
    
    
    // klappt, aber habe ehrlich gesagt kaum eine idee, was diese konstellation der find()-methode macht.
    if (std::find(schwarzeFiguren, schwarzeFiguren + 6, brettState[i - 1][j + 1]) != schwarzeFiguren  + 6) {
      cout << "gegenerische schlagbare figur steht oben rechts von weißem bauern" << endl;
    }
    
    // testen, ob weiß nach oben-links schlagen kann
    if (std::find(schwarzeFiguren, schwarzeFiguren + 6, brettState[i - 1][j - 1]) != schwarzeFiguren + 6) {
      cout << "gegnerische, schlagbare figur steht oben links von weißem bauern" << endl;
    }
    
    
    // testen, ob en-passant möglich ist:
    // vermutlich kann man auch einfach !enPassantBauer, aber idk wie C++ das sieht.
    if (enPassantBauer != NULL) {
      cout << "Oben rechts: ";
      cout << brettState[i][j + 1] << endl;
      // en-passant nach oben rechts (von weiß aus). Eventuell muss umgeschrieben werden, an dieser stelle in JS .includes() verwendet.
      if (brettState[i][j + 1] == 'p' && enPassantBauer[0] == i && enPassantBauer[i] == j + 1) {
        cout << "Für weiß: en passant schlagen mit ziel " << i - 1 << j + 1 << "möglich" << endl;
      }
      
      
      cout << "Oben links: ";
      cout << brettState[i][j - 1] << endl; 
      // en-passant nach oben-links (von weiß aus). Selbes spiel wie eben, muss vielleicht überschrieben werden
      if (brettState[i][j - 1] == 'p' && enPassantBauer[0] == i && enPassantBauer[1] == j - 1) {
        cout << "Für weiß: en passant schlagen mit ziel " << i - 1 << j - 1 << "möglich" << endl;
      }
    }
  
  }
  
  // selber ablauf, nur für die schwarzen bauern
  if (!weißAmZug) {
    if (brettState[i + 1][j] == '.') {
     
      zuege.push_back({{i + 1, j}});
      
      if (brettState[i + 2][j] == '.' && i == 1) {
        zuege.push_back({{ i + 1, j }});
      }
      
      
    }
    
    // testen, ob schwarz nach unten-rechts schlagen kann (unten-rechts aus weißer sicht aufs brett)
    if (std::find(weißeFiguren, weißeFiguren + 6, brettState[i + 1][j + 1]) != weißeFiguren + 6) {
      zuege.push_back({{i + 1, j + 1}});
      
    }
    
    // testen, ob schwarz nach unten-links schlagen kann.
    if (std::find(weißeFiguren, weißeFiguren + 6, brettState[i + 1][j - 1]) != weißeFiguren + 6) {
      zuege.push_back({{i + 1, j - 1}});
      
    }
    
    // testen, ob en-passant geschlagen werden kann:
    if (enPassantBauer != NULL) {
      // ob en passant nach rechts geschlagen werden kann:
      
      if (brettState[i][j + 1] == 'P' && enPassantBauer[0] == i && enPassantBauer[1] == j + 1) {
        zuege.push_back({{i + 1, j + 1}});
        
        cout << "Schwarz: En passant schlagen mit ziel " << i + 1 << " " << j + 1 << " möglich" << endl;
      }
      
      // ob en passant nach links geschlagen werden kann:
      if (brettState[i][j - 1] == 'P' && enPassantBauer[0] == i && enPassantBauer[1] == j + 1) {
        zuege.push_back({{ i + 1, j - 1 }});
        
        cout << "Schwarz: En passant schlagen mit ziel " << i + 1 << " " << j - 1 << " möglich" << endl;
      }
      
    }
    
  }
  
  
  
  return zuege;
};



vector<array<int, 2>> angegriffeneFelderPawn(int ausgangsfeldKoord[2], string farbe) {
  
  vector<array<int, 2>> felder;
    
  const int i = ausgangsfeldKoord[0];
  const int j = ausgangsfeldKoord[1];
  
  if (farbe == "weiß") {
    if (i - 1 >= 0 && j - 1 >= 0) {
      array<int, 2> feld { {i - 1, j - 1 } };
      
      felder.push_back(feld);
    }
    
    if (i - 1 >= 0 && j + 1 <= 7) {
      array<int, 2> feld { {i - 1, j + 1 } };
      
      felder.push_back(feld);
    }
  }
  
  if (farbe == "schwarz") {
    if (i + 1 <= 7 && j - 1 >= 0) {
      array<int, 2> feld { { i + 1, j - 1 } };
      felder.push_back(feld);
    }

    if (i + 1 <= 7 && j + 1 <= 7) {
      array<int, 2> feld { { i + 1, j + 1 } };
      felder.push_back(feld);
    }
  }

  
  return felder;
}
