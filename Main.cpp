/*
 * Main.cpp
 *
 *  	Created on: 22/02/2022
 *      Author: Duy Nhan Ta
 * 		StudentID: 20022020
 * 		Campus: Paramatta South
 */

#include<iostream>
#include<time.h>
#include<algorithm>
#include<unordered_map>
#include<sstream>
#include<vector>
#include<set>
#include<queue>

using namespace std;

#include "Cell.h"
#include "Board.h"
#include "Player.h"
#include "CephalopodGame.h"
#include "HumanPlayer.h"
#include "RandomPlayer.h"
#include "ComputerPlayer.h"
#include "MonteCarloPlayer.h"



int main() {
	srand(time(0));
	cout << "Example solution for high distinction level" << endl;

	Player *players[2];

	players[0] = new RandomPlayer(1);
	players[1] = new MonteCarloPlayer(-1);//Hint: Change it to random player once you have one

	cout << "Input size of the board (say (2,2), (2,3), (3,3), (3,5), (5,5) ... " << endl;

	int row, col;
	cin >> row >> col;

	Board board(row, col);
	CephalopodGame game(board, players);
	game.play();

	delete players[0];
	delete players[1];

	return 0;
}
