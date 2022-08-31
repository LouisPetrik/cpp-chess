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

bool koordInnerhalbBrett(int iVariation, int jVariation);

bool zielfeldLegitim(char brettState[8][8], bool weißAmZug, int iVariation, int jVariation);

vector<array<int, 2>> angegriffeneFelderKnight(int ausgangsfeldKoord[2]);

vector<array<int, 2>> moeglicheZuegeKnight(int ausgangsfeldKoord[2], char brettState[8][8], bool weißAmZug); 



#endif /* Knight_h */
