//
//  Knight.h
//  cpp-chess
//
//  Created by Louis Petrik on 29.08.22.
//

#ifndef Knight_h
#define Knight_h

#include <vector>
#include <stdio.h>
#include <iostream>
#include <array>

using namespace std;

bool zielfeldLegitim(char[8][8] brettState, int iVariation, int jVariation, bool weißAmZug);

bool koordInnerhalbBrett(int iVariation, int jVariation);

vector<array<int, 2>> angegriffeneFelderKnight(int ausgangsfeldKoord[2]);


#endif /* Knight_h */
