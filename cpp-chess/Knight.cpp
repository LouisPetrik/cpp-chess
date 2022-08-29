#include <stdio.h>
#include <vector>
#include <iostream>
#include <array>
#include <iostream>
#include <algorithm>

using namespace std;

const char schwarzeFiguren[6] = {'p', 'r', 'q', 'b', 'n', 'k'};
const char weißeFiguren[6] = {'P', 'R', 'Q', 'B', 'N', 'K'};


// hilfsfunktion funktion, die testet, ob eine versuchte koordinate überhaupt noch auf brett ist,
bool koordInnerhalbBrett(int iVariation, int jVariation) {
  if (
      iVariation >= 0 &&
      jVariation >= 0 &&
      iVariation <= 7 &&
      jVariation <= 7
    ) {
      return true;
    } else {
      return false;
    }
}

// hilfsfunktion
bool zielfeldLegitim(char brettState[8][8], int iVariation, int jVariation, bool weißAmZug) {
  
  if (
    iVariation >= 0 &&
    jVariation >= 0 &&
    iVariation <= 7 &&
    jVariation <= 7
      ) {
        
        if (weißAmZug) {
          // insofern dort keine eigene Figur steht, wird true returned, damit ist das zielfeld legitim.
          return !(std::find(weißeFiguren, weißeFiguren + 6, brettState[iVariation][jVariation]) != weißeFiguren + 6);
        }
        
        if (!weißAmZug) {
          return !(std::find(schwarzeFiguren, schwarzeFiguren + 6, brettState[iVariation][jVariation]) != schwarzeFiguren + 6);
        }
      }
  
  // quasi als "else" und damit sich compiler nicht beschwert. 
  return false;
}




vector<array<int, 2>> angegriffeneFelderKnight(int ausgangsfeldKoord[2]) {
  vector<array<int, 2>> felder;
  
  const int i = ausgangsfeldKoord[0];
  const int j = ausgangsfeldKoord[1];
  
  if (koordInnerhalbBrett(i - 2, j - 1)) {
    array<int, 2> feld { {i - 2, j - 1} };
    felder.push_back(feld);
  }

  if (koordInnerhalbBrett(i - 2, j + 1)) {
    array<int, 2> feld { {i - 2, j + 1} };
    felder.push_back(feld);
  }

  if (koordInnerhalbBrett(i - 1, j - 2)) {
    array<int, 2> feld { {i - 1, j - 2} };
    felder.push_back(feld);
  }

  if (koordInnerhalbBrett(i - 1, j + 2)) {
    array<int, 2> feld { {i - 1, j + 2} };
    felder.push_back(feld);
  }

  if (koordInnerhalbBrett(i + 1, j - 2)) {
    array<int, 2> feld { {i + 1, j - 2} };
    felder.push_back(feld);
  }

  if (koordInnerhalbBrett(i + 1, j + 2)) {
    array<int, 2> feld { {i + 1, j + 2} };
    felder.push_back(feld);
  }

  if (koordInnerhalbBrett(i + 2, j - 1)) {
    array<int, 2> feld { {i + 2, j - 1} };
    felder.push_back(feld);
  }

  if (koordInnerhalbBrett(i + 2, j + 1)) {
    array<int, 2> feld { {i + 2, j + 1} };
    felder.push_back(feld);
  }

  if (koordInnerhalbBrett(i + 2, j - 1)) {
    array<int, 2> feld { {i + 2, j - 1} };
    felder.push_back(feld);
  }

  if (koordInnerhalbBrett(i + 2, j + 1)) {
    array<int, 2> feld { {i + 2, j + 1} };
    felder.push_back(feld);
  }
  
  
  return felder;
  
}


