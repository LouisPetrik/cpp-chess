//
//  Bishop.h
//  cpp-chess
//
//  Created by Louis Petrik on 01.09.22.
//

#ifndef Bishop_h
#define Bishop_h

#include "Linie.h"
#include <vector>
#include <array>


vector<array<int, 2>> angegriffeneFelderBishop(int ausgangsfeldKoord[2], char brettState[8][8], bool weißAmZug);

vector<array<int, 2>> moeglicheZuegeBishop(int ausgangsfeldKoord[2], char brettState[8][8], bool weißAmZug);




#endif /* Bishop_h */
