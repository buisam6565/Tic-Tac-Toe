#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

typedef std::vector < std::vector<char> > State;
typedef std::vector <char> Row;

const int SIZE = 3;

char nexTurn(State s){
	int countX = 0, countO = 0;
	for (unsigned int i = 0; i < SIZE; i += 1){
		for (unsigned int j = 0; j < SIZE; j += 1){
			if (s[i][j] == 'X'){
				countX += 1;
			} else if (s[i][j] == 'O'){
				countO += 1;
			}
		}
	}
	return (countX > countO ? 'O' : 'X');
}

bool is_final(State s){
	for (unsigned int i = 0; i < SIZE; i += 1){
		if (s[i][0] == s[i][1] and s[i][0] == s[i][2] and s[i][0] != ' '){
			return true;
		}
	}

	for (unsigned int i = 0; i < SIZE; i += 1){
		if (s[0][i] == s[1][i] and s[0][i] == s[2][i] and s[0][i] != ' '){
			return true;
		}
	}

	if (s[0][0] == s[1][1] and s[0][0] == s[2][2] and s[0][0] != ' '){
		return true;
	}

	if (s[0][2] == s[1][1] and s[0][2] == s[2][0] and s[0][2] != ' '){
		return true;
	}

	for (unsigned int i = 0; i < SIZE; i += 1){
		for (unsigned int j = 0; j < SIZE; j += 1){
			if (s[i][j] == ' '){
				return false;
			}
		}
	}

	return true;
}

int getFinalScore(State s){
	for (unsigned int i = 0; i < SIZE; i += 1){
		if (s[i][0] == s[i][1] and s[i][0] == s[i][2] and s[i][0] != ' '){
			if (s[i][0] == 'O'){
				return -1;
			}
			return 1;
		}
	}

	for (unsigned int i = 0; i < SIZE; i += 1){
		if (s[0][i] == s[1][i] and s[0][i] == s[2][i] and s[0][i] != ' '){
			if (s[0][i] == 'O'){
				return -1;
			}
			return 1;
		}
	}

	if (s[0][0] == s[1][1] and s[0][0] == s[2][2] and s[0][0] != ' '){
		if (s[0][0] == 'O'){
			return -1;
		}
		return 1;
	}

	if (s[0][2] == s[1][1] and s[0][2] == s[2][0] and s[0][2] != ' '){
		if (s[0][2] == 'O'){
			return -1;
		}
		return 1;
	}

	return 0;
}

void drawBoard(State s){
	std::cout << "  +-----+-----+-----+\n";
	for (std::vector<char> i : s){
		for (char j : i){
			std::cout << "  |  " << j;
		}
		std::cout << "  |\n"; 
		std::cout << "  +-----+-----+-----+\n";
	}
}

std::vector<int> getStateScore(State s){
	if (is_final(s)){
		return {getFinalScore(s), -1, -1};
	}

	char nex = nexTurn(s);
	int score = 2, nexRow = -1, nexCol = -1;
	for (int i = 0; i < SIZE; i += 1){
		for (int j = 0; j < SIZE; j += 1){
			if (s[i][j] == ' '){
				s[i][j] = nex;
				std::vector <int> next = getStateScore(s);
				s[i][j] = ' ';

				if (nex == 'X'){
					if (score == 2 or score <= next[0]){
						score = next[0];
						nexRow = i;
						nexCol = j;
					}
				} else {
					if (score == 2 or score >= next[0]){
						score = next[0];
						nexRow = i;
						nexCol = j;
					}
				}
			}
		}
	}

	return {score, nexRow, nexCol};
}

std::string showWinner(State s, char player){
	int score = getFinalScore(s);
	std::string win = "YOU WIN! CONGRATULATION!\n",
				draw = "YOU AND YOUR COMPUTER DRAW!\n",
				lose = "YOU LOSE! GIVE ME MONEY!\n";
	if (score == 1){
		if (player == 'X'){
			return win;
		}
		return lose;
	} else if (score == 0){
		return draw;
	} else {
		if (player == 'X'){
			return lose;
		}
		return win;
	}
}

int main(){
	// Khai bao bien
	char player, computer;
	int row, col;
	bool playerTurn, running = true;
	State s (SIZE, Row(SIZE, ' '));

	// Cai dat ban dau
	std::cout << "You are X or O ? : ";
	std::cin >> player;
	computer = (player ^ 'X' ^ 'O');
	playerTurn = (player == 'X');

	system("CLS");

	// Chay tro choi
	drawBoard(s);
	while (running){

		if (playerTurn){
			std::cout << "Write your choice : ";
			std::cin >> row >> col;
			while (not (0 <= row and row <= 2 and 0 <= col and col <= 2 and s[row][col] == ' ')){
				std::cout << "Choose again : ";
				std::cin >> row >> col;
			}
			s[row][col] = player;
			playerTurn = not playerTurn;
			system("CLS");
		} else {
			system("CLS");
			std::cout << "Computer's turn here!\n";
			std::vector <int> next = getStateScore(s);
			s[next[1]][next[2]] = computer;
			playerTurn = not playerTurn;
		}
		drawBoard(s);

		if (is_final(s)){
			std::cout << showWinner(s, player);
			running = false;
		}
	}

	return 0;
}