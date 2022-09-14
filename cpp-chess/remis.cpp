//
//  remis.cpp
//  cpp-chess
//
//  Created by Louis Petrik on 06.09.22.
//

#include <stdio.h>
#include <vector>
#include <array>
#include <iostream>
#include "Util.h"
#include "Pawn.h"
#include "Knight.h"
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Queen.h"
#include "Util.h"





bool farbeStehtImPatt(char brettState[8][8], bool weißAmZug, char angriffeWeiß[8][8], char angriffeSchwarz[8][8], int enPassantBauer[2], int posWeißerKing[2], int posSchwarzerKing[2]) {
  // by default true, da sobald nur ein einziger zug gefunden wurde, der legitim ist, kein patt ist (false returnt wird).
  bool istPatt = true;
  
  // Zu diesem Zeitpunkt hat Weiß gerade einen legitimen Zug gemacht, also wird überprüft, ob Schwarz nun im Patt steht.
  // Da dafür die Züge aus Sicht von Schwarz überprüft werden, wird immer bei den Parametern weißAmZug auf false gesetzt.
  
  // alle Figuren von Schwarz finden und bestimmen, ob es noch legitime Züge gibt:
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if ((weißAmZug && istSchwarzeFigur(brettState[i][j])) || (!weißAmZug && istWeißeFigur(brettState[i][j]))) {
        char gefundeneFigur = brettState[i][j];
        int positionFigur[2] = {i, j};
        
        // alle möglichen Züge der Figur, außer Acht gelassen, ob dieser Zug eigenem König Schach gibt. Muss also seperat noch behandelt werden.
        vector<array<int, 2>> moeglicheZuege;
        
        switch (gefundeneFigur) {
          case 'K':
          case 'k':
            moeglicheZuege = moeglicheZuegeKing(positionFigur, brettState, weißAmZug, angriffeWeiß, angriffeSchwarz);
            
            // insofern es nur einen einzige, erlaubten zug gibt. Nur hier wird direkt überprüft, ob die anzahl moeglicher Züge >= 1, da bei den anderen Figuren
            // nicht das in-Schach-setzen des eigenen Königs berücksichtigt wird.
            if (moeglicheZuege.size() >= 1) {
              istPatt = false;
            }
            break;
          
          case 'Q':
          case 'q':
            moeglicheZuege = moeglicheZuegeQueen(positionFigur, brettState, !weißAmZug);
            break;
            
          case 'P':
          case 'p':
            moeglicheZuege = moeglicheZuegePawn(positionFigur, brettState, !weißAmZug, enPassantBauer);
            break;
            
          case 'R':
          case 'r':
            moeglicheZuege = moeglicheZuegeRook(positionFigur, brettState, !weißAmZug);
            break;
            
          case 'B':
          case 'b':
            moeglicheZuege = moeglicheZuegeBishop(positionFigur, brettState, !weißAmZug);
            
            cout << "Anzahl der möglichen Züge des Bishops: " << moeglicheZuege.size() << endl;
            break;
            
          case 'N':
          case 'n':
            moeglicheZuege = moeglicheZuegeKnight(positionFigur, brettState, !weißAmZug);
            break;
            
        }
        
  
        
        // für jeden einzelnen Zug überprüfen, ob er König in Schach setzen würde:
        // bisschen anders als in JS, da hier for-each, daher testen nötig
        for (array<int, 2> zug : moeglicheZuege) {
          int iZielfeld = zug[0];
          int jZielfeld = zug[1];
          
          // unabhängige Kopie vom brettState machen, auf die alle möglichen Züge aller Figuren gebracht werden.
          char testBrettState[8][8];
          // bin mir nicht sicher, ob der noch gefilled werden muss, oder ob das jetzt so gehen sollte.e
          
          // alles aus dem brettState in die Kopie reinschreiben:
          for (int z = 0; z < 8; z++) {
            for (int y = 0; y < 8; y++) {
              testBrettState[z][y] = brettState[z][y];
            }
          }
          
          // den möglichen Zug der Figur in den testBrettState:
          testBrettState[i][j] = '.';
          testBrettState[iZielfeld][jZielfeld] = gefundeneFigur;
          
          // Hier werden die Angriffe zusammengeführt.
          // weißAmZug auf false ist an dieser Stelle vielleicht nicht richtig
          angriffeType moeglicheAngegriffeneFelder = angriffeFinden(testBrettState, !weißAmZug);
          
          
          if (weißAmZug) {
            // hier muss getestet werden, ob die position vom schwarzen König in den moeglichenAngriffen vector<array<int, 2>> ist.
            // in den angriffen bei: moeglicheAngegriffeneFelder.weiß vom typen wie gesagt.
            // wenn in den angegriffenen Feldern, NICHT die position vom könig ist, ist es kein patt. Muss nur einmal der fall sein.
            if (!feldInAngriffen(moeglicheAngegriffeneFelder.weiß, posSchwarzerKing)) {
              istPatt = false; 
              
            }
            
            // muss später mal gemacht werden.
          }
          
          // analog nur für schwarz
          if (!weißAmZug) {
            if (!feldInAngriffen(moeglicheAngegriffeneFelder.schwarz, posWeißerKing)) {
              istPatt = false;
              
            }
            
          }
          
          
          
        }
      }
    }
  }
  return istPatt;
  
  
}

// Bekommt den brettState nach einem ausgeführten zug übergeben und gibt true / false ob remis durch material mangel zurück.
bool unzureichendesMaterial(char brettState[8][8]) {
  // als standard auf true, da quasi umstellung durch gegenbeweis erfolgt.
  // wird auf false gesetzt, wenn eine Seite eine Dame, einen Turm, einen Bauern oder mehr als einen Läufer / Springer hat
  bool istRemis = true;
  
  
  // liste der figuren, die insgesamt auf dem brett sind:
  vector<char> figuren;
  
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (brettState[i][j] != '.') {
        figuren.push_back(brettState[i][j]);
      }
    }
  }
  
  
  cout << "figuren, die noch verfügbar sind: " << endl;
  
  int weißeKnights = 0;
  int schwarzeKnights = 0;
  
  int weißeBishops = 0;
  int schwarzeBishops = 0;
  
  
  for (int i = 0; i < figuren.size(); i++) {
    char figur = figuren[i];
    
    if (figur == 'R' || figur == 'r' || figur == 'Q' || figur == 'q' || figur == 'P' || figur == 'p') {
      istRemis = false;
    }
    
    if (figur == 'N') {
      weißeKnights++;
    }
    
    if (figur == 'n') {
      schwarzeKnights++;
    }
    
    
    if (figur == 'B') {
      weißeBishops++;
    }
    
    if (figur == 'b') {
      schwarzeBishops++;
    }
  }
  
  if (weißeKnights > 1 || weißeBishops > 1 || schwarzeKnights > 1 || schwarzeBishops > 1) {
    istRemis = false; 
  }
  
  return istRemis;

  
}
