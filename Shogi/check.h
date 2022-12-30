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

bool CheckMate(char **b, int turn) {
	
	coordinate king = findKing(b, turn);
	coordinate* kingsMoves; int a = 0;
	kingsMoves = new coordinate[8];
	//storing king's potential moves in an array
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			coordinate kingDC; kingDC.ri = i; kingDC.ci = j;
			if (isMoveLegal(b, king, kingDC, turn)) {
				kingsMoves[a++] = kingDC;
			}
		}
	}

	return false;
}