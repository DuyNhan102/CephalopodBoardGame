/*
 * 		Cell.h
 *
 *  	Created on: 25/02/2022
 *      Author: Duy Nhan Ta
 * 		StudentID: 20022020
 * 		Tutorial Class: 11:00AM Friday
 * 		Campus: Paramatta South
 */

#ifndef CELL_H_
#define CELL_H_

struct Cell {
	int x;
	int y;
	int value;
	double heuristic; 

	Cell(int xx, int yy, double hh):x(xx), y(yy), heuristic(hh) {}

	Cell(){
		x= 0;
		y= 0; 
		value = 0;
		heuristic = 0; 
	}
	bool operator<(const Cell& c) const {
		return heuristic < c.heuristic;
	}
};




#endif /* CELL_H_ */
