/*
 *      MonteCarloPlayer.h
 *
 *      Created on: 15/04/2022
 *      Author: Duy Nhan Ta
 * 		StudentID: 20022020
 * 		Campus: Paramatta South
 *      Reference: Lecture Sample Code week 5
 */
#ifndef MONTECARLOPLAYER_H_
#define MONTECARLOPLAYER_H_

class MonteCarloPlayer: public Player {
public:
	MonteCarloPlayer(int t):Player("MonteCarlo", t){}
	void getMove(Board board, int&, int&);
    double simulation(Board board);
    double expansion(int player, Board board);
};

void MonteCarloPlayer::getMove(Board board, int& x, int& y) {
   

	priority_queue < Cell > moves;	

    

    for(int i=0; i< board.getRow(); i++){
        for (int j=0; j< board.getCollumn(); j++){
            if(board.getGrid(i,j) != 0){
                
                continue;
            }
            Board tempBoard(board);

            tempBoard.addMove(tempBoard.getTurn(), i,j);
            if (tempBoard.checkWinningStatus() == tempBoard.getTurn()) {
					x = i;
					y = j;
					return;
            }

            double utility = simulation(tempBoard);

            Cell c(i,j,utility);
            moves.push(c);
           
        }
        
    }
    if(!moves.empty()){
            x = moves.top().x;
            y = moves.top().y;
            
        }
    return; 
}

double MonteCarloPlayer::simulation(Board board) {
		int times = 1000;
		double winning = 0.0;
		for (int i = 0; i < times; i++) {
			Board tempBoard(board);
			int player = board.getTurn(); // khong can doi tai vi board da getTurn()
			winning += expansion(player, tempBoard);
		}
		return (winning / (double) times);
	}

double MonteCarloPlayer::expansion(int player, Board board) { //General case. 

		if (board.checkWinningStatus() == -1) { // hardcode, 1 hoac la -1
			return 1.0;
		} else if (board.checkWinningStatus() == 0) { //draw game
			return 0.5;
		} else if (board.checkWinningStatus() == -2) { //No player is winning; continue.
			return 0.0;
		}
		int x, y;
		int random = rand() % board.my_vector.size();
        int k;
        k = board.my_vector[random];
        x= k/board.getCollumn();
        y= k%board.getCollumn();
		board.addMove(player, x, y);
		player = board.getTurn();
		return expansion(player, board);
	}
#endif 