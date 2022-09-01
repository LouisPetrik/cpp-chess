//
//  King.h
//  cpp-chess
//
//  Created by Louis Petrik on 01.09.22.
//

#ifndef King_h
#define King_h

#include <vector>
#include <array>
#include <iostream>

using namespace std;


bool koordAufBrett(int iVariation, int jVariation);

bool zielfeldLegitim(int iVariation, int jVariation);

vector<array<int, 2>> angegriffeneFelderKing(int ausgangsfeldKoord[2], char brettState[8][8], bool weißAmZug);

vector<array<int, 2>> moeglicheZuegeKing(int ausgangsfeldKoord[2], char brettState[8][8], bool weißAmZug, char angriffeWeiße[8][8], char angriffeSchwarz[8][8]);



#endif /* King_h */
