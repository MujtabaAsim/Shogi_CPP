#pragma once
#include "auxiliary.h"
#include <math.h>

//these will be used in piecelegality.h

bool isHorizontal(coordinate sc, coordinate dc) {
	return sc.ri == dc.ri;
}

bool isVertical(coordinate sc, coordinate dc) {
	return sc.ci == dc.ci;
}

bool isDiagonal(coordinate sc, coordinate dc) {
	int vert = dc.ri - sc.ri;
	int hori = dc.ci - sc.ci;
	return (abs(hori) == abs(vert)) and hori != 0 and vert != 0;
}

bool horizontalPC(char** b, coordinate sc, coordinate dc) {
	if (dc.ci > sc.ci) {
		for (int c = dc.ci - 1; c > sc.ci; c--) {
			if (b[dc.ri][c] != '-') {
				return false;
			}
		}
		return true;
	}
	else {
		for (int c = dc.ci + 1; c < sc.ci; c++) {
			if (b[dc.ri][c] != '-') {
				return false;
			}
		}
		return true;
	}
}

bool verticalPC(char** b, coordinate sc, coordinate dc) {
	int col = dc.ci;
	if (dc.ri > sc.ri) {
		for (int r = dc.ri - 1; r > sc.ri; r--) {
			if (b[r][col] != '-') {
				return false;
			}
		}
		return true;
	}
	else {
		for (int r = dc.ri + 1; r < sc.ri; r++) {
			if (b[r][col] != '-') {
				return false;
			}
		}
		return true;
	}
}

bool diagonal1PC(char** b, coordinate sc, coordinate dc) {
	int DeltaR = abs(dc.ri - sc.ri) + 1;
	if (sc.ri < dc.ri) {
		for (int i = 1; i < DeltaR; i++) {
			if (b[sc.ri + i][sc.ci + i] != '-') {
				return false;
			}
		}
	}
	else {
		for (int i = 1; i < DeltaR; i++) {
			if (b[sc.ri - i][sc.ci - i] != '-') {
				return false;
			}
		}
	}
	return true;
}

bool diagonal2PC(char** b, coordinate sc, coordinate dc) {
	int DeltaR = abs(dc.ri - sc.ri) + 1;
	if (sc.ri < dc.ri) {
		for (int i = 1; i < DeltaR; i++) {
			if (b[sc.ri + i][sc.ci - i] != '-') {
				return false;
			}
		}
	}
	else {
		for (int i = 1; i < DeltaR; i++) {
			if (b[sc.ri - i][sc.ci + i] != '-') {
				return false;
			}
		}
	}
	return true;
}