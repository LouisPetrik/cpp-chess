//
//  Castle.cpp
//  cpp-chess
//
//  Created by Louis Petrik on 01.09.22.
//

#include <stdio.h>
#include <vector>
#include <array>
#include <iostream>

using namespace std;


bool rochadeMoeglich(string typ, bool weißAmZug, char brettState[8][8], char angriffeWeiß[8][8], char angriffeSchwarz[8][8]) {
  
  bool moeglich = true;
  
  
  if (typ == "kurz" && weißAmZug) {
    // testen, ob der Turm auf h1 noch existiert und die Felder dazwischen frei sind.
    if (brettState[7][7] != 'R' || brettState[7][5] != '.' || brettState[7][6] != '.') {
      moeglich = false;
    }
    
    // testen, ob die felder f1 und g1 durch schwarz bedroht werden. Dann ist Rochade nicht erlaubt, da König darüber ziehen muss.
    if (angriffeSchwarz[7][5] == 'A' || angriffeSchwarz[7][6] == 'A') {
      moeglich = false;
    }
  }
  
  if (typ == "lang" && weißAmZug) {
    if (brettState[7][0] != 'R' || brettState[7][1] != '.' || brettState[7][2] != '.' || brettState[7][3] != '.') {
      moeglich = false;
    }
    
    // testen, ob die Felder, über die der König beim Rochieren ziehen würde, angegriffen werden.
    if (angriffeSchwarz[7][2] == 'A' || angriffeSchwarz[7][3] == 'A') {
      moeglich = false;
    }
  }
  
  // das gleiche spiel nur für schwarz:
  
  if (typ == "kurz" && !weißAmZug) {
    // testen, ob der Turm auf h1 noch existiert und die Felder dazwischen frei sind.
    if (brettState[0][7] != 'r' || brettState[0][5] != '.' || brettState[0][6] != '.') {
      moeglich = false;
    }
    
    // testen, ob die felder f1 und g1 durch schwarz bedroht werden. Dann ist Rochade nicht erlaubt, da König darüber ziehen muss.
    if (angriffeWeiß[0][5] == 'A' || angriffeWeiß[0][6] == 'A') {
      moeglich = false;
    }
  }
  
  if (typ == "lang" && !weißAmZug) {
    if (brettState[0][0] != 'r' || brettState[0][1] != '.' || brettState[0][2] != '.' || brettState[0][3] != '.') {
      moeglich = false;
    }
    
    // testen, ob die Felder, über die der König beim Rochieren ziehen würde, angegriffen werden.
    if (angriffeWeiß[0][2] == 'A' || angriffeWeiß[0][3] == 'A') {
      moeglich = false;
    }
  }
  
  
  return moeglich;
  
}
