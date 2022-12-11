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
	return (abs(hori) == abs(vert)) and abs(hori) != 0 and abs(vert) != 0;
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
	int dr, r, c;
	if (sc.ri < dc.ri) {
		dr = dc.ri - sc.ri - 1;
		r = sc.ri;
		c = sc.ci;
	}
	else {
		dr = sc.ri - dc.ri - 1;
		r = dc.ri;
		c = dc.ci;
	}
	for (int i = 1; i <= dr; i++) {
		if (b[r + i][c + i] != '-') {
			return false;
		}
	}
	return true;
}

bool diagonal2PC(char** b, coordinate sc, coordinate dc) {
	int DC, r, c;
	if (sc.ci < dc.ci) {
		DC = dc.ci - sc.ci - 1;
		r = sc.ri;
		c = sc.ci;
	}
	else {
		DC = sc.ci - dc.ci - 1;
		r = dc.ri;
		c = dc.ci;
	}
	for (int i = 1; i <= DC; i++) {
		if (b[r - i][c + i] != '-') {
			return false;
		}
	}
	return true;
}