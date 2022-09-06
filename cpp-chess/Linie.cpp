/*
 Hilfsklasse mit hilfsfunktionen für das berechnen von linien auf dem brett, genutzt für Türme und Damen.
 */
#include <stdio.h>

#include <vector>
#include <array>
#include <iostream>
#include "Linie.h"
#include "Util.h"



using namespace std;


// können dann weg.
const char schwarzeFiguren[6] = {'p', 'r', 'q', 'b', 'n', 'k'};
const char weißeFiguren[6] = {'P', 'R', 'Q', 'B', 'N', 'K'};


/**
    Diese funktion gibt alle Koordinaten auf einer Linie aus, je nach Modus - angriff oder zuege, also alle angegriffenen felder auf der linie oder ziehbare felder. Außerdem muss natürlich richtung spezifiziert werden.
  @param brettState  - selbsterklärend
  @param ausgangsfeldKoord - selbsterklärend
  @param richtung - string, entweder "oben", "unten", "rechts", oder "links" aus der sicht von weiß.
 */
vector<array<int, 2>> linieFelder(char brettState[8][8], int ausgangsfeldKoord[2], string richtung, string modus, bool weißAmZug) {
  vector<array<int, 2>> felderAufLinie;
  
  const int i = ausgangsfeldKoord[0];
  const int j = ausgangsfeldKoord[1];
  
  // testweise den brettstate ausgeben zu dem zeitpunkt, wo der turm seinen zug machen soll:
  /*
  cout << "brettstate aktuell" << endl;
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      cout << brettState[x][y] << " ";
    }
    cout << endl;
  }*/
 
  // true, insofern auf eine eigene Figur in der Linie gestoßen wird. Sobald das der Fall ist,
  // werden die Felder dahinter (mit den weiteren Durchläufen nicht aufgenommen. )
  bool geblockt = false;
  
  for (int x = 1; x <= 7; x++) {
    if (!geblockt) {
      int iTemp = i;
      int jTemp = j;
      
      if (richtung == "oben" && i - x >= 0) {
        iTemp = i - x;
      }

      if (richtung == "unten" && i + x <= 7) {
        iTemp = i + x;
      }

      if (richtung == "links" && j - x >= 0) {
        jTemp = j - x;
      }

      if (richtung == "rechts" && j + x <= 7) {
        jTemp = j + x;
      }
      
      // der standpunkt der figur selbst zählt nicht als angegriffen durch sich selbst:
      // Genausowenig kann eine figur als legitimen zug auf das feld ziehen, auf dem sie bereits steht
      // -> wenn das eigene feld durchgegangen wird (else-case) wird der rest der schleife geskipped
      // hier ist wichtig, dass es ein logisches ODER ist, da sich bei bewegungen über linien i oder j nicht verändern.
      if (iTemp != i || jTemp != j) {
        felderAufLinie.push_back({{ iTemp, jTemp }});
      } else {
        break;
      }

      if (modus == "angriff") {
        // wenn eine eigene oder gegnerische Figur gefunden wird, wird dieses Feld noch
        // aufgenommen, da es angegriffen / gedeckt wird.
        if (brettState[iTemp][jTemp] != '.') {
          felderAufLinie.push_back({{iTemp, jTemp}});
          break;
        }
      }
      
      if (modus == "zuege") {
        // hier wieder mit der array-in-array funktion testen:
        
        // insofern eine gegnerische figur gefunden wird, ist das feld noch ziehbar.
        // Wenn es eine eigene figur ist, wird der weg dadurch geblockt und das feld selbst nicht aufgenommen.
        
        if (weißAmZug && istSchwarzeFigur(brettState[iTemp][jTemp])) {
          felderAufLinie.push_back({{ iTemp, jTemp }});
        }
        
        // auf eigene figur gestoßen, feld wird nicht aufgenommen und loop abgebrochen
        if (weißAmZug && istWeißeFigur(brettState[iTemp][jTemp])) {
          cout << "es wurde auf eine eigene, weiße figur gestoßen bei " << iTemp << ", " << jTemp << endl;
          cout << "Die figur: " << brettState[iTemp][jTemp] << endl; 
          geblockt = true;
          break;
        }
        
        // brettState[iTemp][jTemp]
        
        if (!weißAmZug && istWeißeFigur(brettState[iTemp][jTemp])) {
          felderAufLinie.push_back({{iTemp, jTemp}});
        }
        
        // auf eigene figur gestoßen, feld wird nicht aufgenommen und loop abgebrochen
        if (!weißAmZug && istSchwarzeFigur(brettState[iTemp][jTemp])) {
          geblockt = true;
          break;
        }
        

      }
    }
  }
  
  return felderAufLinie;
}
