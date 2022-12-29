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
#include "readWritePrint.h"
#include "highlightingFunctions.h"
#include "turnFunctions.h"
#include "basicLegalityFunctions.h"
#include "check.h"
#include "promotionFunctions.h"


void updatePromotionBoard(int** &pMap, coordinate sc, coordinate dc) {
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


void init(ifstream & newB, ifstream & newH, ifstream & loadH, ifstream & loadB, string names[], char** &board, char hand[2][19], int& turn) {
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
            loadHand(loadH, hand);
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
    //cout << "\nPress any key to continue.";
    printBoard(board);
}

int main()
{
    ifstream newBoardReader("newBoard.txt");
    ifstream loadBoardReader("loadBoard.txt");
    ifstream newHandReader("newHand.txt");
    ifstream loadHandReader("loadHand.txt");

    //____VARIABLE DECLARATIONS: hand/turn/game board/promotion board/gameOver bool
    char hand[2][19]{'-'};
    bool gameOver = false;
    int turn = -1;
    string pNames[2];
    
    char** board = new char* [size];
    for (int i = 0; i < size; i++) {
        board[i] = new char [size];
    }
    int** promotionMap = new int* [size];
    for (int i = 0; i < size; i++) {
        promotionMap[i] = new int[size] {};
    }
    

    ///*
    init(newBoardReader, newHandReader, loadHandReader, loadBoardReader, pNames, board, hand, turn);

    while (!gameOver) { //while(!checkmate){}
        coordinate sc, dc;
        bool** bMap;
        char* coveredPieces = new char[9];
        bool pieceDropped = false;
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

        
        
        updatePromotionBoard(promotionMap, sc, dc);
        updateBoard(board, sc, dc);
        printBoard(board);

        promotionCheck(board, dc, turn, pieceDropped, promotionMap); //change false to implement 'fromDrop' functionality
        
        turnChange(turn);

        ofstream boardWriter("loadBoard.txt");
        ofstream HandWriter("loadHand.txt");
        saveBoard(boardWriter, turn, board);
        saveHand(HandWriter, hand);
        for (int i = 0; i < size; i++) {
            delete[] bMap[i];
        }
        delete[] bMap;
        delete[] coveredPieces;
    }
    //*/
    
    return _getch();
}

