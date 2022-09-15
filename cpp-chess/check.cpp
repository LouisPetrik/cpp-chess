//
//  check.cpp
//  cpp-chess
//
//  Created by Louis Petrik on 12.09.22.
//

#include <stdio.h>
#include <vector>
#include <array>
#include <iostream>
#include "Util.h"
#include "King.h"
#include "Queen.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Pawn.h"


using namespace std;


// Hilfsfunktion, die Züge einer übergebenen Figur zurückgibt, die das Schach aufheben
// Namen sollten noch optimiert werden, und string für schachGegen auch unnötig -> lieber bool nutzen.
vector<array<int, 2>> aufhebendeZuegeFigur(int posFigur[2], vector<array<int, 2>> zuege, char brettState[8][8], int posBetroffenerKing[2], string schachGegen) {
  
  vector<array<int, 2>> aufhebendeZuege;
  
  const int iAktuell = posFigur[0];
  const int jAktuell = posFigur[1];
  
  for (int i = 0; i < zuege.size(); i++) {
    
    // kopie vom brettState anlegen
    char brettStateKopie[8][8];
    
    for (int z = 0; z < 8; z++) {
      for (int y = 0; y < 8; y++) {
        brettStateKopie[z][y] = brettState[z][y];
      }
    }
    
    // die figur und ihren Zug auf den kopierten Brett State bringen
    char figurZeichen = brettStateKopie[iAktuell][jAktuell];
    
    const int iZielfeld = zuege[i][0];
    const int jZielfeld = zuege[i][1];
    
    brettStateKopie[iAktuell][jAktuell] = '.';
    brettStateKopie[iZielfeld][jZielfeld] = figurZeichen;
    
    if (schachGegen == "schwarz") {
      // zweiter Param ist weißAmZug, automatisch false, da wenn Schach gegen Schwarz, erstmal schwarz wieder am zug ist.
      // kann vermutlich ein scope nach oben geschoben werden
      angriffeType angriffe = angriffeFinden(brettStateKopie, false);
      
      // Ausgeführte Zug ist noch nicht in der Brett State Kopie?
      
      // insofern das Feld des Königs durch den möglichen Zug dann nicht mehr angegriffen wird
      
      // feldInAngriffen(vector<array<int, 2>> angriffe, int pos[2])
      if (!feldInAngriffen(angriffe.weiß, posBetroffenerKing)) {
        cout << "Dieser Zug hebt das Schach auf, check.cpp" << endl;
        cout << figurZeichen << ": " << iZielfeld << ", " << jZielfeld << endl;
        aufhebendeZuege.push_back({{ iZielfeld, jZielfeld }});
      }
    }
    
    if (schachGegen == "weiß") {
      angriffeType angriffe = angriffeFinden(brettStateKopie, true);
      
      if (!feldInAngriffen(angriffe.schwarz, posBetroffenerKing)) {
        cout << "Dieser Zug hebt das Schach auf, check.cpp" << endl;
        cout << figurZeichen << ": " << iZielfeld << ", " << jZielfeld << endl;
        aufhebendeZuege.push_back({{ iZielfeld, jZielfeld }});
      }
    }
  }
  
  return aufhebendeZuege;
  
}


// Figuren, außer könig
bool istFigurAußerKing(char brettChar, string farbe) {
  char figuren[5] = {'P', 'R', 'Q', 'B', 'N'};
  // insofern doch schwarze Figuren identifiziert werden sollen
  if (farbe == "schwarz") {
    figuren[0] = 'p';
    figuren[1] = 'r';
    figuren[2] = 'q';
    figuren[3] = 'b';
    figuren[4] = 'n';
  }

  char* end = figuren + sizeof(figuren) / sizeof(figuren[0]);
  char* pos = std::find(figuren, end, brettChar);
  
  return (pos != end);
}

// überprüft, ob stellung matt ist, indem legitime züge gegen das matt zurückgegeben werden.
// wenn keine züge zurückommen, sondern leer -> matt.
// in JS: angriffeWeiß, angriffeSchwarz - kann man hier als angriffeType angriff übergeben?
vector<array<int, 2>> istMatt(char brettState[8][8], string schachGegen, char angriffeWeiß[8][8], char angriffeSchwarz[8][8], int posBetroffenerKing[2], int enPassantBauer[2]) {
  vector<array<int, 2>> legitimeZuege;
  
  
  // in der JS variante wurden die figuren Zeichen und das Array ihrer Position gemeinsam in einem einzigen Array gespeichert (weil das in JS so geht)
  // hier erstellen wir jetzt vektor für die figuren, und darunter vektor für die positionen der figuren je als array. Für index i findet man also Figur zeichen
  // und aus dem positionen-vektor die zugehörige positoin.
  vector<char> figuren;
  vector<array<int, 2>> figurenPos;
   
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      // alle figuren der Farbe bis auf den König finden
      if (schachGegen == "weiß" && istFigurAußerKing(brettState[i][j], "weiß")) {
        const char figurZeichen = brettState[i][j];
        
        figuren.push_back(figurZeichen);
        // noch pushen der position der figur
        figurenPos.push_back({{ i, j }});
      }
      
      // analog für schwarz:
      if (schachGegen == "schwarz" && istFigurAußerKing(brettState[i][j], "schwarz")) {
        const char figurZeichen = brettState[i][j];
        
        figuren.push_back(figurZeichen);
        // noch pushen der position der figur
        figurenPos.push_back({{ i, j }});
      }
    }
  }
  
  if (figuren.size() > 0) {
    cout << schachGegen << " hat folgende Figuren: " << figuren.data() << endl;
  } else {
    cout << "es ist nur noch der könig vorhanden" << endl; 
  }
  
  
  // Fall abfangen, dass nur noch der König einer Seite vorhanden ist
  // Dabei alle möglichen Züge für ihn generieren. Dann für alle testen, ob sie noch im angegriffenen Bereich liegen.
  // Selbst wenn der König eine Figur dafür schlagen muss, ist das einbezogen.
  
  if (figuren.size() == 0) {
    if (schachGegen == "schwarz") {
      // mögliche Zuege für den könig
      // vector<array<int, 2>> moeglicheZuegeKing(int ausgangsfeldKoord[2], char brettState[8][8], bool weißAmZug, char angriffeWeiße[8][8], char angriffeSchwarz[8][8])
      vector<array<int, 2>> moeglicheZuege = moeglicheZuegeKing(posBetroffenerKing, brettState, false, angriffeWeiß, angriffeSchwarz);
      
      
      if (moeglicheZuege.size() > 0) {
        // die einzelnen, möglichen züge des königs übernehmen:
        for (auto zug : moeglicheZuege) {
          legitimeZuege.push_back({{ zug[0], zug[1] }});
        }
      }
    }
    // analog für weiß:
    if (schachGegen == "schwarz") {
      // mögliche Zuege für den könig
      // vector<array<int, 2>> moeglicheZuegeKing(int ausgangsfeldKoord[2], char brettState[8][8], bool weißAmZug, char angriffeWeiße[8][8], char angriffeSchwarz[8][8])
      vector<array<int, 2>> moeglicheZuege = moeglicheZuegeKing(posBetroffenerKing, brettState, true, angriffeWeiß, angriffeSchwarz);
      
      
      if (moeglicheZuege.size() > 0) {
        // die einzelnen, möglichen züge des königs übernehmen:
        for (auto zug : moeglicheZuege) {
          legitimeZuege.push_back({{ zug[0], zug[1] }});
        }
      }
    }
  // es noch mehr Figuren, als nur den König, die potentiell das Matt aufheben könnten:
  } else {
    /* Jetzt für die verbleibenden Figuren der Seite über alle möglichen Züge gehen, und dann die möglichen brettStates in Funktion für
     Bedrohungen übergeben. Wenn dann in einer dieser outcomes der König nicht mehr im Schach steht, wird er gepushed.
     Muss noch verkürzt werden. Zu einer Funktion vereinfach werden, die statt immer schachGegen nur einmal alle züge generiert: weißAmZug true oder false wird
     dann über eine inline funktion gemacht, die für "weiß" halt true und sonst false returnt.
     Im nächsten Schritt der Vereinfachung sollte es nur noch eine Funktion geben, die für alle Figuren die aufhebenden Züge zurückgibt. Die einzelnen Funktionen für
     die möglichen züge der Funktion können an diese Funktion übergeben werden. */
    
    for (int i = 0; i < figuren.size(); i++) {
      const char figur = figuren[i];
      int position[2] = { figurenPos[i][0], figurenPos[i][1] };
      // inline-kondition, damit nicht für jede farbe eigener funktionsaufruf geschrieben werden muss.
      // wenn schach gegen weiß, ist weiß natürlich am zug. Als argument für parameter weißAmZug in den funktionen
      bool weißAmZug = ((schachGegen == "weiß") ? true : false);
      
      // jeweils die möglichen Züge für die Figur
      vector<array<int, 2>> moeglicheZuege;
      
      // alle Züge der Figur, die das Schach noch aufheben können
      vector<array<int, 2>> aufhebendeZuege;
      
      
      switch (figur) {
        case 'Q':
        case 'q':
          moeglicheZuege = moeglicheZuegeQueen(position, brettState, weißAmZug);
          aufhebendeZuege = aufhebendeZuegeFigur(position, moeglicheZuege, brettState, posBetroffenerKing, schachGegen);
          
          if (aufhebendeZuege.size() > 0) {
            for (auto zug : aufhebendeZuege) {
              legitimeZuege.push_back({{ zug[0], zug[1] }});
            }
            
            cout << schachGegen << " Queen kann Schach aufheben" << endl;
            cout << "mögliche Aufhebende Züge: " << endl;
            for (auto zug : aufhebendeZuege) {
              cout << zug[0] << ", " << zug[1] << endl;
            }
          }
          
          break;
          
        case 'B':
        case 'b':
          moeglicheZuege = moeglicheZuegeBishop(position, brettState, weißAmZug);
          aufhebendeZuege = aufhebendeZuegeFigur(position, moeglicheZuege, brettState, posBetroffenerKing, schachGegen);
          
          if (aufhebendeZuege.size() > 0) {
            cout << schachGegen << " Läufer kann Schach aufheben" << endl;
            for (auto zug : aufhebendeZuege) {
              legitimeZuege.push_back({{ zug[0], zug[1] }});
            }
          }
      
          
          break;
      
        case 'N':
        case 'n':
          moeglicheZuege = moeglicheZuegeKnight(position, brettState, weißAmZug);
          aufhebendeZuege = aufhebendeZuegeFigur(position, moeglicheZuege, brettState, posBetroffenerKing, schachGegen);
          
          if (aufhebendeZuege.size() > 0) {
            cout << schachGegen << " Springer kann Schach aufheben" << endl;
            for (auto zug : aufhebendeZuege) {
              legitimeZuege.push_back({{ zug[0], zug[1] }});
            }
          }
    
          break;
          
        case 'R':
        case 'r':
          moeglicheZuege = moeglicheZuegeRook(position, brettState, weißAmZug);
          aufhebendeZuege = aufhebendeZuegeFigur(position, moeglicheZuege, brettState, posBetroffenerKing, schachGegen);
          
          if (aufhebendeZuege.size() > 0) {
            cout << schachGegen << " Rook kann Schach aufheben" << endl;
            for (auto zug : aufhebendeZuege) {
              legitimeZuege.push_back({{ zug[0], zug[1] }});
            }
          }
  
          break;
          
        case 'P':
        case 'p':
          moeglicheZuege = moeglicheZuegePawn(position, brettState, weißAmZug, enPassantBauer);
          
          aufhebendeZuege = aufhebendeZuegeFigur(position, moeglicheZuege, brettState, posBetroffenerKing, schachGegen);
          
          if (aufhebendeZuege.size() > 0) {
            cout << schachGegen << " Bauer kann Schach aufheben" << endl;
            for (auto zug : aufhebendeZuege) {
              legitimeZuege.push_back({{ zug[0], zug[1] }});
            }
          }
      
          break;
          
      }
    }
  }
  
  return legitimeZuege;
}
