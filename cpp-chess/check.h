//
//  check.h
//  cpp-chess
//
//  Created by Louis Petrik on 12.09.22.
//

#ifndef check_h
#define check_h
#include <vector>
#include <array>

using namespace std;

vector<array<int, 2>> aufhebendeZuegeFigur(int posFigur[2], vector<array<int, 2>> zuege, char brettState[8][8], int posBetroffenerKing[2], string schachGegen);

bool istFigurAußerKing(char brettChar, string farbe); 

vector<array<int, 2>> istMatt(char brettState[8][8], string schachGegen, char angriffeWeiß[8][8], char angriffeSchwarz[8][8], int posBetroffenerKing[2], int enPassantBauer[2]); 


#endif /* check_h */
