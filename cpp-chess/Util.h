//
//  Util.h
//  cpp-chess
//
//  Created by Louis Petrik on 25.08.22.
//

#ifndef Util_h
#define Util_h

#include <vector>
#include <iostream>

using namespace std; 

void sayHello();


int *feldbezeichnungZuKoord(string feld); 

int *figurFinden(char figurZeichen, char brettState[8][8]);

void moeglicheZuegeAusgeben(vector<array<int, 2>> moeglicheZuege, string figur);



#endif /* Util_h */
