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
#include "dropFunctions.h"
#include "promotionFunctions.h"
#include "captureFunctions.h"

void init(ifstream & newB, ifstream & newH, ifstream & loadH, ifstream & loadB, 
        ifstream & loadP, ifstream & newP,string names[], char** &board, char hand[2][19], 
        int** & pMap, int& turn, int handCounter[]) {
    cout << "Welcome to Shogi, black goes first."; nl(1);  cout << "Piece Symbols (black is lowercase);"; nl(2);
    cout << "Bishop+ (Horse) = H"; nl(1); cout << "Rook+ (Dragon) = D"; nl(1); cout << "Golden Gen. = G"; nl(1);
    cout << "Silver Gen. = S"; nl(1); cout << "Bishop = B"; nl(1); cout << "Knight = N"; nl(1); cout << "Lance = L"; nl(1);
    cout << "Pawn = P"; nl(1); cout << "King = K"; nl(1); cout << "Rook = R"; nl(2); names[black] = "Mujtaba"; names[white] = "Asim";
    //cout << "Black's Name: "; cin >> names[black]; cout << "White's Name: "; cin >> names[white];
    bool modeConfirmed = false;
    while (!modeConfirmed) {
        int mode;
        mode = 2;
        //cout << "Load old board (1) or new game (2): "; cin >> mode;
        switch (mode) {
        case 1:
            loadBoard(loadB, board, turn);
            loadPromotions(loadP, pMap);
            loadHand(loadH, hand, handCounter);
            modeConfirmed = true;
            break;
        case 2:
            loadBoard(newB, board, turn);
            loadPromotions(newP, pMap);
            loadHand(newH, hand, handCounter);
            modeConfirmed = true;
            break;
        default:
            cout << "Invalid input.";
        }
    }
    cout << "\tPress any key to continue.";
    //char junk = _getch();
    printBoard(board, hand, handCounter, names);
}

int main() {
    //___fstream declarations
    ifstream newBoardReader("newBoard.txt");
    ifstream loadBoardReader("loadBoard.txt");
    ifstream newHandReader("newHand.txt");
    ifstream loadHandReader("loadHand.txt");
    ifstream newPromotionMap("newPromotionMap.txt");
    ifstream loadPromotionMap("loadPromotionMap");
    
    //___Variable declarations
    char hand[2][19]{'-'};
    int handCounter[2] = {0, 0};
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
    
    init(newBoardReader, newHandReader, loadHandReader, loadBoardReader, loadPromotionMap, newPromotionMap, pNames, board, hand, pMap, turn, handCounter);
    
    while (!checkMate(board, turn, hand, handCounter)) {
        coordinate sc, dc;
        turnMessage(pNames, turn);
        bool drop = false, undo = false, newPromotionHappened = false;
        //___Drop a Piece
        if (handCounter[turn] > 0) {
            cout << "Drop piece from hand instead of moving? (Y/N): ";
            if (yesNoInput()) {
                drop = true;
                char piece;
                do {
                    piece = pickPieceFromHand(turn, hand, handCounter);
                    do {
                        cout << "Click where you want to place it";
                        userInput(dc);
                    } while (!isDropValid(board, dc, turn, piece, hand, handCounter));
                    tempDrop(board, dc, piece);
                    if (selfCheck(board, turn)) {
                        system("cls"); undoTempDrop(board, dc);
                        printBoard(board, hand, handCounter, pNames);
                        cout << "That move places you in a check, try again!"; nl(1);
                    }
                } while (selfCheck(board, turn));
                undoTempDrop(board, dc);
                realDrop(board, dc, piece);
                printBoard(board, hand, handCounter, pNames);
            }
        }
        //___Move a Piece
        if (!drop) { //move a piece
            bool** bMap;
            char* coveredPieces = new char[12];
            do {
                do {
                    do {
                        cout << "Click on the piece you want to move";
                        userInput(sc);
                    } while (!validSC(board, sc, turn));
                    bMap = computeHighlight(board, sc, turn);
                    highlight(bMap, board, coveredPieces);
                    printBoard(board, hand, handCounter, pNames);
                    cout << "Click where you want to place it";
                    userInput(dc);
                    if (!bMap[dc.ri][dc.ci]) {
                        unhighlight(bMap, board, coveredPieces);
                        system("cls");
                        printBoard(board, hand, handCounter, pNames);
                    }
                    if (bMap[dc.ri][dc.ci] and board[dc.ri][dc.ci] == 'O') {
                        unhighlight(bMap, board, coveredPieces);
                        char enemyPiece = board[dc.ri][dc.ci];
                        highlight(bMap, board, coveredPieces);
                        string enemyPieceName = charToPieceName(enemyPiece);
                        cout << "Capture the enemy's " << enemyPieceName << "? (Y/N): ";
                        if (yesNoInput()) {
                            capturePiece(dc, pMap, hand, turn, enemyPiece, handCounter);
                        }
                    }
                } while (!bMap[dc.ri][dc.ci]);
                unhighlight(bMap, board, coveredPieces);
                updateBoardTemp(board, sc, dc);
                if (selfCheck(board, turn)) {
                    system("cls"); undoTempBoardUpdate(board, sc, dc);
                    printBoard(board, hand, handCounter, pNames);
                    cout << "That move places you in a check, try again!"; nl(1);
                }
            } while (selfCheck(board, turn));
            undoTempBoardUpdate(board, sc, dc);
            updatePromotionBoard(pMap, sc, dc); updateBoard(board, sc, dc);
            printBoard(board, hand, handCounter, pNames);
            promotionCheck(board, dc, turn, pMap, newPromotionHappened);
            printBoard(board, hand, handCounter, pNames);
            for (int i = 0; i < size; i++) {
                delete[] bMap[i];
            }
            delete[] bMap;
            delete[] coveredPieces;
        }
        cout << "Do you want to undo the last move? (Y/N): ";
        undo = yesNoInput();
        if (undo) {
            if (drop) {
                //undoDrop();
            }
            else {
                if (newPromotionHappened) {
                    undoNewPromotion(pMap, board, dc);
                }
                undoPromotionBoard(pMap, sc, dc);
                undoTempBoardUpdate(board, sc, dc);
            }
        }
        else {
            //___Writing + Deletion
            ofstream boardWriter("loadBoard.txt");
            ofstream handWriter("loadHand.txt");
            ofstream pMapWriter("loadPromotionMap.txt");
            turnChange(turn);
            savePromotions(pMapWriter, pMap);
            saveBoard(boardWriter, turn, board);
            saveHand(handWriter, hand, handCounter);
        }
    }
    gameEndMessage(turn, pNames);
    return _getch();
}

