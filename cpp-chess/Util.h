//
//  Util.h
//  cpp-chess
//
//  Created by Louis Petrik on 25.08.22.
//

#ifndef Util_h
#define Util_h

using namespace std; 

void sayHello();


int *feldbezeichnungZuKoord(string feld); 

int *figurFinden(char figurZeichen, char brettState[8][8]);



#endif /* Util_h */
