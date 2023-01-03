#pragma once

enum { black = 0, white = 1 }; //black goes first in Shogi

#define size 9
#define fill -37
#define cap 50

using namespace std;

struct coordinate {
	int ri;
	int ci;
};

struct gameState {
	char handState[2][cap];
	char** boardState;
	int** promotionMap;
};

void nl(int i) {
    for (int j = 0; j < i; j++) {
        cout << endl;
    }
}

bool yesNoInput() {
	char input;
	do {
		cin >> input;
		input = tolower(input);
	} while (input != 'y' and input != 'n');
	if (input == 'y') {
		return true;
	}
	else {
		return false;
	}
}

void initHand(char hand[2][cap]) {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < cap; j++) {
			hand[i][j] = '-';
		}
	}
}

void copyHand() {

}

void copyBoard() {

}

void copyMap() {

}

char intToPiece(int pieceInteger) {
	switch (pieceInteger) {
	case 1:
		return 'p';
	case 2:
		return 'n';
	case 3:
		return 'l';
	case 4:
		return 's';
	case 5:
		return 'b';
	case 6:
		return 'r';
	case 7:
		return 'P';
	case 8:
		return 'N';
	case 9:
		return 'L';
	case 10:
		return 'S';
	case 11:
		return 'B';
	case 12:
		return 'R';
	}
	return '+';
}

void getRCfromMB1(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do {
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}

void gotoRC(int rpos, int cpos) {	
	COORD scrn{0, 0};
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos; scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void SetColour(int clr) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}

void gameEndMessage(int turn, string pNames[]) {
	cout << "Game over, " << pNames[turn] << " won!";
	nl(5);
	cout << "Press any key to continue.";
}