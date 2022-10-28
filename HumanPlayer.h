/*
 * 		HumanPlayer.h
 *
 *  	Created on: 15/04/2022
 *      Author: Duy Nhan Ta
 * 		StudentID: 20022020
 * 		Campus: Paramatta South
 */

#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_

class HumanPlayer: public Player {
public:
	HumanPlayer(int t):Player("Human Player", t){}
	void getMove(Board board, int&, int&);
};

void HumanPlayer::getMove(Board board, int& x, int& y)
{
	if(board.isBoardFull())
		return;

	do {
		cout << "Input your move with row and column numbers:" << endl;
		int row, col;
		cin >> row >> col;
		x = row-1;
		y = col-1;
	} while (!board.validMove(x,y));
}

#endif /* HUMANPLAYER_H_ */
