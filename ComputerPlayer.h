/*
 *      ComputerPlayer.h
 *
 *      Created on: 15/04/2022
 *      Author: Duy Nhan Ta
 * 		StudentID: 20022020
 * 		Tutorial Class: 11:00AM Friday
 * 		Campus: Paramatta South
 *      Reference: Lecture Sample Code week 4 - TicTacToe
 */




#ifndef COMPUTERPLAYER_H_
#define COMPUTERPLAYER_H_


class ComputerPlayer: public Player {
public:
	ComputerPlayer(int t):Player("Computer", t){}
	void getMove(Board board, int&, int&);
};

void ComputerPlayer::getMove(Board board, int& x, int& y) {
    if(board.isBoardFull())
		return;

	priority_queue < Cell > moves;	

    for(int i=0; i< board.getRow(); i++){
        for (int j=0; j< board.getCollumn(); j++){
            Board tempBoard(board);
            if(!tempBoard.validMove(i,j)){
                continue;
            }
            
            tempBoard.addMove(tempBoard.getTurn(), i, j);

            Cell c(i, j, tempBoard.heuristics());
		    moves.push(c);
           
        }
    }
    if(moves.size() > 0){
            x = moves.top().x;
            y= moves.top().y;
        }

}

	
#endif /* HUMANPLAYER_H_ */