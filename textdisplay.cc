#include <iostream>
#include <string>
#include <vector>
#include "textdisplay.h"

using namespace std;

//rnbqkb1r/ppp1pppp/5n2/3p4/4P3/2N5/PPPP1PPP/R1BQKBNR w KQkq - 2 3

//initializes empty board with white ' ' and black '_' "squares"
textDisplay::textDisplay() {
    vector<char> oddLine;
    vector<char> evenLine;
    int size = 8;

    for(int i = 0; i < size; i++) {
        if (i % 2 == 0) {
            oddLine.emplace_back('_');
            evenLine.emplace_back(' ');
        } else {
            oddLine.emplace_back(' ');
            evenLine.emplace_back('_');
        }
    }

    for (int i = 0; i < size; i++) {
        if (i % 2 == 0) {
            board.emplace_back(evenLine);
        } else {
            board.emplace_back(oddLine);
        }
    }
}

// rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR
void textDisplay::printBoard(const string fen) {
	vector<char> v(fen.begin(), fen.end());
	int row = 0;
	int col = 0;
	for(long unsigned int i = 0; i < v.size(); i++) {
		char piece = v.at(i);
		if(piece== 'r') {
			board.at(row).at(col) = 'r';
            		col++;
			cout << "Printed r at " << row << " row and " << col << "column\n";
        	} else if(piece == 'n') {
            		board.at(row).at(col) = 'n';
            		col++;
			cout << "Printed n at " << row << " row and " << col << "column\n";
        	} else if(piece == 'b') {
            		board.at(row).at(col) = 'b';
            		col++;
			cout << "Printed b at " << row << " row and " << col << "column\n";
        	} else if(piece == 'q') {
            		board.at(row).at(col) = 'q';
            		col++;
			cout << "Printed q at " << row << " row and " << col << "column\n";
        	} else if(piece == 'k') {
            		board.at(row).at(col) = 'k';
            		col++;
			cout << "Printed k at " << row << " row and " << col << "column\n";
        	} else if(piece == 'p') {
            		board.at(row).at(col) = 'p';
            		col++;
			cout << "Printed p at " << row << " row and " << col << "column\n";
        	} else if(piece >= '1' && piece <= '8') {
            		int num = piece - '0';
            		col += num;
        	} else if(piece == 'R') {
            		board.at(row).at(col) = 'R';
            		col++;
			cout << "Printed R at " << row << " row and " << col << "column\n";
        	} else if(piece == 'N') {
            		board.at(row).at(col) = 'N';
            		col++;
			cout << "Printed N at " << row << " row and " << col << "column\n";
        	} else if(piece == 'B') {
            		board.at(row).at(col) = 'B';
            		col++;
			cout << "Printed B at " << row << " row and " << col << "column\n";
        	} else if(piece == 'Q') {
            		board.at(row).at(col) = 'Q';
            		col++;
			cout << "Printed Q at " << row << " row and " << col << "column\n";
        	} else if(piece == 'K') {
            		board.at(row).at(col) = 'K';
            		col++;
			cout << "Printed K at " << row << " row and " << col << "column\n";
        	} else if(piece == 'P') {
            	board.at(row).at(col) = 'P';
            		col++;
			cout << "Printed P at " << row << " row and " << col << "column\n";
        	} else {
            		row++;
            		col = 0;
		}
	}
}

ostream &operator<<(ostream &out, const textDisplay &t) {
    for (long unsigned int i = 0; i < t.board.size(); i++) {
        out << t.board.size() - i << " ";

        for (long unsigned int j = 0; j < t.board[i].size(); j++) {
            out << t.board.at(i).at(j);
        }

        out << endl;
    }

    out << endl << "  "; // two spaces to align
    for (char i = 'a'; i <= 'h'; i++) {
        out << i;
    }
    out << endl;
    return out;
}

int main() {
    textDisplay t;
    string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    t.printBoard(fen);
    cout << endl;
    // cout << t.board.size() << endl;
    cout << t;
}
