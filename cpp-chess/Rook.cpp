//
//  Rook.cpp
//  cpp-chess
//
//  Created by Louis Petrik on 31.08.22.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <array>
#include "Linie.h"
#include "check.h"


const char schwarzeFiguren[6] = {'p', 'r', 'q', 'b', 'n', 'k'};
const char weißeFiguren[6] = {'P', 'R', 'Q', 'B', 'N', 'K'};



using namespace std;


vector<array<int, 2>> angegriffeneFelderRook(int ausgangsfeldKoord[2], char brettState[8][8], bool weißAmZug) {
  vector<array<int, 2>> felder;
    
  const int i = ausgangsfeldKoord[0];
  const int j = ausgangsfeldKoord[1];
  
  // Die linienFelder funktion gibt zurück: vector<array<int, 2>>
  // Diese Funktion vom Rook soll selbst vector<array<int, 2>> zurückgeben, also müssen diese Werte alle in einen eigenen vector kopiert werden.
  
  
  
  
  // holt aus der linieFelder funktion alle felder die auf den entsprechenden Linien angegriffen werden, und fügt
  // sie den insgesamt angegriffenen feldern hinzu.
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
  
  
  
  return felder;
  
  
}


// versuch, diese funktion im neuen stil mit der helfer funktion aus Linie.cpp umzuschreiben:


vector<array<int, 2>> moeglicheZuegeRook(int ausgangsfeldKoord[2], char brettState[8][8], bool weißAmZug) {
  
  
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
  
  
  // hier alle züge auch schachlich korrekt überprüfen:
  // dieser teil muss quasi genauso für alle anderen figuren übernommen werden.
  vector<array<int, 2>> legitimeZuege;
  
  char figurZeichen = weißAmZug ? 'R' : 'r';
  
  for (auto zug : zuege) {
    if (zugSchachlichLegitim(zug, ausgangsfeldKoord, brettState, figurZeichen, weißAmZug)) {
      
      legitimeZuege.push_back({{ zug[0], zug[1] }});
      
    } else {
      cout << "Der Zug: " << zug[0] << ", " << zug[1] << " ist nicht legitim!" << endl;
    }
  }
  
  return legitimeZuege;
}



// Muss massiv umgeschrieben werden, bisheriger ansatz kann komplett durch die neue Linie.cpp ersetzt werden.
/*
vector<array<int, 2>> moeglicheZuegeRook(int ausgangsfeldKoord[2], char brettState[8][8], bool weißAmZug) {
  vector<array<int, 2>> zuege;
  
  
  const int i = ausgangsfeldKoord[0];
  const int j = ausgangsfeldKoord[1];
  
  for (int iTemp = i - 1; iTemp >= 0; iTemp--) {
    
    if (weißAmZug) {
      // std::find(weißeFiguren, weißeFiguren + 6, brettState[iTemp][jTemp])
      if (std::find(weißeFiguren, weißeFiguren + 6, brettState[iTemp][j])) {
        break;
      } else {
        zuege.push_back({{iTemp, j}});
      }

      if (std::find(schwarzeFiguren, schwarzeFiguren + 6, brettState[iTemp][j])) {
        zuege.push_back({{iTemp, j}});
        break;
      }
    }
    if (!weißAmZug) {
      if (std::find(schwarzeFiguren, schwarzeFiguren + 6, brettState[iTemp][j])) {
        break;
      } else {
        zuege.push_back({{iTemp, j}});
      }

      if (std::find(weißeFiguren, weißeFiguren + 6, brettState[iTemp][j])) {
        zuege.push_back({{iTemp, j}});
        break;
      }
    }
  }
  
  // von weiß aus nach unten:
  
  for (int iTemp = i + 1; iTemp <= 7; iTemp++) {
      // eine Figur steht dort. Dann wird dieses Feld noch aufgenommen in die gedeckten / angegriffenen Felder
      // alles danach in der linie (weiter nach oben) entfällt aber

      if (weißAmZug) {
        if (std::find(weißeFiguren, weißeFiguren + 6, brettState[iTemp][j])) {
          break;
        } else {
          zuege.push_back({{iTemp, j}});
        }

        if (std::find(schwarzeFiguren, schwarzeFiguren + 6, brettState[iTemp][j])) {
          zuege.push_back({{iTemp, j}});
          break;
        }
      }
    
      if (!weißAmZug) {
        if (std::find(schwarzeFiguren, schwarzeFiguren + 6, brettState[iTemp][j])) {
          break;
        } else {
          
          zuege.push_back({{iTemp, j}});
        }

        if (std::find(weißeFiguren, weißeFiguren + 6, brettState[iTemp][j])) {
          zuege.push_back({{iTemp, j}});
          break;
        }
      }
    }
  
  // von weiß und schwarz aus nach links:
  for (int jTemp = j - 1; jTemp >= 0; jTemp--) {
    if (weißAmZug) {
      if (std::find(weißeFiguren, weißeFiguren + 6, brettState[i][jTemp])) {
        break;
      } else {
        zuege.push_back({{i, jTemp}});
      }

      if (std::find(schwarzeFiguren, schwarzeFiguren + 6, brettState[i][jTemp])) {
        zuege.push_back({{i, jTemp}});
        break;
      }
    }
    if (!weißAmZug) {
      if (std::find(schwarzeFiguren, schwarzeFiguren + 6, brettState[i][jTemp])) {
        break;
      } else {
        zuege.push_back({{i, jTemp}});
      }

      if (std::find(weißeFiguren, weißeFiguren + 6, brettState[i][jTemp])) {
        zuege.push_back({{i, jTemp}});
        break;
      }
    }
  }
  
  // von weiß und schwarz aus nach rechts:
  
  for (int jTemp = j + 1; jTemp <= 7; jTemp++) {
    if (weißAmZug) {
      if (std::find(weißeFiguren, weißeFiguren + 6, brettState[i][jTemp])) {
        break;
      } else {
        zuege.push_back({{ i, jTemp }});
      }

      if (std::find(schwarzeFiguren, schwarzeFiguren + 6, brettState[i][jTemp])) {
        zuege.push_back({{ i, jTemp }});
        break;
      }
    }
    
    if (!weißAmZug) {
      if (std::find(schwarzeFiguren, schwarzeFiguren + 6, brettState[i][jTemp])) {
        break;
      } else {
        zuege.push_back({{ i, jTemp }});
      }

      if (std::find(weißeFiguren, weißeFiguren + 6, brettState[i][jTemp])) {
        zuege.push_back({{ i, jTemp }});
        break;
      }
    }
  }
  
  cout << "Rook.cpp, länge zuege: " << zuege.size() << endl;
  return zuege; 
}



*/
