//
//  Pawn.h
//  cpp-chess
//
//  Created by Louis Petrik on 26.08.22.
//

#ifndef Pawn_h
#define Pawn_h


#include <vector>
#include <stdio.h>
#include <iostream>
#include <array>



using namespace std; 


void pawnFunction(int num);

vector<array<int, 2>> moeglicheZuegePawn(int ausgangsfeldKoord[2], char brettState[8][8], bool weißAmZug, int enPassantBauer[2]);


vector<array<int, 2>> angegriffeneFelderPawn(int ausgangsfeldKoord[2], string farbe);



#endif /* Pawn_h */
