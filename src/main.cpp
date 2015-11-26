/*
 * 	Name:		SudokuSolve
 *	Description:	Simple Sudoku solver. First project to learn a little C++.
 *					The program takes an argument which contains the sudoku puzzle.
 *					The puzzle is passed as a single string.
 *					If no argument is provided the puzzle can be provided at runtime.
 *					The solved puzzle is printed to screen.
 *
 *  Created on: Nov 26, 2015
 *      Author: bweigel
 */
#include<iostream>
#include"sudoku.h"

int main(int argc, char *argv[]){
	using std::cout;
	using std::cin;
	using std::endl;

	SudokuGrid sample;

	cout << "\f\t-----------------------------------------------------------\n";
	cout << "\t---\tWelcome to the sudoku solver by bweigel!\t---\n";
	cout << "\t-----------------------------------------------------------\n";
	if(argc > 1){
		//copy arguments into sample array if a arguments is given
		std::copy(argv[1], argv[1]+sizeof(argv[1]), sample);
	} else {
		cout << "Gimme plox!\n";
		cin >> sample;
	}

	//cout << "Size of sample: " << sizeof(sample) <<endl;
	// structure game into desired format
	readGame(sample);
	// print the input
	cout << "\n\nThis is your input: \n";
	printGame(sample);

	// check the games validity first
	if(!checkValid(sample)){
		return 0;
	}

	// check for a solution
	hasSolution(sample);

	//print the solution
	cout << "\n\nThis is (one/the) solution: \n";
	printGame(sample);

	return 0;
}

