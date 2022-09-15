//
//  FischerChess.cpp
//  cpp-chess
//
//  Created by Louis Petrik on 15.09.22.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <array>

using namespace std;

void positionGenerieren() {
  
  
    
  // für die position werden die jeweiligen Figuren (erstmal nur für weiß, da für schwarz selbe stellung)
  // nach und nach in das array eingetragen.
  char figuren[8] = {'.', '.', '.', '.', '.', '.', '.', '.'};
  
  // vermutlich hinfällig, da man das auch so einfach abgefragen kann.
  int weißeIndizies[4] = {1, 3, 5, 7};
  int schwarzeIndizies[4] = {0, 2, 4, 6};
  

  
  int posKing = (1 + ( std::rand() % ( 6 - 1 + 1 ) ));
  
  // links neben dem könig ist nun auf den feldern von 0 - (posKing - 1) platz
  // rechts nebem könig ist nun von feldern (posKing + 1) - 7 platz
  
  int posLinkerTurm = (0 + ( std::rand() % ( (posKing - 1) - 0 + 1 ) ));
  
  
  int posRechterTurm = ((posKing + 1) + ( std::rand() % ( 7 - (posKing + 1) + 1 ) ));

  
  
  figuren[posKing] = 'K';
  figuren[posLinkerTurm] = 'R';
  figuren[posRechterTurm] = 'R';
  
  // jetzt zu den läufern:
  int weißfeldigerBishop = 0;
  
  while (weißfeldigerBishop == 0 || weißfeldigerBishop == 2 || weißfeldigerBishop == 4 || weißfeldigerBishop == 6 || figuren[weißfeldigerBishop] != '.') {
    weißfeldigerBishop = (0 + ( std::rand() % ( 7 - 0 + 1 ) ));
  }
  
  figuren[weißfeldigerBishop] = 'B';
  

  
  // das gleiche für den schwarzfeldigen bishop:
  
  int schwarzfeldigerBishop = 0;
  
  while (schwarzfeldigerBishop == 1 || schwarzfeldigerBishop == 3 || schwarzfeldigerBishop == 5 || schwarzfeldigerBishop == 7 || figuren[schwarzfeldigerBishop] != '.') {
    schwarzfeldigerBishop = (0 + ( std::rand() % ( 7 - 0 + 1 ) ));
  }
  
  figuren[schwarzfeldigerBishop] = 'B';
  
  // für das erste pferd:
  int knight1 = 0;
  
  while (figuren[knight1] != '.') {
    knight1 = (0 + ( std::rand() % ( 7 - 0 + 1 ) ));
  }
  figuren[knight1] = 'N';
  
  // das zweite pferd:
  int knight2 = 0;
  
  while (figuren[knight2] != '.') {
    knight2 = (0 + ( std::rand() % ( 7 - 0 + 1 ) ));
  }
  figuren[knight2] = 'N';
  
  // die dame:
  int queen = 0;
  
  while(figuren[queen] != '.') {
    queen = (0 + ( std::rand() % ( 7 - 0 + 1 ) ));
  }
  figuren[queen] = 'Q';
  
  
  
  cout << "position: " << endl;
  
  for (int i = 0; i < 8; i++) {
    cout << figuren[i] << "";
  }
  cout << endl;
  cout << "----------------------" << endl;
  
  
}
