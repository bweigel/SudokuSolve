/*
 * solver.cpp
 *
 *  Created on: Nov 26, 2015
 *      Author: bweigel
 */
#include<iostream>
#include<cmath>
#include<cstdlib>
#include"sudoku.h"


int checkValid(SudokuGrid game){
	int GRID = charToint(GRID_SIZE);
	value CheckPosVal;
	std::cout << "\nChecking solvability!...";

	for(cell CheckPos = 1; CheckPos <= GRID; CheckPos++){
		CheckPosVal = game[CheckPos];
		clearCell(game, CheckPos);

		if(!isLegal(game, CheckPos, CheckPosVal) && CheckPosVal != '.'){
			std::cout << "This is not solveable!";
			return 0;
		} else {
			setCell(game, CheckPos, CheckPosVal);
		}
	}

	std::cout << "Good to go!";
	return 1;
}

int hasSolution(SudokuGrid game){
	cell candidateCell;
	value trialValue;
	// uncomment to follow the solving progress
	//printGame(game);
	BOOL solved;

	if(isFull(game)){
		solved = TRUE;
	} else {
		solved = FALSE;
		candidateCell = FindEmpty(game);
		trialValue = MIN_VALUE;

		int loop = charToint(trialValue);

		while(!solved  &&  loop <=  charToint(MAX_VALUE) ) {
			if(isLegal(game, candidateCell, trialValue)){
				setCell(game, candidateCell, trialValue);
				if(hasSolution(game)){
					solved = TRUE;
				} else {
					clearCell(game, candidateCell);
				}
			}
			loop ++;
			trialValue = intTochar(loop);
		}
	}
	return solved;
}

int getCellRow(cell Cell){
	int MAX = charToint(MAX_VALUE);
	int row = floor(Cell/MAX)+1;
	return(row);
}

int getCellColumn(cell Cell){
	int MAX = charToint(MAX_VALUE);
	return((Cell % MAX)+1);
}

int getBoxX(cell Cell){
	int MAX = charToint(MAX_VALUE);
	int a = floor(Cell/sqrt(MAX)), b = sqrt(MAX);
	return((a % b)+1);
}

int getBoxY(cell Cell){
	int MAX = charToint(MAX_VALUE);
	return(floor(floor(Cell/MAX) / sqrt(MAX))+1);
}

int charToint(char character){
	int integer = character - '0';
	return(integer);
}

char intTochar(int integer){
	char character = integer + 48;
	return(character);
}


void getBox(SudokuGrid game, int x, int y, Box CandidateBox){

	int MAX = charToint(MAX_VALUE);
	for(int i = 1; i <= MAX; i++){

		// formula to get the cells in each box
		int a= (i-1)+(x-1)*sqrt(MAX);
		int b = floor((i-1)/sqrt(MAX))*MAX + (MAX*sqrt(MAX))*(y-1);
		int c = floor((i-1)/sqrt(MAX))*sqrt(MAX);
		int cell = a+b-c;

		CandidateBox[i-1] = game[cell];
	}
}

int isLegal(SudokuGrid game, cell candidateCell, value candidateValue){

	// check row for validity
	int row = getCellRow(candidateCell);
	for(int i = 1; i <= charToint(MAX_VALUE); i++){
		// ... if the candidate value is already present in the row, return FALSE ...
		if(candidateValue == game[((row-1)*charToint(MAX_VALUE))+i-1]) {
			return 0;
		}
	}


	// check column for validity
	int column = getCellColumn(candidateCell);
	for(int i = 1; i <= charToint(MAX_VALUE); i++){
		// ... if the candidate value is already present in the column, return FALSE ...
		if(candidateValue == game[(column-1)+(i-1)*charToint(MAX_VALUE)]) {
			return 0;
		}
	}

	// check box for validity
	int box_X = getBoxX(candidateCell), box_Y = getBoxY(candidateCell);
	Box CandidateBox;
	// get the corresponding box and put in array
	getBox(game, box_X, box_Y, CandidateBox);

	// ... if the candidate value is already present in the box, return FALSE ...
	for(int i = 1; i <= charToint(MAX_VALUE); i++){
		if(candidateValue == CandidateBox[i-1]){
			return 0;
		}
	}

	//...otherwise return 1 (TRUE)
	return 1;
}

void setCell(SudokuGrid game, cell candidateCell, value candidateValue){
	game[candidateCell] = candidateValue;
}

void clearCell(SudokuGrid game, cell candidateCell){
	game[candidateCell] = '.';
}

int FindEmpty(SudokuGrid game){
	// This is a stepwise implementation
	  int i = 0;
		while(i <= 80){
			if(game[i] == '.'){
				return i;
			}
			i++;
		}

	/* this is a pseudo random implementation
	BOOL loop = TRUE;
	while(loop){
		int rnd = rand() % 81;
		if(game[rnd] == '.') {
			loop = FALSE;
			return rnd;
		}
	} */
	return 0;
}


int isAllowed(char value){
	for(int a = 0; a<=9; a++){
		if(value == (char) Allowed[a]) return 1;
	}
	return 0;
}

int readGame(SudokuGrid game){
	for(int i = 0; i <= MAX_CELL; i++){
		//check if the character is allowed, if not replace it with a '.' (the default blank character)
		if(!isAllowed(game[i])) game[i] = '.';
	}
	return 0;
}

int printGame(SudokuGrid game){
	std::cout << "\n\n";
	for(int i = 0; i <= MAX_CELL; i++){
		if(i != 0){
			if((i % 3) == 0 && i % 9 != 0) std::cout << "| ";
			if((i % 9) == 0 && (i % (9*3)) != 0) std::cout << "\n\t";
			if((i % (9*3)) == 0) std::cout << "\n\t------|-------|------\n\t";
		} else {
			std::cout <<"\t";
		}
		std::cout << game[i] << " ";
	}
	std::cout << "\n";
	return 0;
}

int isFull(SudokuGrid game){
	int i = 0;
	while(i <= 80){
		// check if there are any missing places in the grid
		if(game[i] == '.'){
			return 0;
		}
		i++;
	}
	return 1;
}
