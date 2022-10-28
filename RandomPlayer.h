/*
 *      RandomPlayer.h
 *
 *      Created on: 15/04/2022
 *      Author: Duy Nhan Ta
 * 		StudentID: 20022020
 * 		Campus: Paramatta South
 */
#ifndef RANDOMPLAYER_H_
#define RANDOMPLAYER_H_


class RandomPlayer: public Player {
public:
	RandomPlayer(int t):Player("Random", t){}
	void getMove(Board board, int&, int&);
};

void RandomPlayer::getMove(Board board, int& x, int& y)
{
	if(board.isBoardFull())
		return;

	int random = rand() % board.my_vector.size(); 
    int k;
    k = board.my_vector[random];
    x= k/board.getCollumn();
    y= k%board.getCollumn();
    //board.addMove(board.getTurn(), x, y);
}

#endif /* HUMANPLAYER_H_ */