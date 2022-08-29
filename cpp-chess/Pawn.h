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


// Diese funktion generiert alle möglichen Züge eines Bauerns - inklusive Schlagen, auch über en-passant.
vector<array<int, 2>> moeglicheZuegePawn(int ausgangsfeldKoord[2], char brettState[8][8], bool weißAmZug, int enPassantBauer[2]);

// Diese funktion generiert alle felder, die ein pawn angegreifen kann, also auf denen er schlagen kann.
vector<array<int, 2>> angegriffeneFelderPawn(int ausgangsfeldKoord[2], string farbe);



#endif /* Pawn_h */
