#pragma once

coordinate findKing(char** b, int turn) {
	if (turn == black) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (b[i][j] == 'k') {
					coordinate dc{ i, j };
					return dc;
				}
			}
		}
	}
	else {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (b[i][j] == 'K') {
					coordinate dc{ i, j };
					return dc;
				}
			}
		}
	}
	return dc;
}

bool check(char** b, int turn) {
	turnChange(turn);
	coordinate dc = findKing(b, turn);
	turnChange(turn);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			coordinate sc { i, j };
			if (validSC(b, sc, turn) and isMoveLegal(b, sc, dc, turn)) {
				return true;
			}
		}
	}
	return false;
}

bool selfCheck(char** b, int turn) {
	turnChange(turn);
	return check(b, turn);
}

bool checkMate(char **b, int turn) {
	//1.___SEE IF THE KING CAN SAVE ITSELF
		if (selfCheck(b, turn) == false) { //if, at any given point, the king is NOT in check, then it obviously can't be in a mate.
			return false;
		}
	//2.___SEE IF OTHER PIECES CAN SAVE THE KING
		coordinate* validSCs; int NumOfSCs = 0;
		validSCs = new coordinate[20];
		for (int r = 0; r < size; r++) {
			for (int c = 0; c < size; c++) {
				coordinate sc { r, c };
				if (validSC(b, sc, turn)) {
					validSCs[NumOfSCs++] = sc;
				}
			}
		}
		for (int i = 0; i < NumOfSCs; i++) {
			for (int r = 0; r < size; r++) {
				for (int c = 0; c < size; c++) {
					coordinate dc { r, c };
					updateBoardTemp(b, validSCs[i], dc);
					if (selfCheck(b, turn) == false) { //if, after another friendly piece has moved, the king is no longer in check, then it obviously can't be in a mate.
						undoTempBoardUpdate(b, validSCs[i], dc);
						return false;
					}
					undoTempBoardUpdate(b, validSCs[i], dc);
				}
			}
		}
	//3.___SEE IF DROPPABLE PIECES CAN SAVE THE KING
		
		
	return true;
}