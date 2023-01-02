// Shogi.cpp : This file contains the 'main' function. Program execution begins and ends there.
// IHTFP.

#include <iostream>
#include <fstream> 
#include <Windows.h> 
#include <conio.h> 
#include <ctime>
#include "auxiliary.h"
#include "directionalLegality.h"
#include "pieceLegality.h"
#include "readWritePrint.h"
#include "highlightingFunctions.h"
#include "turnFunctions.h"
#include "basicLegalityFunctions.h"
#include "checkFunctions.h"
#include "promotionFunctions.h"
#include "captureFunctions.h"

void init(ifstream & newB, ifstream & newH, ifstream & loadH, ifstream & loadB, 
        ifstream & loadP, ifstream & newP,string names[], char** &board, 
        char hand[2][19], int** & pMap, int& turn, int blackHandCounter, int whiteHandCounter) {
    cout << "Welcome to Shogi, black goes first."; nl(1);
    cout << "Piece Symbols (black is lowercase);"; nl(2);
    cout << "Bishop+ (Horse) = H"; nl(1);
    cout << "Rook+ (Dragon) = D"; nl(1);
    cout << "Golden Gen. = G"; nl(1);
    cout << "Silver Gen. = S"; nl(1);
    cout << "Bishop = B"; nl(1);
    cout << "Knight = N"; nl(1);
    cout << "Lance = L"; nl(1);
    cout << "Pawn = P"; nl(1);
    cout << "King = K"; nl(1);
    cout << "Rook = R"; nl(2);

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
            loadPromotions(loadP, pMap);
            loadHand(loadH, hand, blackHandCounter, whiteHandCounter);
            modeConfirmed = true;
            break;
        case 2:
            loadBoard(newB, board, turn);
            loadPromotions(newP, pMap);
            loadHand(newH, hand, blackHandCounter, whiteHandCounter);
            modeConfirmed = true;
            break;
        default:
            cout << "Invalid input.";
        }
    }
    cout << "\tPress any key to continue.";
    //char junk = _getch();
    printBoard(board, hand, blackHandCounter, whiteHandCounter);;
}

int main() {
    ifstream newBoardReader("newBoard.txt");
    ifstream loadBoardReader("loadBoard.txt");
    ifstream newHandReader("newHand.txt");
    ifstream loadHandReader("loadHand.txt");
    ifstream newPromotionMap("newPromotionMap.txt");
    ifstream loadPromotionMap("loadPromotionMap");
    
    //____VARIABLE DECLARATIONS: hand/turn/game board/promotion board/gameOver bool
    char hand[2][19]{'-'};
    int blackHandCounter = 0, whiteHandCounter = 0;
    int turn = -1;
    string pNames[2];
    char** board = new char* [size];
    for (int i = 0; i < size; i++) {
        board[i] = new char [size];
    }
    int** pMap = new int* [size];
    for (int i = 0; i < size; i++) {
        pMap[i] = new int[size];
    }
    
    init(newBoardReader, newHandReader, loadHandReader, loadBoardReader, loadPromotionMap, newPromotionMap, pNames, board, hand, pMap, turn, blackHandCounter, whiteHandCounter);
    
    ///*
    while (!checkMate(board, turn) or !staleMate(board, turn)) {
        coordinate sc, dc;
        bool** bMap;
        char* coveredPieces = new char[12];
        bool pieceDropped = false;
        turnMessage(pNames, turn);
        do {
            do {
                do {
                    cout << "Click on the piece you want to move."; nl(1);
                    userInput(sc);
                } while (!validSC(board, sc, turn));
                bMap = computeHighlight(board, sc, turn);
                highlight(bMap, board, coveredPieces);
                printBoard(board, hand, blackHandCounter, whiteHandCounter);
                cout << "Click where you want to place it."; nl(1);
                userInput(dc);
                if (bMap[dc.ri][dc.ci] == false) {
                    unhighlight(bMap, board, coveredPieces);
                    system("cls");
                    printBoard(board, hand, blackHandCounter, whiteHandCounter);
                }
                if (bMap[dc.ri][dc.ci] and board[dc.ri][dc.ci] == 'O') {
                    unhighlight(bMap, board, coveredPieces);
                    char enemyPiece = board[dc.ri][dc.ci];
                    highlight(bMap, board, coveredPieces);
                    string enemyPieceName = charToPieceName(enemyPiece);
                    cout << "Capture the enemy's " << enemyPieceName << "? (Y/N): ";
                    if (yesNoInput()) {
                        capturePiece (dc, pMap, hand, turn, enemyPiece, blackHandCounter, whiteHandCounter);
                    }
                }
            } while (!bMap[dc.ri][dc.ci]);
            unhighlight(bMap, board, coveredPieces);
            updateBoardTemp(board, sc, dc);
            if (selfCheck(board, turn)) {
                system("cls");
                undoTempBoardUpdate(board, sc, dc); printBoard(board, hand, blackHandCounter, whiteHandCounter);
                cout << "That move places you in a check, try again!"; nl(1);
            }
        } while (selfCheck(board, turn));
        undoTempBoardUpdate(board, sc, dc);
        updatePromotionBoard(pMap, sc, dc); updateBoard(board, sc, dc);
        printBoard(board, hand, blackHandCounter, whiteHandCounter);

        //implement if here to not run promotionCheck if piece is dropped on board.
        promotionCheck(board, dc, turn, pMap);
        printBoard(board, hand, blackHandCounter, whiteHandCounter);
        turnChange(turn);
        //___Writing to file + highlight map deletion
        ofstream boardWriter("loadBoard.txt");
        ofstream handWriter("loadHand.txt");
        ofstream pMapWriter("loadPromotionMap.txt");
        savePromotions(pMapWriter, pMap);
        saveBoard(boardWriter, turn, board);
        saveHand(handWriter, hand, blackHandCounter, whiteHandCounter);
        for (int i = 0; i < size; i++) {
            delete[] bMap[i];
        }
        delete[] bMap;
        delete[] coveredPieces;
        
    }
    cout << "Game over, " << pNames[turn] << " won!"; nl(5);
    //*/
    return 0;
}

