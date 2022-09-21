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


// Dieses Struct dient zum zusammenfassen von angriffen für beide seiten in der variable "angriffe".
struct angriffeType {
  vector<array<int, 2>> weiß;
  vector<array<int, 2>> schwarz;
};



bool istWeißeFigur(char brettChar);

bool istSchwarzeFigur(char brettChar);


string generiereFEN(char brettState[8][8]); 

angriffeType angriffeFinden(char brettState[8][8], bool weißAmZug);

int *feldbezeichnungZuKoord(string feld); 

int *figurFinden(char figurZeichen, char brettState[8][8]);

void moeglicheZuegeAusgeben(vector<array<int, 2>> moeglicheZuege, string figur);


void angegriffeneFelderAusgeben(vector<array<int, 2>>, string figur);

bool feldInAngriffen(vector<array<int, 2>> angriffe, int pos[2]); 



#endif /* Util_h */
