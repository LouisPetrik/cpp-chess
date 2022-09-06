//
//  Util.cpp
//  cpp-chess
//
//  Created by Louis Petrik on 25.08.22.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include "Util.h"
#include "Pawn.h"
#include "Knight.h"
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Queen.h"
#include "Castle.h"


using namespace std;



string koordinaten[8][8] = {
  {"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8"},
  {"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7"},
  {"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6"},
  {"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5"},
  {"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4"},
  {"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3"},
  {"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2"},
  {"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"}
};

using namespace std;



bool istWeißeFigur(char brettChar) {
  char figuren[6] = {'P', 'R', 'Q', 'B', 'N', 'K'};
  char* end = figuren + sizeof(figuren) / sizeof(figuren[0]);
  char* pos = std::find(figuren, end, brettChar);
  
  return (pos != end);
}

// selbe implementierung für schwarz, beide funktionen können noch zu einer zusammengefasst werden.
bool istSchwarzeFigur(char brettChar) {
  char figuren[6] = {'p', 'r', 'q', 'b', 'n', 'k'};
  char* end = figuren + sizeof(figuren) / sizeof(figuren[0]);
  char* pos = std::find(figuren, end, brettChar);
  
  return (pos != end);
}


int *feldbezeichnungZuKoord(string feld) {
  int position[2];
  
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (koordinaten[i][j] == feld) {
        position[0] = i;
        position[1] = j;
      }
    }
  }
  
  return position;
}

// Bekommt eine Figur, dessen Koordinaten diese Funktion finden soll und gibt sie als [i, j] array wieder zurück:
int *figurFinden(char figurZeichen, char brettState[8][8]) {
  int position[2];
  
  // iteriert über das gesamte array bis der die figur findet:
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (brettState[i][j] == figurZeichen) {
        position[0] = i;
        position[1] = j;
      }
    }
  }
  
  return position;
};

// hierfür wird ein array von vectoren behandelt oder ein set oder eine map - also etwas mit zwei values.


angriffeType angriffeFinden(char brettState[8][8], bool weißAmZug) {
  // dieser struct ist folgendermaßen aufgebaut:
  // angriffe.weiß ist ein vector<array<int, 2>> für die weißen angriffe. Mit denen fangen wir an.
  
  angriffeType angriffe;
  // angriffe.weiß dient als angegriffeneFelderWeiß alternative in der JS. Analog für angriffe.schwarz.
  
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      char figur = brettState[i][j];
      int figurPos[2] = {i, j};
      

      
      // erstmal nur für die weißen figuren, zum testen: 
      if (figur == 'P') {
        
        for (array<int, 2> feld : angegriffeneFelderPawn(figurPos, "weiß")) {
          angriffe.weiß.push_back({{feld[0], feld[1]}});
        }
      }
      
      if (figur == 'N') {
        for (array<int, 2> feld : angegriffeneFelderKnight(figurPos)) {
          angriffe.weiß.push_back({{feld[0], feld[1]}});
        }
      }
      
      if (figur == 'B') {
        for (array<int, 2> feld : angegriffeneFelderBishop(figurPos, brettState, weißAmZug)) {
          angriffe.weiß.push_back({{feld[0], feld[1]}});
        }
      }
      
      if (figur == 'R') {
        for (array<int, 2> feld : angegriffeneFelderRook(figurPos, brettState, weißAmZug)) {
          angriffe.weiß.push_back({{feld[0], feld[1]}});
        }
      }
      
      if (figur == 'Q') {
        for (array<int, 2> feld : angegriffeneFelderQueen(figurPos, brettState, weißAmZug)) {
          angriffe.weiß.push_back({{feld[0], feld[1]}});
        }
      }
      
      if (figur == 'K') {
        for (array<int, 2> feld : angegriffeneFelderKing(figurPos, brettState, weißAmZug)) {
          angriffe.weiß.push_back({{feld[0], feld[1]}});
        }
      }
      
      
      if (figur == 'p') {
        
        for (array<int, 2> feld : angegriffeneFelderPawn(figurPos, "schwarz")) {
          angriffe.schwarz.push_back({{feld[0], feld[1]}});
        }
      }
      
      if (figur == 'n') {
        for (array<int, 2> feld : angegriffeneFelderKnight(figurPos)) {
          angriffe.schwarz.push_back({{feld[0], feld[1]}});
        }
      }
      
      if (figur == 'b') {
        for (array<int, 2> feld : angegriffeneFelderBishop(figurPos, brettState, weißAmZug)) {
          angriffe.schwarz.push_back({{feld[0], feld[1]}});
        }
      }
      
      if (figur == 'r') {
        for (array<int, 2> feld : angegriffeneFelderRook(figurPos, brettState, weißAmZug)) {
          angriffe.schwarz.push_back({{feld[0], feld[1]}});
        }
      }
      
      if (figur == 'q') {
        for (array<int, 2> feld : angegriffeneFelderQueen(figurPos, brettState, weißAmZug)) {
          angriffe.schwarz.push_back({{feld[0], feld[1]}});
        }
      }
      
      if (figur == 'k') {
        for (array<int, 2> feld : angegriffeneFelderKing(figurPos, brettState, weißAmZug)) {
          angriffe.schwarz.push_back({{feld[0], feld[1]}});
        }
      }
      
    }
  }
  return angriffe;
}


void moeglicheZuegeAusgeben(vector<array<int, 2>> moeglicheZuege, string figur) {
  cout << figur << " wurde bewegt" << endl; 
  cout << "Anzahl möglicher Züge: " << moeglicheZuege.size() << endl;
  
  
  char moeglicheZuegeFigur[8][8] = {
      {'.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.'},
  };
  
  
  for (array<int, 2> zugArr : moeglicheZuege) {
    int i = zugArr[0];
    int j = zugArr[1];
    
    moeglicheZuegeFigur[i][j] = 'X';
    
    cout << zugArr[0] << ", " << zugArr[1] << endl;
  }
  // nur noch gesamte darstellung ausgeben:
  cout << "---------------" << endl;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      cout << moeglicheZuegeFigur[i][j] << " ";
    }
    cout << endl;
  }
  cout << "---------------" << endl;
}

// eigentlich die selbe funktion wie oben, aber die hier ist vor allem zum testen - entweder also zusammenfassen oder die hier löschen
void angegriffeneFelderAusgeben(vector<array<int, 2>> angegriffeneFelder, string figur) {
  cout << "Angegriffene Felder: " << angegriffeneFelder.size() << endl;
  
  
  char angegriffeneFelderMap[8][8] = {
      {'.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.'},
  };
  
  
  for (array<int, 2> zugArr : angegriffeneFelder) {
    int i = zugArr[0];
    int j = zugArr[1];
    
    angegriffeneFelderMap[i][j] = 'A';
    
    cout << zugArr[0] << ", " << zugArr[1] << endl;
  }
  // nur noch gesamte darstellung ausgeben:
  cout << "---------------" << endl;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      cout << angegriffeneFelderMap[i][j] << " ";
    }
    cout << endl;
  }
  cout << "---------------" << endl;
}


void sayHello() {
  cout << "hello!" << endl;
}
