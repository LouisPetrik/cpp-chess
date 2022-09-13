//
//  remis.h
//  cpp-chess
//
//  Created by Louis Petrik on 06.09.22.
//

#ifndef remis_h
#define remis_h



bool farbeStehtImPatt(char brettState[8][8], bool weißAmZug, char angriffeWeiß[8][8], char angriffeSchwarz[8][8], int enPassantBauer[2], int posWeißerKing[2], int posSchwarzerKing[2]);

bool unzureichendesMaterial(char brettState[8][8]); 

#endif /* remis_h */
