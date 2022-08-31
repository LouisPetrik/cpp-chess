//
//  Rook.h
//  cpp-chess
//
//  Created by Louis Petrik on 31.08.22.
//

#ifndef Rook_h
#define Rook_h

#include <vector>
#include <array>
#include <iostream>

using namespace std;

vector<array<int, 2>> angegriffeneFelderRook(int ausgangsfeldKoord[2], char brettState[8][8], bool weißAmZug);


vector<array<int, 2>> moeglicheZuegeRook(int ausgangsfeldKoord[2], char brettState[8][8], bool weißAmZug);

#endif /* Rook_h */
