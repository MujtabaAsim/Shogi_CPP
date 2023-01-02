#pragma once

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