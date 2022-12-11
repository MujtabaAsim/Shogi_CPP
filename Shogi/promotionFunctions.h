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
	} while (input != 'Y' or input != 'y' or input != 'N' or input != 'n');
	if (input == 'Y' or input == 'y') {
		return true;
	}
	else {
		return false;
	}
}

bool promotePiece(char** b, coordinate PC) {
	char piece = b[PC.ri][PC.ci];

	switch (piece) {
	case 'p':
	case 'n':
	case 'l':
	case 's':
		cout << "Promote " << piece << " at " << PC.ri + 1 << ", " << PC.ci + 1 << " to " << "Golden General? (Y/N): ";
		return yesNoInput;
		break;
	case 'b':
		cout << "Promote " << piece << " at " << PC.ri + 1 << ", " << PC.ci + 1 << " to " << "Horse? (Y/N): ";
		return yesNoInput;
		break;
	case 'r':
		cout << "Promote " << piece << " at " << PC.ri + 1 << ", " << PC.ci + 1 << " to " << "Dragon? (Y/N): ";
		return yesNoInput;
		break;

	case 'P':
	case 'N':
	case 'L':
	case 'S':
		cout << "Promote " << piece << " at " << PC.ri + 1 << ", " << PC.ci + 1 << " to " << "Golden General? (Y/N): ";
		return yesNoInput;
		break;
	case 'B':
		cout << "Promote " << piece << " at " << PC.ri + 1 << ", " << PC.ci + 1 << " to " << "Horse? (Y/N): ";
		return yesNoInput;
		break;
	case 'R':
		cout << "Promote " << piece << " at " << PC.ri + 1 << ", " << PC.ci + 1 << " to " << "Dragon? (Y/N): ";
		return yesNoInput;
		break;
	}
}

bool promotionCheck(char** b, coordinate PC, int turn, bool fromDropOrMoved) {

	if (turn == black) {
		
	}
	else {
		
	}
}