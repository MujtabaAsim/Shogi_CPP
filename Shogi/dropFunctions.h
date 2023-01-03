#pragma once
#include "captureFunctions.h"

char pickPieceFromHand(int turn, char hand[2][cap], int handCounter[], int &pieceIndex) {
	cout << "Pick a piece number from your hand: ";
	int pieceNumber;
	do {cin >> pieceNumber;} while (pieceNumber < 1 or pieceNumber > handCounter[turn]);
	pieceNumber--;
	return hand[turn][pieceNumber];
	pieceIndex = pieceNumber;
}

bool ThisPieceHasALegalMove(char** b, char piece, coordinate sc, int turn) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			coordinate dc{ i, j };
			if (validSC(b, sc, turn) and isMoveLegal(b, sc, dc, turn)) {
				return true;
			}
		}
	}
	return false;
}

bool isDropValid(char** b, coordinate dc, int turn, char piece, char hand[2][cap], int handCounter[]) {
	//if out of bounds
	if (!validDC(b, dc, turn)) {
		return false;
	}
	//if not empty
	if (b[dc.ri][dc.ci] != '-') {
		return false;
	}
	//dropped pawn can not have another friendly pawn in the same column
	if (turn == black) {
		if (piece == 'p') {
			
			for (int i = 0; i < size; i++) {
				if (b[dc.ri][i] == piece) {
					cout << "This pawn can not be placed in this column because another friendly pawn already exists.";
					return false;
				}
			}
		}
	}
	else {
		if (piece == 'P') {
			for (int i = 0; i < size; i++) {
				if (b[i][dc.ci] == piece) {
					cout << "This pawn can not be placed in this column because another friendly pawn already exists.";
					return false;
				}
			}
		}
	}
	//dropped piece has to have at least one legal move
	tempDrop(b, dc, piece);
	if (!ThisPieceHasALegalMove(b, piece, dc, turn)) {
		undoTempDrop(b, dc);
		cout << "This piece does not have a valid legal move at that position.";
		return false;
	}
	undoTempDrop(b, dc);
	//dropped pawn can not give an immediate checkmate
	tempDrop(b, dc, piece);
	if ((piece == 'P' or piece == 'p') and (checkMate(b, turn, hand, handCounter))) {
		undoTempDrop(b, dc);
		cout << "Placing this " << charToPieceName(piece) << " at that position will cause a checkmate.";
		return false;
	}
	undoTempDrop(b, dc);
	return true;
}