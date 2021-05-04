#include "Mastermind.h"
#include "Standard.h"




//Sets turns to 10, score to 0, rounds to 0, and makes a randomly generated board.
Mastermind::Mastermind() {
	setTurns();
	setScore();
	setBoard();
	setRounds();
}

//Sets turns to 10, sets score to s, sets rounds to r, and makes a randomly generated board. used for continuing a game.
Mastermind::Mastermind(int s, int r) {
	setTurns();
	setScore(s);
	setBoard();
	setRounds(r);
}

//setters
void Mastermind::setTurns() {
	turns = 10;
}

void Mastermind::setTurns(int t) {
	turns = t;
}

//(Randomly selects characters on the board)
void Mastermind::setBoard() {
	char temp[SIZE2];
	for (int i = 0; i < SIZE2; i++) {
		temp[i] = texture[i];
	}
	for(int i = 0; i < SIZE2; i++)
		shuffle(temp, 6);
	for (int i = 0; i < SIZE; i++) {
		board[i] = temp[i];
	}
}

void Mastermind::setScore() {
	score = 0;
}

void Mastermind::setScore(int s) {
	score = s;
}

void Mastermind::setRounds() {
	rounds = 0;
}

void Mastermind::setRounds(int r) {
	rounds = r;
}


//getters
const int Mastermind::getSize() {
	return SIZE;
}

int Mastermind::getTurns() {
	return turns;
}

char* Mastermind::getBoard() {
	static char b[SIZE];
	for(int i = 0; i < SIZE; i++) {
		b[i] = board[i];
	}
	return b;
}

int Mastermind::getScore() {
	return score;
}

char* Mastermind::getTexture() {
	static char t[SIZE2];
	for(int i = 0; i < SIZE2; i++) {
		t[i] = texture[i];
	}
	return t;
}

/*
* Adds s to score.
*/
void Mastermind::addScore(int s) {
	score += s;
}

/*
* Decrements turn.
*/
void Mastermind::nextTurn() {
	turns -= 1;
}

/*
* Checks to see if user ran out of turns, or solved the puzzle.
* If user ran out of turns, returns true.
* If user solved the puzzle, resets turns to 10, and returns false.
*/
bool Mastermind::nextRound() {
	if (turns <= 0) {
		return true;
	}
	else {
		turns = 10;
		return false;
	}
}

/*
* Calculates the score based on the number of turns left.
*/
int Mastermind::calculateScore() {
	return 10 * pow((turns), 2);
}

/*
* Takes a set of choices. Returns true if they can all be found in texture. Returns false if ANY choice is invalid.
*/
bool Mastermind::isTexture(char choices[]) {
	bool validChoices = true;
	for (int i = 0; i < SIZE; i++) {
		bool validChoice = false;
		for (int j = 0; j < SIZE2; j++) {
			if (choices[i] == texture[j])
				validChoice = true;
		}
		if (validChoice == false)
			validChoices = false;
	}
	return validChoices;
}

bool Mastermind::isCorrect(char choices[]) {
	bool isCorrect = true;
	for (int i = 0; i < SIZE; i++) {
		if (choices[i] != board[i])
			isCorrect = false;
	}
	return isCorrect;
}

/*
* Asks user for 4 of the specified characters, and validates the data. returns true if user guessed correctly. Otherwise, tells the user which characters are in the right position, and which characters are the right color but are in the wrong position.
*/
bool Mastermind::play() {
	char choices[SIZE];
	while (turns != 0) {
	//	for (int i = 0; i < 4; i++)
	//		cout << board[i] << ' ';
		cout << "Turn " << turns << ": Please enter " << SIZE << " tokens, separated by a space. Your choices are:";
		for (int i = 0; i < SIZE2; i++) {
			cout << texture[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < SIZE; i++) {
			cin >> choices[i];


		}
		while (!isTexture(choices)) {
			cout << "Invalid Input. Please enter " << SIZE << " tokens, separated by a space. your choices are:";
			for (int i = 0; i < SIZE2; i++) {
				cout << texture[i] << " ";
			}
			cout << endl;
			for (int i = 0; i < SIZE; i++)
				cin >> choices[i];
		}
		if (isCorrect(choices)) {
			cout << "You Won in "<< turns << " turns!\n";
			addScore(calculateScore());
			cout << "Current Score is: " << score << endl;
			cout << "Next round..." << endl;
			nextRound();
			setTurns();
			setBoard();
		}
		else {
			
				cout << "Your choices were incorrect.\n";
				giveHints(choices);
				nextTurn();
		}
	}
	cout << "You Lose!\n";
	return true;
}

void Mastermind::giveHints(char choices[]) {
	int rightPositions = 0; //For pegs in the right position and color
	int rightColors = 0; //For pegs with the right color in the wrong position
	for (int i = 0; i < SIZE; i++) {
		if (choices[i] == board[i]) {
			rightPositions++;
		}
		else {
			bool isRightColor = false;
			for (int j = 0; j < SIZE; j++) {
				if (choices[i] == board[j]) {
					isRightColor = true;
				}
			}
			if (isRightColor) {
				rightColors++;
			}
		}
	}
	cout << "You have " << rightPositions << " pegs in the right position, and " << rightColors << " pegs with the a color that is on the board, but in the wrong position.\n";
}

/*
* Shows the users final score, and asks the user if they wish to save it. If they accept, saves the scores to a binary file.
*/
void Mastermind::finalScore(fstream& file) {
	int tempHighScore;
	file.clear();
	file.seekg(0L, ios::beg);
	file.read(reinterpret_cast<char*>(&tempHighScore), sizeof(tempHighScore));
	if (score > tempHighScore) {
		file.close();
		file.open(createDirectory("\\Documents\\Mastermind") + "\\file", ios::out | ios::in | ios::binary | ios::trunc);
		file.seekp(0L, ios::beg);
		file.write(reinterpret_cast<char*>(&score), sizeof(score));
		cout << "New high score! Updated high score to: " << score << endl;
	}
	else {
		cout << "Your final score was " << score << ".\n";
	}
}