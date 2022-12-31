#pragma once
#include "basicLegalityFunctions.h"

bool** computeHighlight(char** b, coordinate sc, int turn) {
    bool** returnA = new bool* [size];
    for (int i = 0; i < size; i++) {
        returnA[i] = new bool[size] {false};
    }
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            coordinate dc { r, c };
            if (validDC(b, dc, turn) and isMoveLegal(b, sc, dc, turn)) {
                returnA[r][c] = true;
            }
        }
    }
    return returnA;
}

void highlight(bool** highlightMap, char**& b, char* &coveredPieces) {
    int a = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (highlightMap[i][j]) {
                if (b[i][j] == '-') {
                    b[i][j] = 'X';
                }
                else {
                    coveredPieces[a] = b[i][j]; a++;
                    b[i][j] = 'O';
                }
            }
        }
    }
}

void unhighlight(bool** highlightMap, char** b, char* &coveredPieces) {
    int a = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (highlightMap[i][j]) {
                if (b[i][j] == 'X') {
                    b[i][j] = '-';
                }
                else {
                    b[i][j] = coveredPieces[a]; a++;
                }
            }
        }
    }
}