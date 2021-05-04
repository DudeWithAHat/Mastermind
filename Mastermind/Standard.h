///******************************************************
/// Jayden Campbell
/// Standard Header File
/// 2.0 - Introduced.
/// 
/// 
/// 
/// 
#ifndef STANDARD_H
#define STANDARD_H
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <direct.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <random>
#include <string>
#include <shlobj.h>
#include <vector>
#include <windows.h>


using namespace std;

/*
*Holds the user until the required input is entered.
*/
template <class T>
inline T get(string desc) {
	T input;
	cout << desc;
	while (!(cin >> input) || cin.fail()) {
		cin.clear();
		cin.sync();
		cin.ignore(100, '\n');
		cout << "Invalid Input. " << desc;
	}
	return input;
}

template<>
inline int get<int>(string desc) {
	float input;
	cout << desc;
	while (!(cin >> input) || cin.fail() || input != static_cast<int>(input)) {
		cin.clear();
		cin.sync();
		cin.ignore(100, '\n');
		cout << "Invalid Input. " << desc;
	}
	return input;
}

/*
*Holds the user until the required input is entered. Input must be greater than/equal to min.
*/
template <class T1, class T2>
inline T1 get(T2 min, string desc) {
	T1 input;
	cout << desc;
	while (!(cin >> input) || cin.fail() || input < min) {
		cin.clear();
		cin.sync();
		cin.ignore(100, '\n');
		cout << "Invalid Input. " << desc;
	}
	return input;
}

template<>
inline int get<int>(int min, string desc) {
	float input;
	cout << desc;
	while (!(cin >> input) || cin.fail() || input != static_cast<int>(input) || input < min) {
		cin.clear();
		cin.sync();
		cin.ignore(100, '\n');
		cout << "Invalid Input. " << desc;
	}
	return input;
}
/*
* Holds the user until the required input is entered. Input must be greater than/equal to min, and less than/equal to max.
*/
template <class T1, class T2 >
inline T1 get(T2 min, T2 max, string desc) {
	T1 input;
	cout << desc;
	while (!(cin >> input) || cin.fail() || input < min || input > max) {
		cin.clear();
		cin.sync();
		cin.ignore(100, '\n');
		cout << "Invalid Input. " << desc;
	}
	return input;
}

template<>
inline int get<int>(int min, int max, string desc) {
	float input;
	cout << desc;
	while (!(cin >> input) || cin.fail() || input != static_cast<int>(input) || input < min || input > max) {
		cin.clear();
		cin.sync();
		cin.ignore(100, '\n');
		cout << "Invalid Input. " << desc;
	}
	return input;
}

/*
* Gets a file name from the user.
*/
inline string getFile() {
	string directory;
	string fileName;

	cout << "Please enter directory:";
	getline(cin, directory);
	cout << "Please enter file name (.txt files only):";
	getline(cin, fileName);

	return (directory + '\\' + fileName + ".txt");
}

/*
*Creates a directory to the file location specified by 'directory'.
* C:\Users\(user)\[directory]
*/
inline string createDirectory(string directory){
	char path[MAX_PATH];
	if (SHGetFolderPathA(NULL, CSIDL_PROFILE, NULL, 0, path) != S_OK)
	{
		throw "Couldn't retrieve the home directory.\n";
	}
	else
	{
		string newpath(path); 
		newpath.append(directory); 
		_mkdir(newpath.c_str());
		
		return newpath;
	}
	
}

/*
* Searches for 'value'. Can find multiple instances of the same value. Does not require the array to be in any specific order.
* slower than searchBinary.
*/
template <class T>
inline vector<int> searchLinear(const T list[], int size, float value) {
	int index = 0;
	vector<int> elementNums;
	for (int i = 0; i < size; i++) {
		if (list[i] == value) {
			elementNums.push_back(i);
		}
	}
	return elementNums;
}

template <class T>
inline vector<int> searchLinear(vector<T> list, float value) {
	int index = 0;
	vector<int> elementNums;
	for (int i = 0; i < list.size(); i++) {
		if (list[i] == value) {
			elementNums.push_back(i);
		}
	}
	return elementNums;
}

/*
* Searches for 'value'. Cannot find multiple instances of the same value. In order to function, the array must be in ascending or descending order.
* faster than searchLinear.
*/
template <class T>
inline T searchBinary(const T list[], int size, T value, bool isAscending) {
	int start = 0;
	int end = size - 1;
	int mid;
	int position = -1;
	bool found = false;
	
	if (isAscending) {
		while (start <= end && !found) {
			mid = (start + end) / 2;
			if (list[mid] == value) {
				position = mid;
				found = true;
			}
			else if (list[mid] > value) {
				end = mid - 1;
			}
			else {
				start = mid + 1;
			}
		}
	}
	else {
		while (start <= end && !found) {
			mid = (start + end) / 2;
			if (list[mid] == value) {
				position = mid;
				found = true;
			}
			else if (list[mid] < value) {
				end = mid - 1;
			}
			else {
				start = mid + 1;
			}
		}
	}
	return position;
}

template <class T>
inline T searchBinary(vector<T> list, T value, bool isAscending) {
	int start = 0;
	int end = list.size() - 1;
	int mid;
	int position = -1;
	bool found = false;

	if (isAscending) {
		while (start <= end && !found) {
			mid = (start + end) / 2;
			if (list[mid] == value) {
				position = mid;
				found = true;
			}
			else if (list[mid] > value) {
				end = mid - 1;
			}
			else {
				start = mid + 1;
			}
		}
	}
	else {
		while (start <= end && !found) {
			mid = (start + end) / 2;
			if (list[mid] == value) {
				position = mid;
				found = true;
			}
			else if (list[mid] < value) {
				end = mid - 1;
			}
			else {
				start = mid + 1;
			}
		}
	}
	return position;
}

/*
* Gets a random number between min and max.
*/
template <class T>
inline T getRandom(T min, T max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distr(min, max);
	return distr(gen);
}

/*
* Checks to see if a character is a vowel.
*/

/*
* Shuffles a deck.
*/
template<class T>
inline void shuffle(T array[], int size) {
	for (int i = 0; i < size; i++) {
		int r = (getRandom(0, (size - i)));
		swap(array[i], array[r]);
	}
}

inline bool isVowel(char character) {
	if (tolower(character) == 'a' || tolower(character) == 'e' || tolower(character) == 'i' || tolower(character) == 'o' || tolower(character) == 'u' || tolower(character) == 'y')
		return true;
	else
		return false;

}

/*
*Leaves the program.
*/
inline void leave() {
	cout << "\nPress any key to continue...\n";
	cin.get();
	exit(0);
}

#endif