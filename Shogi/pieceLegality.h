#pragma once

#include "directionalLegality.h"



bool silverGenLegality(char** b, coordinate sc, coordinate dc, int turn) {
	int deltaR = abs(sc.ri - dc.ri);
	int deltaC = abs(sc.ci - dc.ci);
	if (turn == black) {
		return ((deltaR < 2 and deltaC < 2) and (isDiagonal(sc, dc) or (dc.ri == sc.ri - 1)));
	}
	else {
		return ((deltaR < 2 and deltaC < 2) and (isDiagonal(sc, dc) or (dc.ri == sc.ri + 1)));
	}
}

bool goldenGenLegality(char** b, coordinate sc, coordinate dc, int turn) {
	int deltaR = abs(sc.ri - dc.ri);
	int deltaC = abs(sc.ci - dc.ci);
	if (turn == black) {
		return ((deltaR < 2 and deltaC < 2) and (isHorizontal(sc, dc) or isVertical(sc, dc) or (dc.ri == sc.ri - 1 and deltaC == 1)));
	}
	else {
		return ((deltaR < 2 and deltaC < 2) and (isHorizontal(sc, dc) or isVertical(sc, dc) or (dc.ri == sc.ri + 1 and deltaC == 1)));
	}
}

bool kingLegality(char** b, coordinate sc, coordinate dc){
	int deltaR = abs(sc.ri - dc.ri);
	int deltaC = abs(sc.ci - dc.ci);
	return (deltaR < 2 and deltaC < 2);
}

bool pawnLegality(char** b, coordinate sc, coordinate dc, int turn) {
	if (turn == black) {
		return (isVertical(sc, dc) and dc.ri == sc.ri - 1);
	} else {
		return (isVertical(sc, dc) and dc.ri == sc.ri + 1);
	}
}

bool rookLegality(char** b, coordinate sc, coordinate dc) {
	return (isHorizontal(sc, dc) and horizontalPC(b, sc, dc)) or (isVertical(sc, dc) and verticalPC(b, sc, dc));
}

bool bishopLegality(char** b, coordinate sc, coordinate dc) {
	return isDiagonal(sc, dc) and (diagonal1PC(b, sc, dc) or (diagonal2PC(b, sc, dc)));
}

bool lanceLegality(char** b, coordinate sc, coordinate dc, int turn) {
	if (turn == black) {
		return isVertical(sc, dc) and verticalPC(b, sc, dc) and sc.ri > dc.ri;
	}
	else {
		return isVertical(sc, dc) and verticalPC(b, sc, dc) and sc.ri < dc.ri;
	}
}

bool knightLegality(char** b, coordinate sc, coordinate dc, int turn) {
	int deltaC = abs(sc.ci - dc.ci);
	if (turn == black) {
		return (dc.ri == sc.ri - 2 and deltaC == 1);
	}
	else {
		return (dc.ri == sc.ri + 2 and deltaC == 1);
	}
}

bool promotedBishopLegality(char** b, coordinate sc, coordinate dc) {
	int deltaR = abs(sc.ri - dc.ri);
	int deltaC = abs(sc.ci - dc.ci);
	return ((deltaR < 2 and deltaC < 2) or bishopLegality(b, sc, dc));
}

bool promotedRookLegality(char** b, coordinate sc, coordinate dc) {
	int deltaR = abs(sc.ri - dc.ri);
	int deltaC = abs(sc.ci - dc.ci);
	return ((deltaR < 2 and deltaC < 2) or rookLegality(b, sc, dc));
}