#include "Pawn.h"
#include "check.h"
#include <vector>
#include <stdio.h>
#include <iostream>
#include <array>
#include <algorithm>


// Grobe Beschreibung wofür die Funktionen sind ist in Pawn.h!

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
      
      zuege.push_back({{i - 1, j }});
      
      if (i == 6) {
        if (brettState[i - 2][j] == '.') {
          zuege.push_back({{ i - 2, j }});
        }
      }
      
    }
    
    // Im folgenden code wird std::find genutzt, welches true returnt, wenn ein wert (letzter parameter) im definierten spektrum liegt
    // testen, ob weiß nach rechts-oben schlagen kann. Dafür muss getestet werden, ob brettState eine von mehreren chars an einer stelle enthält
    
    
    // klappt, aber habe ehrlich gesagt kaum eine idee, was diese konstellation der find()-methode macht.
    if (std::find(schwarzeFiguren, schwarzeFiguren + 6, brettState[i - 1][j + 1]) != schwarzeFiguren  + 6) {
      cout << "gegenerische schlagbare figur steht oben rechts von weißem bauern" << endl;
      
      zuege.push_back({{ i - 1, j + 1}});
    }
    
    // testen, ob weiß nach oben-links schlagen kann
    if (std::find(schwarzeFiguren, schwarzeFiguren + 6, brettState[i - 1][j - 1]) != schwarzeFiguren + 6) {
      cout << "gegnerische, schlagbare figur steht oben links von weißem bauern" << endl;
      
      zuege.push_back({{ i - 1, j - 1}});
    }
    
    
    // testen, ob en-passant möglich ist:
    // vermutlich kann man auch einfach !enPassantBauer, aber idk wie C++ das sieht.
    if (enPassantBauer[0] != 0 && enPassantBauer[1] != 0) {
      
      // en-passant nach oben rechts (von weiß aus). Eventuell muss umgeschrieben werden, an dieser stelle in JS .includes() verwendet.
      if (brettState[i][j + 1] == 'p' && enPassantBauer[0] == i && enPassantBauer[i] == j + 1) {
        cout << "Für weiß: en passant schlagen mit ziel " << i - 1 << " " << j + 1 << " möglich" << endl;
        
        zuege.push_back({{i - 1, j + 1}});
        
      }
      
      
      
      cout << "En-passant bauer i: " << enPassantBauer[0] << " j: " << enPassantBauer[0] << endl;
      
      
      // en-passant nach oben-links (von weiß aus). Selbes spiel wie eben, muss vielleicht überschrieben werden
      // Es scheitert irgendwie gerade an enPassantBauer
      if (brettState[i][j - 1] == 'p' && enPassantBauer[0] == i && enPassantBauer[1] == j - 1) {
        cout << "Für weiß: en passant schlagen mit ziel " << i - 1 << " " << j - 1 << "möglich" << endl;
        
        
        zuege.push_back({{i - 1, j - 1}});
      }
    }
    
    
    
  }
  
  // selber ablauf, nur für die schwarzen bauern
  if (!weißAmZug) {
    if (brettState[i + 1][j] == '.') {
      
      zuege.push_back({{i + 1, j}});
      
      if (brettState[i + 2][j] == '.' && i == 1) {
        zuege.push_back({{ i + 2, j }});
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
    if (enPassantBauer[0] != 0 && enPassantBauer[1] != 0) {
      
      // ob en passant nach rechts geschlagen werden kann:
      
      if (brettState[i][j + 1] == 'P' && enPassantBauer[0] == i && enPassantBauer[1] == j + 1) {
        zuege.push_back({{i + 1, j + 1}});
        
        cout << "Schwarz: En passant schlagen mit ziel " << i + 1 << " " << j + 1 << " möglich" << endl;
        
        
      }
      
      // ob en passant nach links geschlagen werden kann:
      if (brettState[i][j - 1] == 'P' && enPassantBauer[0] == i && enPassantBauer[1] == j - 1) {
        zuege.push_back({{ i + 1, j - 1 }});
        
        cout << "Schwarz: En passant schlagen mit ziel " << i + 1 << " " << j - 1 << " möglich" << endl;
      }
      
    }
    
  }
  
  
  
  // hier alle züge auch schachlich korrekt überprüfen:
   // dieser teil muss quasi genauso für alle anderen figuren übernommen werden. 
  vector<array<int, 2>> legitimeZuege;
  
  char figurZeichen = weißAmZug ? 'P' : 'p';
  
  for (auto zug : zuege) {
    // zielfelder und ausgangslage muss übergeben werden an funktion.
    // fuck was ist mit schach aufheben durch en-passant?
    // hier muss ein inliner ob es sich um P oder p für den pawn handelt. Erstmal für den weißen Bauern
    
    // zugSchachlichLegitim(array<int, 2> zug, int ausgangsfeldKoord[2], char brettState[8][8], char figurZeichen)
    
    
    if (zugSchachlichLegitim(zug, ausgangsfeldKoord, brettState, figurZeichen, weißAmZug)) {
      
      legitimeZuege.push_back({{ zug[0], zug[1] }});
      
    } else {
      cout << "Der Zug: " << zug[0] << ", " << zug[1] << " ist nicht legitim!" << endl;
    }
    
  }
  
  return legitimeZuege;
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
