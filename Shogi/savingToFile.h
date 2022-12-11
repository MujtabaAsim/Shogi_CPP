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
void savePrison() {

}