#pragma once

bool validSC(char** b, coordinate sc, int turn) {
    if (sc.ci >= size or sc.ri >= size) {
        return false;
    }
    if (b[sc.ri][sc.ci] == '-') {
        return false;
    }
    //if black's turn and he's picking an uppercase piece
    if (turn == black and b[sc.ri][sc.ci] == toupper(b[sc.ri][sc.ci])) {
        return false;
    }
    //if white's turn and he's picking a lowercase piece
    if (turn == white and b[sc.ri][sc.ci] == tolower(b[sc.ri][sc.ci])) {
        return false;
    }
    return true;
}

bool validDC(char** b, coordinate dc, int turn) {
    if (dc.ci > size or dc.ri > size) {
        return false;
    }
    //if black's turn and he's placing the piece on another lowercase piece
    if (turn == black and b[dc.ri][dc.ci] != '-' and b[dc.ri][dc.ci] == tolower(b[dc.ri][dc.ci])) {
        return false;
    }

    //if white's turn and he's placing the piece on another uppercase piece
    if (turn == white and b[dc.ri][dc.ci] != '-' and b[dc.ri][dc.ci] == toupper(b[dc.ri][dc.ci])) {
        return false;
    }

    return true;
}

bool isMoveLegal(char** board, coordinate sc, coordinate dc, int turn) {
    char unit = board[sc.ri][sc.ci];
    switch (unit) {
    case 'p':
    case 'P':
        return pawnLegality(board, sc, dc, turn);
        break;
    case 'r':
    case 'R':
        return rookLegality(board, sc, dc);
        break;
    case 'B':
    case 'b':
        return bishopLegality(board, sc, dc);
        break;
    case 'K':
    case 'k':
        return kingLegality(board, sc, dc);
        break;
    case 'n':
    case 'N':
        return knightLegality(board, sc, dc, turn);
        break;
    case 'L':
    case 'l':
        return lanceLegality(board, sc, dc, turn);
        break;
    case 's':
    case 'S':
        return silverGenLegality(board, sc, dc, turn);
        break;
    case 'g':
    case 'G':
        return goldenGenLegality(board, sc, dc, turn);
        break;
    case 'H':
    case 'h':
        return promotedBishopLegality(board, sc, dc);
        break;
    case 'd':
    case 'D':
        return promotedRookLegality(board, sc, dc);
        break;
    }
    return 0;
}