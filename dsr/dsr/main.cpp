#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

//TODO: fill the struct
struct travels {
	int number;
	char destination[50];
	char shipName[50];
	char captainName[50];
	double firstClassPrice;
	double secondClassPrice;
	int passangersFirstClass;
	int passangersSecondClass;
	int startDay;
	int endDay;
	char status[50];
};

//TODO: create all global variables needed
const int MAX_TRAVELS = 100;
int travelCount = 0;
int currentDay = 1;
travels travel[MAX_TRAVELS];

void menu() {
	setlocale(LC_ALL, "");

	//TODO: fill all the choices
	cout << "МЕНЮ:\n"
		<< "1. "
		<< "2. "
		<< "3. "
		<< "4. "
		<< "5. "
		<< "6. "
		<< "7. "
		<< "0. ";
}

void addTravel() {

	// must create functions to check if the captain/ship is already booked !!!

	if (travelCount >= MAX_TRAVELS) {
		// write the massage that the max travel count is reached
		cout << "";
	}

	// message: input travels count to add
	cout << "";
	int n;
	cin >> n;

	if (travelCount + n > MAX_TRAVELS) {
		// message: there could not be more travels
		cout << "";
	}

	for (int i = 0; i < n; i++) {
		travels newTravel = {};

		cout << ""; // travel i + 1 
		cout << ""; // number of travel
		cin >> newTravel.number;

		// destination, shipName, captainName (the same way for all 3, just gotta figure out how)
		cin.ignore();
		cout << ""; // destination
		// input the destination

		cout << ""; // first class price
		cin >> newTravel.firstClassPrice;

		cout << ""; // second class price
		cin >> newTravel.secondClassPrice;

		cout << ""; // first class passangers
		cin >> newTravel.passangersFirstClass;

		cout << ""; // second class passangers
		cin >> newTravel.passangersSecondClass;

		cout << ""; // start dya
		cin >> newTravel.startDay;

		cout << ""; // end day
		cin >> newTravel.endDay;

		if (newTravel.startDay > newTravel.endDay) {
			cout << ""; // error message
		}
	}

}

//TODO: fill all these functions accordingly
void printAllTravels() {
	// must output all travles in a table !!!
}
void searchTravelSpecificPeriod();
void searchDestinationTravel();
void sortTravelsByDestination();
void giveInfoToExternalFile();
void getInfroFromExternalFile();

int main() {
	int choice;

	do {
		menu();
		cin >> choice;
		
		switch (choice){
			case 1:
				addTravel();
				break;
			case 2:
				printAllTravels();
				break;
			case 3:
				searchTravelSpecificPeriod();
				break;
			case 4:
				searchDestinationTravel();
				break;
			case 5:
				sortTravelsByDestination();
				break;
			case 6:
				giveInfoToExternalFile();
				break;
			case 7:
				getInfroFromExternalFile();
				break;
			case 0:
				cout << "Данните са записани успешно!\n";
				break;
			default:
				cout << "Невалиден избор! Моля изберете отново: ";
				break;
		}
	} while (choice != 0);


	return 0;
}
