//
//  diagonale.cpp
//  cpp-chess
//
//  Created by Louis Petrik on 01.09.22.
//

#include <stdio.h>
#include <vector>
#include <array>
#include <iostream>
#include "Util.h"

using namespace std;

const char schwarzeFiguren[6] = {'p', 'r', 'q', 'b', 'n', 'k'};
const char weißeFiguren[6] = {'P', 'R', 'Q', 'B', 'N', 'K'};

vector<array<int, 2>> diagonaleFelder(char brettState[8][8], int ausgangsfeldKoord[2], string richtung, string modus, bool weißAmZug)
{
  vector<array<int, 2>> felderAufDiagonale;

  const int i = ausgangsfeldKoord[0];
  const int j = ausgangsfeldKoord[1];

  bool geblockt = false;

  for (int x = 1; x <= 7; x++)
  {
    if (!geblockt)
    {
      int iTemp = i;
      int jTemp = j;

      if (richtung == "oben-rechts" && i - x >= 0 && j + x <= 7)
      {
        iTemp = i - x;
        jTemp = j + x;
      }

      if (richtung == "oben-links" && i - x >= 0 && j - x >= 0)
      {
        iTemp = i - x;
        jTemp = j - x;
      }

      if (richtung == "unten-rechts" && i + x <= 7 && j + x <= 7)
      {
        iTemp = i + x;
        jTemp = j + x;
      }

      if (richtung == "unten-links" && i + x <= 7 && j - x >= 0)
      {
        iTemp = i + x;
        jTemp = j - x;
      }

      if (modus == "angriff")
      {
        // wenn eine eigene oder gegnerische Figur gefunden wird, wird dieses Feld noch aufgenommen, da es angegriffen / gedeckt wird.
        if (brettState[iTemp][jTemp] != '.')
        {
          felderAufDiagonale.push_back({{iTemp, jTemp}});

          break;
        }
      }

      // std::find(weißeFiguren, weißeFiguren + 6, brettState[i][jTemp])

      if (modus == "zuege")
      {
        // insofern weiß eine gegnerische figur findet wird, ist das feld noch ziehbar.
        // Wenn es eine eigene figur ist, wird der weg dadurch geblockt und das feld selbst nicht aufgenommen.
        if (
            weißAmZug &&
            istSchwarzeFigur(brettState[iTemp][jTemp]))
        {
          felderAufDiagonale.push_back({{iTemp, jTemp}});
          // neu:
          geblockt = true;
          break;
        }

        // auf eigene figur gestoßen, feld wird nicht aufgenommen und loop abgebrochen
        if (
            weißAmZug &&
            istWeißeFigur(brettState[iTemp][jTemp]))
        {
          geblockt = true;
          break;
        }

        // wenn schwarz auf eine gegnerische figur stößt:
        if (
            !weißAmZug &&
            istWeißeFigur(brettState[iTemp][jTemp]))
        {
          felderAufDiagonale.push_back({{iTemp, jTemp}});
          // neu:
          geblockt = true;
          break;
        }
        
        // wenn schwarz auf eine eigenen figur stößt: 
        if (
            !weißAmZug &&
            istSchwarzeFigur(brettState[iTemp][jTemp]))
        {
          geblockt = true;
          break;
        }
      }

      // der standpunkt der figur selbst zählt nicht als angegriffen durch sich selbst und auch nicht als zug
      if (iTemp != i && jTemp != j)
      {
        felderAufDiagonale.push_back({{iTemp, jTemp}});
      }

      // kann vielleicht noch hinsichtlich der anzahl der durchläufe optimiert werden.
      if (iTemp == 0 || iTemp == 7 || jTemp == 0 || jTemp == 7)
      {
        break;
      }
    }
  }

  return felderAufDiagonale;
}
