#pragma once

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

void capturePiece (coordinate PC, int** &promoMap, char hand[][19], int turn, char piece, int handCounter[]) {
	if (turn == black) {
		if (promoMap[PC.ri][PC.ci] == 0) {
			hand[black][handCounter[black]] = tolower(piece);
		}
		else {
			int pieceInteger = promoMap[PC.ri][PC.ci];
			char enemyPiece = intToPiece(pieceInteger);
			hand[black][handCounter[black]] = tolower(enemyPiece);
		}
		handCounter[black]++;
	}
	else {
		if (promoMap[PC.ri][PC.ci] == 0) {
			hand[white][handCounter[white]] = toupper(piece);
		}
		else {
			int pieceInteger = promoMap[PC.ri][PC.ci];
			char enemyPiece = intToPiece(pieceInteger);
			hand[white][handCounter[white]] = toupper(enemyPiece);
		}
		handCounter[white]++;
	}
	promoMap[PC.ri][PC.ci] = 0;
}

string charToPieceName(char enemyPiece) {
	enemyPiece = tolower(enemyPiece);
	switch(enemyPiece){
	case 'p':
		return "Pawn";
	case 'g':
		return "Golden General";
	case 'h':
		return "Horse (bishop)";
	case 'n':
		return "Knight";
	case 'l':
		return "Lance";
	case 's':
		return "Silver General";
	case 'r':
		return "Rook";
	case 'b':
		return "Bishop";
	case 'd':
		return "Dragon (Rook)";
	case 'k':
		return "King";
	}
	return "YOUR CODE IS FUCKED.";
}