/*
 * sudoku.h
 *
 *  Created on: Nov 26, 2015
 *      Author: bweigel
 */

#ifndef SUDOKU_H_
#define SUDOKU_H_


const char MIN_VALUE = '1';
const char MAX_VALUE = '9';
const char EMPTY_VALUE = '.';
const int NUM_VALUES = (MAX_VALUE-MIN_VALUE)+1;
const int GRID_SIZE = NUM_VALUES*NUM_VALUES;
const int MAX_CELL = GRID_SIZE-1;
const char Allowed[10] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};
enum BOOL {TRUE = 1, FALSE = 0};

typedef int cell;
typedef char value;
typedef value SudokuGrid[GRID_SIZE];
typedef value Box[MAX_VALUE];
//typedef int ValArray[];

int hasSolution(SudokuGrid game);
int readGame(SudokuGrid game);
int isAllowed(char value);
int printGame(SudokuGrid game);
int FindEmpty(SudokuGrid game);
int isFull(SudokuGrid game);
int isLegal(SudokuGrid game, cell candidateCell, value candidateValue);
void setCell(SudokuGrid game, cell candidateCell, value candidateValue);
void clearCell(SudokuGrid game, cell candidateCell);
int checkValid(SudokuGrid game);
int charToint(char character);
char intTochar(int integer);
void getBox(SudokuGrid game, int x, int y, Box CandidateBox);
int getBoxX(cell Cell);
int getBoxY(cell Cell);
int getCellRow(cell Cell);
int getCellColumn(cell Cell);



#endif /* SUDOKU_H_ */
