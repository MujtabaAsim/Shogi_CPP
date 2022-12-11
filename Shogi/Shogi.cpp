// Shogi.cpp : This file contains the 'main' function. Program execution begins and ends there.
// IHTFP.

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include "auxiliary.h"
#include <ctime>
#include "directionalLegality.h"
#include "pieceLegality.h"
#include "savingToFile.h"
#include "highlightingFunctions.h"
#include "turnFunctions.h"
#include "basicLegalityFunctions.h"
#include "check.h"

void loadBoard(ifstream &rdr, char** &B, int &turn) {
    rdr >> turn;
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            rdr >> B[r][c];
        }
    }
}
void printBoard (char** B) {
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

void userInput(coordinate &position) {
    int r, c;
    getRCfromMB1(r, c);
    position.ri = r/=2;
    position.ci = c/=4;
}
void init(ifstream & newB, ifstream& newP, ifstream& loadP, ifstream& loadB, string names[], char** &board, char** &prison, int &turn) {
    cout << "Welcome to Shogi, black goes first."; nl(1);
    cout << "Piece Symbols (black is lowercase);"; nl(2);
    cout << "Promoted Bishop (Horse) = H"; nl(1);
    cout << "Promoted Rook (Dragon) = D"; nl(1);
    cout << "Golden General = G"; nl(1);
    cout << "Silver General = S"; nl(1);
    cout << "Bishop = B"; nl(1);
    cout << "Knight = N"; nl(1);
    cout << "Lance = L"; nl(1);
    cout << "Pawn = P"; nl(1);
    cout << "King = K"; nl(1);
    cout << "Rook = R"; nl(2);

    cout << "Promotions: "; nl(2);
    cout << "S/P/L/N -> G"; nl(1);
    cout << "B -> H"; nl(1);
    cout << "R -> D"; nl(2);

    names[black] = "Mujtaba";
    names[white] = "Asim";
    //cout << "Black's Name: "; cin >> names[black];
    //cout << "White's Name: "; cin >> names[white];

    bool modeConfirmed = false;
    while (!modeConfirmed) {
        int mode;
        mode = 2;
        //cout << "Load old board (1) or new game (2): "; cin >> mode;

        switch (mode) {
        case 1:
            loadBoard(loadB, board, turn);
            modeConfirmed = true;
            break;
        case 2:
            loadBoard(newB, board, turn);
            modeConfirmed = true;
            break;
        default:
            cout << "Invalid input.";
        }
    }
    Sleep(800);
    printBoard(board);
}

int main()
{
    ifstream newBoardReader("newBoard.txt");
    ifstream loadBoardReader("loadBoard.txt");
    ifstream newPrisonReader("newPrison.txt");
    ifstream loadPrisonReader("loadPrison.txt");//
    ofstream boardWriter("loadBoard.txt");
    ofstream prisonWriter("loadPrison.txt");
    
    char** board;
    char** prison;
    int turn = -1;
    string pNames[2];
    board = new char* [size+1];
    for (int i = 0; i <= size; i++) {
        board[i] = new char [size + 1];
    }


    ///*
    init(newBoardReader, newPrisonReader, loadPrisonReader, loadBoardReader, pNames, board, prison, turn);

    while (true) { //while(!checkmate){}
        coordinate sc, dc;
        bool** bMap;
        char* coveredPieces = new char[9];
        do {
            
            do {
                turnMessage(pNames, turn);
                cout << "Click on the piece you want to move."; nl(1);
                userInput(sc);
            } while (!validSC(board, sc, turn));
            bMap = computeHighlight(board, sc, turn);
            highlight(bMap, board, coveredPieces);
            printBoard(board);
            cout << "Click where you want to place it."; nl(1);
            userInput(dc);
            if (bMap[dc.ri][dc.ci] == false) {
                unhighlight(bMap, board, coveredPieces);
                printBoard(board);
            }
        } while (!bMap[dc.ri][dc.ci]);
        unhighlight(bMap, board, coveredPieces);
        
        
        updateBoard(board, sc, dc);
        printBoard(board);
        turnChange(turn);
        //saveBoard(boardWriter, turn, board);
        savePrison(); //WIP
        //deletion
        for (int i = 0; i < size; i++) {
            delete[] bMap[i];
        }
        delete[] bMap;
        delete[]coveredPieces;
    }
    //*/
    
    return _getch();
}

