#pragma once

void saveBoard(ofstream &writer, int turn, char**b) {
	writer << turn;
	writer << endl;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			writer << b[i][j] << " ";
		}
		writer << endl;
	}
}

void saveHand(ofstream &writer, char hand[][19]) {
	for (int player = 0; player < 2; player++) {
		for (int pieceNo = 0; pieceNo < 19; pieceNo++) {
			writer << hand[player][pieceNo] << " ";
		}
		writer << endl;
	}
}

void loadHand(ifstream& rdr, char hand[][19]) {
	for (int player = 0; player < 2; player++) {
		for (int pieceNo = 0; pieceNo < 19; pieceNo++) {
			rdr >> hand[player][pieceNo];
		}
	}
}

void loadBoard(ifstream& rdr, char**& B, int& turn) {
	rdr >> turn;
	for (int r = 0; r < size; r++) {
		for (int c = 0; c < size; c++) {
			rdr >> B[r][c];
		}
	}
}

void printBoard(char** B) {
	system("cls");
	char f = char(fill);
	//top-most line
	for (int m = 0; m < size * 4 + 1; m++) {
		cout << f;
	} nl(1);
	//rows
	for (int r = 0; r < size; r++) {
		cout << f;
		//cols
		for (int c = 0; c < size; c++) {
			cout << " " << B[r][c] << " " << f;
		} nl(1);
		for (int m = 0; m < size * 4 + 1; m++) {
			cout << f;
		} nl(1);
	}
}

void updatePromotionBoard(int**& pMap, coordinate sc, coordinate dc) {
	int pieceValue = pMap[sc.ri][sc.ci];
	pMap[sc.ri][sc.ci] = 0;
	pMap[dc.ri][dc.ci] = pieceValue;
}

void updateBoardTemp(char**& board, coordinate sc, coordinate dc) {
	char piece = board[sc.ri][sc.ci];
	board[sc.ri][sc.ci] = '-';
	board[dc.ri][dc.ci] = piece;
}

void undoTempBoardUpdate(char**& board, coordinate sc, coordinate dc) {
	char piece = board[dc.ri][dc.ci];
	board[dc.ri][dc.ci] = '-';
	board[sc.ri][sc.ci] = piece;
}

void updateBoard(char**& board, coordinate sc, coordinate dc) {
	char piece = board[sc.ri][sc.ci];
	board[sc.ri][sc.ci] = '-';
	board[dc.ri][dc.ci] = piece;
}

void userInput_Mouse(coordinate& position) {
	getRCfromMB1(position.ri, position.ci);
	position.ri /= 2;
	position.ci /= 4;
}

void userInput(coordinate& position) {
	cout << "Enter coordinates (r c): ";
	cin >> position.ri >> position.ci;
	position.ri--;
	position.ci--;
}