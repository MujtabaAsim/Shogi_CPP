#pragma once


void promotionReplacement(char** &b, coordinate PC) {

	char piece = b[PC.ri][PC.ci];

	switch (piece) {
	//blacks
	case 'p':
	case 'n':
	case 'l':
	case 's':
		b[PC.ri][PC.ci] = 'g';
		break;
	case 'b':
		b[PC.ri][PC.ci] = 'h';
		break;
	case 'r':
		b[PC.ri][PC.ci] = 'd';
		break;
	//whites
	case 'P':
	case 'N':
	case 'L':
	case 'S':
		b[PC.ri][PC.ci] = 'G';
		break;
	case 'B':
		b[PC.ri][PC.ci] = 'H';
		break;
	case 'R':
		b[PC.ri][PC.ci] = 'D';
		break;
	}
}

bool yesNoInput() {
	char input;
	do {
		cin >> input;
		input = tolower(input);
	} while (input != 'y' or input != 'n');
	if (input == 'y') {
		return true;
	}
	else {
		return false;
	}
}

bool wantToPromotePiece(char** b, coordinate PC) {
	char piece = b[PC.ri][PC.ci];

	switch (piece) {
	case 'p':
	case 'n':
	case 'l':
	case 's':
		cout << "Promote " << piece << " at " << PC.ri + 1 << ", " << PC.ci + 1 << " to " << "Golden General? (Y/N): ";
		return yesNoInput();
		break;
	case 'b':
		cout << "Promote " << piece << " at " << PC.ri + 1 << ", " << PC.ci + 1 << " to " << "Horse? (Y/N): ";
		return yesNoInput();
		break;
	case 'r':
		cout << "Promote " << piece << " at " << PC.ri + 1 << ", " << PC.ci + 1 << " to " << "Dragon? (Y/N): ";
		return yesNoInput();
		break;

	case 'P':
	case 'N':
	case 'L':
	case 'S':
		cout << "Promote " << piece << " at " << PC.ri + 1 << ", " << PC.ci + 1 << " to " << "Golden General? (Y/N): ";
		return yesNoInput();
		break;
	case 'B':
		cout << "Promote " << piece << " at " << PC.ri + 1 << ", " << PC.ci + 1 << " to " << "Horse? (Y/N): ";
		return yesNoInput();
		break;
	case 'R':
		cout << "Promote " << piece << " at " << PC.ri + 1 << ", " << PC.ci + 1 << " to " << "Dragon? (Y/N): ";
		return yesNoInput();
		break;
	}
	return false;
}

bool isSelectedPiecePromotable(char piece) {
	char pieces[12] = { 'b', 'B', 'p',  'P',  'n',  'N',  's',  'S',  'l',  'L',  'r', 'R' };
	for (int i = 0; i < 12; i++) {
		if (pieces[i] == piece) {
			return true;
		}
	}
	return false;
}

void addToPromotionMap(int**& pBoard, coordinate PC, char piece) {
	switch (piece) {
	case 'p':
		pBoard[PC.ri][PC.ci] = 1;
		break;
	case 'n':
		pBoard[PC.ri][PC.ci] = 2;
		break;
	case 'l':
		pBoard[PC.ri][PC.ci] = 3;
		break;
	case 's':
		pBoard[PC.ri][PC.ci] = 4;
		break;
	case 'b':
		pBoard[PC.ri][PC.ci] = 5;
		break;
	case 'r':
		pBoard[PC.ri][PC.ci] = 6;
		break;
	case 'P':
		pBoard[PC.ri][PC.ci] = 7;
		break;
	case 'N':
		pBoard[PC.ri][PC.ci] = 8;
		break;
	case 'L':
		pBoard[PC.ri][PC.ci] = 9;
		break;
	case 'S':
		pBoard[PC.ri][PC.ci] = 10;
		break;
	case 'B':
		pBoard[PC.ri][PC.ci] = 11;
		break;
	case 'R':
		pBoard[PC.ri][PC.ci] = 12;
		break;
	}
}

void  promotionCheck(char** b, coordinate PC, int turn, bool fromDrop, int** pBoard) {
	char piece = b[PC.ri][PC.ci];
	
	if (turn == black) {
		if (PC.ri < 3) {
			if (piece == 'p' and PC.ri == 0) {
				promotionReplacement(b, PC);
				addToPromotionMap(pBoard, PC, piece);
			} else if (piece == 'k' and PC.ri < 2 ) {
				promotionReplacement(b, PC);
				addToPromotionMap(pBoard, PC, piece);
			} else if (isSelectedPiecePromotable(piece)) {
				if (wantToPromotePiece(b, PC)) {
					promotionReplacement(b, PC);
					addToPromotionMap(pBoard, PC, piece);
				}
			}
		}
	}
	else {
		if (PC.ri > 5) {
			if (piece == 'P' and PC.ri == 8) {
				promotionReplacement(b, PC);
				addToPromotionMap(pBoard, PC, piece);
			}
			else if (piece == 'N' and PC.ri > 6) {
				promotionReplacement(b, PC);
				addToPromotionMap(pBoard, PC, piece);
			}
			else if (isSelectedPiecePromotable(piece)) {
				if (wantToPromotePiece(b, PC)) {
					promotionReplacement(b, PC);
					addToPromotionMap(pBoard, PC, piece);
				}
			}
		}
	}
}