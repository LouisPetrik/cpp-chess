//
//  Util.cpp
//  cpp-chess
//
//  Created by Louis Petrik on 25.08.22.
//

#include <stdio.h>
#include <iostream>

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



void sayHello() {
  cout << "hello!" << endl;
}
