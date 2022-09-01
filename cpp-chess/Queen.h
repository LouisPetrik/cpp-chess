//
//  Queen.h
//  cpp-chess
//
//  Created by Louis Petrik on 01.09.22.
//

#ifndef Queen_h
#define Queen_h

#include "Linie.h"
#include "diagonale.h"
#include <vector>
#include <array>
#include <iostream>

using namespace std;


vector<array<int, 2>> angegriffeneFelderQueen(int ausgangsfeldKoord[2], char brettState[8][8], bool weißAmZug);


vector<array<int, 2>> moeglicheZuegeQueen(int ausgangsfeldKoord[2], char brettState[8][8], bool weißAmZug);

#endif /* Queen_h */
