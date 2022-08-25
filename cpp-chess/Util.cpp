//
//  Util.cpp
//  cpp-chess
//
//  Created by Louis Petrik on 25.08.22.
//

#include <stdio.h>
#include <iostream>

using namespace std;


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
