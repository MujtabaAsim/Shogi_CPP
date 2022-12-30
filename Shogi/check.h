#pragma once

coordinate findKing(char** b, int turn) {
	coordinate dc; dc.ri = 0; dc.ci = 0;
	if (turn == black) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (b[i][j] == 'k') {
					dc.ri = i; dc.ci = j; 
					return dc;
				}
			}
		}
	}
	else {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (b[i][j] == 'K') {
					dc.ri = i; dc.ci = j; 
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
			coordinate sc; sc.ri = i; sc.ci = j;
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
	//___SEE IF THE KING CAN SAVE ITSELF
	coordinate kingSC = findKing(b, turn);
	coordinate* kingsMoves; int a = 0;
	kingsMoves = new coordinate[12];
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			coordinate kingDC; kingDC.ri = i; kingDC.ci = j;
			if (isMoveLegal(b, kingSC, kingDC, turn)) {
				kingsMoves[a++] = kingDC;
			}
		}
	}
	for (int i = 0; i < a; i++) {
		if (!selfCheck(b, turn)) {
			return true;
		}
	}
	//___SEE IF OTHER PIECES CAN SAVE THE KING
	coordinate* validSCs; int a;
	validSCs = new coordinate[20];
	for (int r = 0; r < size; r++) {
		for (int c = 0; c < size; c++) {
			coordinate sc; sc.ri = r, sc.ci = c;
			if (validSC(b, sc, turn)) {
				validSCs[a++] = sc;
			}
		}
	}
	for (int i = 0; i < a; i++) {
		for (int r = 0; r < size; r++) {
			for (int c = 0; c < size; c++) {
				coordinate dc; dc.ri = r, dc.ci = c;
				if (isMoveLegal(b, validSCs[i], dc, turn) and validDC(b, dc, turn)) {
					updateBoardTemp(b, validSCs[i], dc);
					if (!selfCheck(b, turn)) {
						undoTempBoardUpdate(b, validSCs[i], dc);
						return true;
					}
					undoTempBoardUpdate(b, validSCs[i], dc);
				}
			}
		}
	}
	return false;
}