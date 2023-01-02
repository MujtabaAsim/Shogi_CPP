#pragma once

enum { black = 0, white = 1 }; //black goes first in Shogi

#define size 9
#define fill -37

using namespace std;

struct coordinate {
	int ri;
	int ci;
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

void initHand(char hand[2][19]) {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 19; j++) {
			hand[i][j] = '-';
		}
	}
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