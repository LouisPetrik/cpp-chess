//
//  EngineUtil.h
//  cpp-chess
//
//  Created by Louis Petrik on 07.09.22.
//

#ifndef EngineUtil_h
#define EngineUtil_h

#include <vector>
#include <array>
#include <iostream>


using namespace std;


typedef array<array<char, 8>, 8> brett;


brett brettStateDurchFigur(char brettState[8][8], int position[2], int enPassantBauer[2], array<int, 2> zielfeld, char figurZeichen); 

vector<brett> moeglicheBrettStates(char brettState[8][8], bool weißAmZug, int enPassantBauer[2], char angriffeWeiße[8][8], char angriffeSchwarz[8][8]);


#endif /* EngineUtil_h */
