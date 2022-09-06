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
        }
      }
    }
  }
  return istPatt;
  
  
}
