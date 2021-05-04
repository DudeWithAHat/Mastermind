#pragma once

#ifndef MASTERMIND_H
#define MASTERMIND_H
#include "Standard.h"

class Mastermind {
private:
	static const int SIZE = 4; //Change for more/less rows
	static const int SIZE2 = 6; //Change for more/less choices
	char texture[SIZE2] = { 'R', 'C', 'P', 'Y', 'G', 'B' }; //Change to change the peg textures, add, or remove choices.
	char board[SIZE];
	int turns = 10; //(turns left in a round)
	int score = 0;
	int rounds = 0;
public:
	//Constructors (explained in Mastermind.cpp)
	Mastermind();

	Mastermind(int s, int r);
	//setters
	void setTurns();

	void setTurns(int t);

	void setBoard();

	void setScore();

	void setScore(int s);

	void setTexture(int t);

	void setRounds();

	void setRounds(int r);


	//getters
	static const int getSize();

	int getTurns();

	char* getBoard();

	int getScore();

	char* getTexture();


	//other (explained in Mastermind.ccp)
	void addScore(int s);

	void nextTurn();

	bool nextRound();

	int calculateScore();

	bool isTexture(char choices[]);

	bool isCorrect(char choices[]);

	bool play();

	void giveHints(char choices[]);

	void finalScore(fstream&);


};
#endif