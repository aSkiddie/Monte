#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cassert>
#include <fstream>
#include <string>

struct gameshow {

		void init_door();
		void shuffle();
		void print();
		void reveal(int&,char&,bool&);
		void statistics(char&, bool&);
		bool cardFound = false;
		bool stat = false;
		int doors[3];
		int goatDoor;
		char answer;
};

void gameshow::init_door() {doors[0] = 0;doors[1] = 1; doors[2] = 0;}

void gameshow::shuffle()
{
	srand ( time(NULL) );

	for (int i = 3-1; i > 0; i--) {
		int j = rand() % (i+1);
		int t = doors[i];
		doors[i] = doors[j];
		doors[j] = t;
	}
}

void gameshow::reveal(int& choice, char& answer, bool& stat) {
	for(int i = 0; cardFound != true; i++)
		if((i != choice) && (doors[i] != 1)) {
			std::cout << "\033[1;31m";
			std::cout << "Behind door " << (i + 1) << " there is a Goat\n\n";
			cardFound = true;
			goatDoor = i + 1;

			}

	std::cout << "\033[1;35mWould you like to choose a different door? (choose y or n): ";
	std::cin >> answer;
	assert(answer == 'y' || answer == 'n');
	if (answer == 'y') { 
		for(int i = 0; cardFound != false; i++) {
			if (i != choice && i != (goatDoor - 1)) {
		       		std::cout << "\033[1;30mBehind door " << (i + 1) << ((doors[i] == 0) ? " is a Goat!\033[1;40m\n" : " is the Luxury Car!\033[1;40m\n");
				cardFound = false;
				if(doors[i] == 1)
					stat = true;
				
			}
	
		}
	}
	
	else {
		std::cout << "\033[1;30mBehind door " << (choice + 1) << ((doors[choice] == 0) ? " is a Goat!\033[1;40m\n" : " is the Luxury Car!\033[1;40m\n");
			
			if(doors[choice] == 1)
				stat = true;

	}
}	

void gameshow::statistics(char& answer, bool& stat) {
	long double win, loss, total, percentage;
	std::string data;
	std::ofstream statfileW, statfileW2;
	std::ifstream statfileR, statfileR2;
	if(answer == 'y') {
		statfileR.open("statfile\"Y\".dat", std::ios::in | std::ios::out);  	
		statfileW.open("statfile\"Y\".dat", std::ios::in | std::ios::out);
	
		std::getline(statfileR, data);
		std::cout << data << '\n';
		win = std::stoi(data);
		std::getline(statfileR, data);
		loss = std::stoi(data);
		std::getline(statfileR, data);
		total = std::stoi(data);
		statfileR.close();

		if (stat == true) win++;
		else loss++;
		total++;	
	
		percentage = win/total;
		statfileW << win << ": Car\n" << loss << ": Goat\n" << total << ": Total Games Played\n" << percentage << ": Cars Won Percentage\n";
		statfileW.close();
	}

	else {
		statfileR2.open("statfile\"N\".dat", std::ios::in | std::ios::out);  	
		statfileW2.open("statfile\"N\".dat", std::ios::in | std::ios::out);
		
		std::getline(statfileR2, data);
		std::cout << data << '\n';
		win = std::stoi(data);
		std::getline(statfileR2, data);
		loss = std::stoi(data);
		std::getline(statfileR2, data);
		total = std::stoi(data);
		statfileR2.close();

		if (stat == true) win++;
		else loss++;
		total++;	
	
		percentage = win/total;
		statfileW2 << win << ": Car\n" << loss << ": Goat\n" << total << ": Total Games Played\n" << percentage << ": Cars Won Percentage\n";
		statfileW2.close();
	}
	
}


int main() {

	int choice, choice2;
	bool stat = false;
        char answer;
	gameshow game;
	game.init_door();
	game.shuffle();
	std::cout << "\033[1;47m\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	std::cout << "\033[1;30m";	
	std::cout << "You have 3 doors in front of you.\n";
	std::cout << "Behind two doors is a goat, and the other is a luxury car.\n\n";
	std::cout << "\033[1;31m";
	std::cout << "Make your choice (select 1, 2, or 3): ";
	
	std::cin >> choice;
	assert(choice > 0 && choice <= 3);
	choice--;
	assert(choice > 0 || choice < 3);
	std::cout << "\033[1;34mYou chose Door " << (choice + 1) << "\n";
	game.reveal(choice, answer, stat);
	game.statistics(answer, stat);
	return 0;
}
	
	




