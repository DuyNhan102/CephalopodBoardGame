/*
 * Board.h
 *
 *  	Created on: 25/02/2022
 *      Author: Duy Nhan Ta
 * 		StudentID: 20022020
 * 		Tutorial Class: 11:00AM Friday
 * 		Campus: Paramatta South
 */

#ifndef BOARD_H_
#define BOARD_H_
#include <unordered_map>
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

class Board {
private:
	int row, col;
	int player; //1 = white; -1 = black
	int **grid; // 0 = empty; other values for pip count; positive for white; negative for black
	
public:
	//create vector to store empty cell
	vector <int> my_vector; 
	//chay 1 vong for cu moi mot row thi se cho ra so collumn 
	Board(int r, int c) :
			row(r), col(c) {
		grid = new int*[row];
		for (int i = 0; i < row; i++)
			grid[i] = new int[col];

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				grid[i][j] = 0;
				my_vector.push_back(i *col+j); // {0,1,2}
			}
		}

		player = 1; // white has the first turn
	}

	~Board() {
		for (int i = 0; i < row; i++)
			delete[] grid[i];

		delete[] grid;
	}

	Board(const Board &cboard) {//Copy constructor
		row = cboard.row;
		col = cboard.col;
		
		grid = new int*[row];
		for (int i = 0; i < row; i++)
			grid[i] = new int[col];

		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++) {
				grid[i][j] = cboard.grid[i][j]; // take the value of the main board r pass vao cboard 
				
			}
		my_vector = cboard.my_vector;
		player = cboard.getTurn();
	}

	bool isBoardFull() {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if(grid[i][j] == 0)
					return false;
			}
		}
		return true;
	}

	int getTurn() const {
		return player;
	}

	bool validMove(int x, int y);

	bool addMove(int player, int x, int y);

	int checkWinningStatus();

	void printBoard();

	int capturingPlacement(int, int);//to be implemented

	void refreshIndex (int k);

	int getCollumn();

	int getRow();

	int heuristics();

	int getGrid(int i, int j);
};

int Board::getGrid(int i, int j){
		return grid[i][j];
	}

int Board::getCollumn(){
	return col;
}

int Board::getRow(){
	return row;
}

int Board::heuristics(){ // number of dice after that move
	int k=0;
	for(int i=0; i< row; i++){
		for(int j=0; j<col ;j++){
			if(grid[i][j] == player) 
			k += grid[i][j];
		}
	}
	return k; 
}

int Board::capturingPlacement(int x, int y){
	int sum =0;
	int count =0;
	int sumCapture =0;// only use for Task 5 case 3, capturing 
	unordered_map<string, Cell> umap;
	Cell cell;
	vector<int> HXvalue; // store the neighbor value
	vector<string> HXpos; // store the neighbor position
	
	if(x > 0 && grid[x-1][y] !=0){ 
		/*Take the up value from the map and put it into un-ordered map*/
		cell.x = x-1; 
		cell.y = y;
		cell.value = abs(grid[x-1][y]);
		sum = sum + cell.value;
		umap["up"] = cell; 
	}

	if(y > 0 && grid[x][y-1] !=0){
		/*Take the left value from the map and put it into un-ordered map*/
		cell.x = x; 
		cell.y = y-1; 
		
		cell.value = (abs(grid[x][y-1]));
		sum = sum + cell.value;
		umap["left"] = cell;
	}	

	if(x < row -1 && grid[x+1][y] !=0){
		/*Take the down value from the map and put it into un-ordered map*/
		cell.x = x+1;
		cell.y = y; 
		cell.value = (abs(grid[x+1][y]));
		sum = sum + cell.value;
		umap["down"] = cell; 
	}

	if(y < col-1 &&grid[x][y+1] != 0){
		/*Take the right value from the map and put it into un-ordered map*/
		cell.x = x; 
		cell.y = y+1; 
		cell.value = (abs(grid[x][y+1]));
		sum = sum + cell.value; 
		umap["right"] = cell;  
	}

	
	for(auto i: umap){
		HXvalue.push_back(i.second.value);// put the value of a neighbor into 1 vector
		HXpos.push_back(i.first);// put the key value of the un-ordered map into different vector
	}

	/*Capturing Process*/
	if(umap.size() <2)
		return 1; 

	if(umap.size() == 2){
		if(sum <=6){
			for(auto it: umap){ 
				grid[it.second.x][it.second.y]= 0;
				int k = it.second.x * col + it.second.y; //put the value back into vector after capturing
				my_vector.push_back(k);
			}
			return sum;
		}
		else 
			return 1;  
	}

	if(umap.size() > 2){
		if(sum <=6){
			for(auto itr: umap){ 
				grid[itr.second.x][itr.second.y]= 0;
				int k = itr.second.x * col + itr.second.y;
				my_vector.push_back(k);
			}
			return sum;
		}
		else{
		/*Check if there any value sum <=6 */	
	 	for(int i=0; i< HXvalue.size(); i++){
	 	for(int j = i+1; j < HXvalue.size(); j++){
	 		if(HXvalue.at(i) + HXvalue.at(j) <=6){
	 			sumCapture = HXvalue.at(i) + HXvalue.at(j);
				grid[umap[HXpos[i]].x][umap[HXpos[i]].y] =0;
				grid[umap[HXpos[j]].x][umap[HXpos[j]].y] =0;
				int m =umap[HXpos[i]].x * col + umap[HXpos[i]].y; 
				int n =umap[HXpos[j]].x * col + umap[HXpos[j]].y;
				my_vector.push_back(m);
				my_vector.push_back(n);
				break;
	 		}
		}
		if(sumCapture >0){
				 return sumCapture;
			}
		}			
		}
	}
	return 1; 
}

int Board::checkWinningStatus(){
	if (!isBoardFull())
		return -2; //error message

	int counter = 0;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (grid[i][j] > 0)
				counter++;
		}
	}

	if (counter * 2 > row * col)
		return 1; //white player won
	else if (counter * 2 < row * col)
		return -1; //black player won
	else
		return 0;//draw
}

bool Board::validMove(int x, int y) {

	if (x < 0 || y < 0 || x > row - 1 || y > col - 1) {
		return false;
	}

	if (grid[x][y] != 0) {
		return false;
	}

	return true;
}

void Board::refreshIndex(int k){
	for(int i=0; i< my_vector.size(); i++){
		if( k == my_vector[i]){
			my_vector.erase(my_vector.begin() +i);
			break;
		}
	}
}

bool Board::addMove(int p, int x, int y) {
	if (p != player) {
		cout << "It is not the player's turn!" << endl;
		return false;
	}

	if (!validMove(x, y))
		return false;

	grid[x][y] = player * capturingPlacement(x, y);

	player = -1 * player;

	int i = x * col +y;
	refreshIndex(i);
	
	
	return true;
}

void Board::printBoard() {
	cout << "    ";
	for (int j = 0; j < col; j++) {
		cout << j + 1 << "   ";
	}
	cout << endl;

	for (int i = 0; i < row; i++) {
		cout << "  ";
		for (int j = 0; j < col; j++) {
			cout << " ---";
		}
		cout << endl;

		cout << (i + 1) << " |";

		for (int j = 0; j < col; j++) {
			if (grid[i][j] == 0) {
				cout << "   |";
			} else if (grid[i][j] > 0) {
				cout << " " << grid[i][j] << " |";
			} else if (grid[i][j] < 0) {
				cout << "" << grid[i][j] << " |";
			}
		}
		cout << endl;
	}
	cout << "  ";

	for (int j = 0; j < col; j++) {
		cout << " ---";
	}
	cout << endl << endl;
}

#endif /* BOARD_H_ */
