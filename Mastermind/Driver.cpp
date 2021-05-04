// Jayden Campbell
// C++ coding final project
// Mastermind
// 1.0 - Introduced.
#include "Standard.h"
#include "Mastermind.h"
#include <filesystem>

//namespace fs = std::filesystem;

int displayMenu1();
void getHighScore(fstream&);


int main() {
	fstream file;
	file.open(createDirectory("\\Documents\\Mastermind") + "\\file",  ios::out | ios::binary | ios::app);
	file.close();
	file.open(createDirectory("\\Documents\\Mastermind") + "\\file", ios::out | ios::in | ios::binary | ios::app);
	if (file.is_open()) {
		cout << "   _____                   __                       .__            .___\n"
			<< "  /     \\ _____    _______/  |_  ___________  _____ |__| ____    __| _/\n"
			<< " /  \\ /  \\\\__  \\  /  ___/\\   __\\/ __ \\_  __ \\/     \\|  |/    \\  / __ |\n"
			<< "/    Y    \\/ __ \\_\\___ \\  |  | \\  ___/|  | \\/  Y Y  \\  |   |  \\/ /_/ |\n"
			<< "\\____|__  (____  /____  > |__|  \\___  >__|  |__|_|  /__|___|  /\\____ | \n"
			<< "        \\/     \\/     \\/            \\/            \\/        \\/      \\/ \n\n";
		Mastermind mastermind;
		char* board = mastermind.getBoard();
		bool left = false;
		cout << endl;
		while (!left) {
			switch (displayMenu1()) {

			case 1:

				while (mastermind.getTurns() != 0) {
					mastermind.play();
					mastermind.finalScore(file);
				}

				mastermind.setTurns();
				break;
			case 2:
				getHighScore(file);
				break;
			default:
				left = true;
				break;
			}
		}
	}
	else
		cout << "ERROR: File could not be generated.\n";
	cin.ignore(100, '\n');
	leave();
}

/*
* Displays menu 1. Requests integer input from the user. 
*/
int displayMenu1() {
	cout << "1. Play the game\n2. See high score\n3. Exit\n";
	return get<int>(1, 3, "Enter a menu choice:");
}

/*
*  Gets a high score from the user.
*/
void getHighScore(fstream& file) {
	
	if (file.peek() == std::fstream::traits_type::eof()) {
		cout << "There are no current scores.\n";
	}
	else {
		int tempHighScore;
		file.clear();
		file.seekg(0L, ios::beg);
		file.read(reinterpret_cast<char*>(&tempHighScore), sizeof(tempHighScore));

		cout << "The current high score is " << tempHighScore << endl;
	}
}
