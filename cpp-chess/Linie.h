/*
 Hilfsklasse mit hilfsfunktionen für das berechnen von linien auf dem brett, genutzt für Türme und Damen.
 */

#ifndef Linie_h
#define Linie_h

#include <vector>
#include <array>
#include <iostream>

using namespace std;

vector<array<int, 2>> linieFelder(char brettState[8][8], int ausgangsfeldKoord[2], string richtung, string modus, bool weißAmZug); 

#endif /* Linie_h */
