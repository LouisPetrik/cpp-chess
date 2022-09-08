//
//  EngineUtil.cpp
//  cpp-chess
//
//  Created by Louis Petrik on 07.09.22.
//

#include <stdio.h>

#include <vector>
#include <array>
#include <iostream>

#include "Pawn.h"
#include "Queen.h"
#include "Knight.h"
#include "King.h"
#include "Bishop.h"
#include "Rook.h"


using namespace std;

// zweidimensionales array an chars für visuelles brett
typedef array<array<char, 8>, 8> brett;

brett brettStateDurchFigur(char brettState[8][8], int position[2], int enPassantBauer[2], array<int, 2> zielfeld, char figurZeichen) {
  brett brettStateKopie;
  
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      brettStateKopie[i][j] = brettState[i][j];
    }
  }
  
  brettStateKopie[position[0]][position[1]] = '.';
  brettStateKopie[zielfeld[0]][zielfeld[1]] = figurZeichen;
  
  return brettStateKopie;
}

vector<brett> moeglicheBrettStates(char brettState[8][8], bool weißAmZug, int enPassantBauer[2], char angriffeWeiß[8][8], char angriffeSchwarz[8][8]) {
  
  // die verschiedenen brettStates
  vector<brett> brettStates;
  
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      char figurZeichen = brettState[i][j];
      int position[2] = {i, j};
      
      if (weißAmZug) {
        switch (figurZeichen) {
            
          case 'P':
            for (array<int, 2> zielfeld : moeglicheZuegePawn(position, brettState, weißAmZug, enPassantBauer)) {
              
              brettStates.push_back(brettStateDurchFigur(brettState, position, enPassantBauer, zielfeld, figurZeichen));
            }
            break;
            
          case 'K':
            for (array<int, 2> zielfeld : moeglicheZuegeKing(position, brettState, weißAmZug, angriffeWeiß, angriffeSchwarz)) {
              brettStates.push_back(brettStateDurchFigur(brettState, position, enPassantBauer, zielfeld, figurZeichen));
            }
            break;
            
          case 'Q':
            for (array<int, 2> zielfeld : moeglicheZuegeQueen(position, brettState, weißAmZug)) {
              brettStates.push_back(brettStateDurchFigur(brettState, position, enPassantBauer, zielfeld, figurZeichen));
            }
            break;
            
          case 'R':
            for (array<int, 2> zielfeld : moeglicheZuegeRook(position, brettState, weißAmZug)) {
              brettStates.push_back(brettStateDurchFigur(brettState, position, enPassantBauer, zielfeld, figurZeichen));
            }
            break;
            
          case 'B':
            for (array<int, 2> zielfeld : moeglicheZuegeBishop(position, brettState, weißAmZug)) {
              brettStates.push_back(brettStateDurchFigur(brettState, position, enPassantBauer, zielfeld, figurZeichen));
            }
            break;
            
          case 'N':
            for (array<int, 2> zielfeld : moeglicheZuegeKnight(position, brettState, weißAmZug)) {
              brettStates.push_back(brettStateDurchFigur(brettState, position, enPassantBauer, zielfeld, figurZeichen));
            }
            break;
        }
      }
      
    }
  }
  
  
  return brettStates;

  
}
