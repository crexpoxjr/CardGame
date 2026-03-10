#include <iostream>
#include <ctype.h>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
using namespace std;

const int SIZE = 4;
enum Choice {Match = 1, Display = 2, Giveup = 3, Exit = 4};

string getName() {
	int i;
	int j;
	string username;
	bool isValid = true;
	bool capNext = true;

	do {
		cout << "Enter your name: ";
		getline(cin, username);

		isValid = true;
		for (i = 0; username.size() > i; ++i) {
			if (!isalpha(username.at(i)) && !isspace(username.at(i))){
					isValid = false;
					break;
					}
		}
		if (!isValid) {
			cout << "You can only have alphabets or spaces. Enter again." << endl;
		}
	}while (!isValid);

	for (j = 0; j < username.length(); ++j) {
		if (isspace(username.at(j))) {
			capNext = true;
		}
		else if (capNext) {
			username.at(j) = toupper(username.at(j));
			capNext = false;
		}
		else {
			username.at(j) = tolower(username.at(j));
		}
	}

	return username;
}

int genRandomIndex() {
	int index;

	index = (rand() % SIZE);

	return index;
}

void shuffle(int cardArr[][SIZE]) {
	int i;
	int x1;
	int y1;
	int x2;
	int y2;
	int tmpVal;
	srand(time(0));

	for(i = 0; i < 15; ++i) {
		x1 = genRandomIndex();
		y1 = genRandomIndex();
		x2 = genRandomIndex();
		y2 = genRandomIndex();
		tmpVal = cardArr[x1][y1];
		cardArr[x1][y1] = cardArr[x2][y2];
		cardArr[x2][y2] = tmpVal;
	}
}

void initialize(int cardArr[][SIZE], int cardStat[][SIZE]) {
	int i;
	int j;
	int values[SIZE*SIZE] = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8};
	int index = 0;

	for (i = 0; i < SIZE; ++i){
		for (j = 0; j < SIZE; ++j) {
			cardArr[i][j] = values[index++];
		}
	}

	shuffle(cardArr);

	for (i = 0; i < SIZE; ++i) {
		for (j = 0; j < SIZE; ++j) {
			cardStat[i][j] = 0;
		}
	}

	 
}

void showCards(int cardArr[][SIZE], int cardStat[][SIZE], bool showReal = false)
{
	int i;
	int j;

	cout << "|   ";
	for (j = 0; j < SIZE; j++) {
		cout << "|  " << j << "   ";
	}
	cout << "|\n";


	for (i = 0; i < SIZE; ++i){
		cout << "| " << i << " ";

		for (j = 0; j < SIZE; ++j) {
			cout << "| ";
			if (showReal || cardStat[i][j] == 1) {
				cout << cardArr[i][j];
			}
			else {
				cout << "*";
			}
			cout << "    ";
		}
		cout << "|\n";
	}
}

bool allFaceUp(int cardStat[][SIZE]) {
	int i;
	int j;

	for(i = 0; i < SIZE; ++i) {
		for (j = 0; j < SIZE; ++j) {
			if (cardStat[i][j] == 0) {
				return false;
				}
			}
		}
	return true;
	}

bool checkInputs(int x, int y, int cardStat[][SIZE]) {
	bool isValid;

	if ((((x >= 0) && (x < SIZE)) && ((y >= 0) && (y < SIZE))) && (cardStat[x][y] == 0)) {
			isValid = true;
	}
			else {
				isValid = false;
			}
	return isValid;
}

void match (int cardArr[][SIZE], int cardStat[][SIZE], int& points){
	int x1;
	int y1;
	int x2;
	int y2;

	showCards(cardArr, cardStat);

	cout << "Enter coordinates for the first card:";
	cin >> x1 >> y1;

	if (!checkInputs(x1, y1, cardStat)) {
		if ((x1 > SIZE) || (y1 > SIZE)) {
			cout << "Invalid card selection!" << endl;
			return;
		}
		cout << "Card is already facing up!" << endl;
		return;
	}

	cout << "Enter coordinates for second card:";
	cin >> x2 >> y2;

	if (!checkInputs(x2, y2, cardStat)) {
		if ((x2 > SIZE) || (y2 > SIZE)) {
			cout << "Invalid card selection!" << endl;
			return;
		}
		cout << "Card is already facing up!" << endl;
		return;
	}

	if (x1 == x2 && y1 == y2) {
		cout << "You selected the same card twice." << endl;
		return;
	}


	int card1 = cardArr[x1][y1];
	int card2 = cardArr[x2][y2];

	if (card1 == card2) {
		cardStat[x1][y1] = 1;
		cardStat[x2][y2] = 1;
		points += 5;
		cout << "Cards match at locations: (" << x1 << ", " << y1 << ")" << " and " << "(" << x2 << ", " << y2 << ")" << endl;
		cout << "Your updated points are: " << points << endl;
	}
	else {
		cardStat[x1][y1] = 1;
		cardStat[x2][y2] = 1;
		showCards(cardArr, cardStat, false);
		sleep(5);
		system("clear");
		points -= 1;

		cout << "Cards do not match at locations: (" << x1 << ", " << y1 << ")" << " and " << "(" << x2 << ", " << y2 << ")" << endl;
		cout << "Your updated points are: " << points << endl;
		cardStat[x1][y1] = 0;
		cardStat[x2][y2] = 0;

	}



}

void display(int cardArr[][SIZE], int cardStat[][SIZE], int& points) {
	int i;
	int j;
	if (points < 10) {
		cout << "Error: Insufficient points!" << endl;
		return;
	}

	int x1 = -1;
	int y1 = -1;

	for (i = 0; i < SIZE; ++i) {
		for (j = 0; j < SIZE; ++j) {
			if (cardStat[i][j] == 0) {
				x1 = i;
				y1 = j;
				break;
			}
		}
		if (x1 != -1) {
			break;
		}
	}

	if (x1 == -1) {
		cout << "All cards are already facing up!" << endl;
		return;
	}

	int x2 = -1;
	int y2 = -1;

	for (i = 0; i < SIZE; ++i) {
		for (j = 0; j < SIZE; ++j) {
			if ((cardStat[i][j] == 0) && (i != x1 || j != y1) && cardArr[i][j] == cardArr[x1][y1]) {
				
				x2 = i;
				y2 = j;
				break;
			}
		}
		if (x2 != -1) {
			break;
		}
	}
	cardStat[x1][y1] = 1;
	cardStat[x2][y2] = 1;

	points -= 10;

	cout << "Revealed matching pair:" << endl;
	showCards(cardArr, cardStat, false);
	cout << "Your updated points are: " << points << endl;

}

int main() {

	int points = 50;
	char exitChar;
	bool exit = false;
	int arrCards[SIZE][SIZE];
	int statCards[SIZE][SIZE];
	int choice;

	cout << "+--------------------------------------------------+\n"
		"|	  Computer Science and Engineering     	   |\n"
		"|	   CSCE 1030 - Computer Science I          |\n"
		"| Hecdier Crespo hdc0074 HecdierCrespo@my.unt.edu  |\n"
		"+--------------------------------------------------+\n";


	string name = getName();
	cout <<"Welcome, " << name << "." << endl;
	initialize(arrCards, statCards);
	do {
		cout << "\n1. Match\n2. Display\n3. Giveup\n4. Exit" << endl;
		cout << "What would you like to do?";
		cin >> choice;
	
		switch(choice) {
			case Match:
				match(arrCards, statCards, points);
				if (allFaceUp(statCards) == true){
					cout << "Would you like to play another game? Y/N:";
					cin >> exitChar;
					if (toupper(exitChar) != 'N') {
						initialize(arrCards, statCards);
					}
				}


				break;
			case Display:
				display(arrCards, statCards, points);
				break;
			case Giveup:
				cout << "The locations of the cards are: " << endl;
				showCards(arrCards, statCards, true);
				cout << "Would you like to start a new game? Y/N:";
				cin >> exitChar;
				if (toupper(exitChar) != 'N') {
					initialize(arrCards, statCards);
				}
				break;
			case Exit:
				exit = true;
				break;
			default:
				cout << "Invalid choice. Try again." << endl;
				break;
		}
	}while ((exit != true) && (toupper(exitChar) != 'N'));
	cout << "Your final points are: " << points << endl;
	cout << "Goodbye, " << name << "." << endl;
	return 0;
}
