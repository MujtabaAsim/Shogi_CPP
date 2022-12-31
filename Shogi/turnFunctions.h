#pragma once

void turnMessage(string name[], int turn) {
    cout << name[turn] << "'s turn. "; nl(1);
}

void turnChange(int& turn) {
    if (turn == black) {
        turn = white;
    }
    else {
        turn = black;
    }
}