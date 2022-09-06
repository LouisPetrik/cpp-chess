//
//  diagonale.h
//  cpp-chess
//
//  Created by Louis Petrik on 01.09.22.
//

#ifndef diagonale_h
#define diagonale_h

#include <stdio.h>
#include <iostream>
#include <array>
#include <vector>

using namespace std;


// char brettState[8][8], int ausgangsfeldKoord[2], string richtung, string modus, bool weißAmZug


vector<array<int, 2>> diagonaleFelder(char brettState[8][8], int ausgangsfeldKoord[2], string richtung, string modus, bool weißAmZug); 



#endif /* diagonale_h */
