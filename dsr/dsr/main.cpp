#include <iostream>

using namespace std;

//TODO: fill the struct
struct travels {

};

//TODO: create all global variables needed
const int MAX_TRAVELS = 100;

void menu() {
	setlocale(LC_ALL, "");

	//TODO: fill all the choices
	cout << "МАНЮ:\n"
		<< "1. "
		<< "2. "
		<< "3. "
		<< "4. "
		<< "5. "
		<< "6. "
		<< "7. "
		<< "0. ";
}

//TODO: fill all these functions accordingly
void addTravel();
void printAllTravels();
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