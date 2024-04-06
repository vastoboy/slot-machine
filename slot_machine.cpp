#include <iostream>
#include <conio.h> 
#include <stdlib.h> 
#include <ctype.h>  
#include <windows.h> 
#include <string> 
#include <time.h> 

using namespace std;

int credit = 100;
string slot_items[3][3] = { {"@","#","$" }, {"@","#","$" }, {"@","#","$" } };
char key;
bool win = false;
int keyPress_counter = 0;
int rand_item1 = 0;
int rand_item2 = 0;
int i = 0;
int j = 0;


//check if the user has won any prize 
bool check_win() {

	if (slot_items[0][0] == slot_items[0][1] && slot_items[0][1] == slot_items[0][2]) { //check if the all 3 values in the first row matches 
		credit += 50; //credit the user $50
		win = true; //set bolean win euals to true 
	}

	if (slot_items[1][0] == slot_items[1][1] && slot_items[1][1] == slot_items[1][2]) {  //check if the all 3 values in the second row matches 
		credit += 50;
		win = true; //set bolean win equals to true 
	}

	if (slot_items[2][0] == slot_items[2][1] && slot_items[2][1] == slot_items[2][2]) {  //check if the all 3 values in the third row matches 
		credit += 50;
		win = true; //set bolean win equals to true 
	}
	return win;
}

//allows user to exit the game with their balance 
void user_cashout(char key) {
	if (key == 'C') {
		cout << "Your total cash is $" << credit;
		Sleep(300); //pause the program for 3 seconds 
		exit(0); //exit the program 
	}
}


void print_art() {
		cout << " ________                __   __            __       __                   __       __                        " << endl;
		cout << "/        |              /  | /  |          /  \\     /  |                 /  |     /  |                      " << endl;
		cout << "$$$$$$$$______  __    __$$/ _$$ |_         $$  \\   /$$ | ______   _______$$ |____ $$/ _______   ______	  " << endl;
		cout << "$$ |__ /      \\/  |  /  /  / $$   |        $$$  \\ /$$$ |/      \\ /       $$      \\/  /       \\ / \\     " << endl;
		cout << "$$    /$$$$$$  $$ |  $$ $$ $$$$$$/         $$$$  /$$$$ |$$$$$$  /$$$$$$$/$$$$$$$  $$ $$$$$$$  /$$$$$$  |     " << endl;
		cout << "$$$$$/$$ |  $$/$$ |  $$ $$ | $$ | __       $$ $$ $$/$$ |/    $$ $$ |     $$ |  $$ $$ $$ |  $$ $$    $$ |     " << endl;
		cout << "$$ |  $$ |     $$ \\__$$ $$ | $$ |/  |      $$ |$$$/ $$ /$$$$$$$ $$ \\_____$$ |  $$ $$ $$ |  $$ $$$$$$$$/    " << endl;
		cout << "$$ |  $$ |     $$    $$/$$ | $$  $$/       $$ | $/  $$ $$    $$ $$       $$ |  $$ $$ $$ |  $$ $$       |     " << endl;
		cout << "$$/   $$/       $$$$$$/ $$/   $$$$/        $$/      $$/ $$$$$$$/ $$$$$$$/$$/   $$/$$/$$/   $$/ $$$$$$$/      " << endl << endl;

		cout << "Press S to toggle Slow Spins and stop wheel, C to Cash out" << endl;
		cout << "Current Credit: " << "$" << credit << endl << endl;
}



void run_game() {
	while (true) {

		for (i = 0, j = 0; j < sizeof(slot_items) / sizeof(slot_items[0]) - 1; ++j, i++) { //spins the wheel

			if (keyPress_counter == 0) { //shuffles all values within the array
				rand_item1 = rand() % sizeof(slot_items) / sizeof(slot_items[0]);
				rand_item2 = rand() % sizeof(slot_items) / sizeof(slot_items[0]);
			}
			else if (keyPress_counter == 1) { //exclude the first row from shuffling if key counter equals 1 

				rand_item2 = rand() % (1 - 0 + 1) + 1;  
				rand_item1 = rand() % (2 - 0 + 1) + 0;

				if (j == 0) {
					j = rand() % (1 - 0 + 1) + 1;
				}
			}
			else if (keyPress_counter == 2) { //exclude the second row from shuffling if key counter equals 2

				rand_item2 = 2;
				rand_item1 = rand() % (2 - 0 + 1) + 0;

				if (j == 0 || j == 1) {
					j = 2;
				}
			}


			system("CLS");


			//shuffel the value withing the array
			string temp = slot_items[i][j];
			slot_items[i][j] = slot_items[rand_item1][rand_item2];
			slot_items[rand_item1][rand_item2] = temp;

			print_art();

			cout << "***********************************" << endl;
			cout << "*" << "	                          *" << endl;
			cout << "*" << "	                          *" << endl;
			cout << "*\t" << slot_items[0][0] << "\t " << slot_items[0][1] << "\t " << slot_items[0][2] << "        *" << endl << flush;
			cout << "*\t" << slot_items[1][0] << "\t " << slot_items[1][1] << "\t " << slot_items[1][2] << "        *" << endl << flush;
			cout << "*\t" << slot_items[2][0] << "\t " << slot_items[2][1] << "\t " << slot_items[2][2] << "        *" << endl << flush;
			cout << "*" << "	                          *" << endl;
			cout << "*" << "	                          *" << endl;
			cout << "***********************************" << endl;


			if (_kbhit()) {

				key = toupper(_getch());  //gets user keyboard input

				if (key == 'S') {
					keyPress_counter++; //add one to counter everytime S is pressed

					if (key == 'S' && keyPress_counter == 3) { //if the user has stopped all the wheels
						keyPress_counter = 0;
						check_win(); //check if the values within a row matches 
						 if (win) { //if all three value within the array matches 

							cout << "We have a match!!!" << endl;
							cout << "Your new balance is $" << credit << endl;

							win = false; //set booloean win to false in the event the user decides to play again
							key = toupper(_getch());
							user_cashout(key);

						}
						else {
							
							if (credit <= 0) { // exits the game if the player's balance equals 0
								cout << "You have lost al your money!!!";
								cout << "Gambling is a terrible hobby!!!";
								Sleep(300);
								exit(0);
							}

							else {
								// deduct $10 if not of the value in the row matches 
								credit -= 10;
								cout << "Better luck next time!!!" << endl;
								cout << "Press any key to continue....." << endl;
								key = toupper(_getch());
								user_cashout(key); //check if user wants to cash out 

							}
						}

					}
				}
			}
		}
	}
}


int main() {
	
	print_art();


	while (key != 'S') { //start the game only when the user presses S
		key = toupper(_getch());

		if (key == 'S') {

			run_game(); //start game 
		}
	}
	return 0;

}
