#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

//TODO: fill the struct
struct Travel {
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
Travel travel[MAX_TRAVELS];

void menu() {
	setlocale(LC_ALL, "");

	//TODO: fill all the choices
	cout << "МЕНЮ:\n"
		<< "1. Добавяне на пътуване"
		<< "2. Извеждане на всички записани пътувания"
		<< "3. Търсене на пътувания за определен интервал от време"
		<< "4. Търсене на пътувания до определена дестинация"
		<< "5. Сортиране на пътуванията по дестинация"
		<< "6. Записване на данните във външен файл"
		<< "7. Четене на данни от външен файл"
		<< "0. ";
}

void addTravel() {

	// must create functions to check if the captain/ship is already booked !!!

	if (travelCount == MAX_TRAVELS) {
		cout << "Максималният брой на пътувания е достигнат!\n";
	}

	cout << "Въведете брой на пътувания, които искате да добавите: ";
	int n;
	cin >> n;

	if (travelCount + n > MAX_TRAVELS) {
		cout << "Максималният брой на пътувания е достигнат!\n"
			<< "Въведете валиден брой пътувания!";
	}

	for (int i = 0; i < n; i++) {
		Travel newTravel = {};

		cout << "Пътуване " << i + 1;
		cout << "Въведете номер на пътуването: ";
		cin >> newTravel.number;

		cin.ignore();
		cout << "\nВъведете дестинация: ";
		cin.getline(newTravel.destination, 50);

		cout << "\nВъведете име на кораб: ";
		cin.getline(newTravel.shipName, 50);

		cout << "\nВъведете име на капитан: ";
		cin.getline(newTravel.captainName, 50);

		cout << "\nВъведете цена за първа класа: ";
		cin >> newTravel.firstClassPrice;

		cout << "\nВъведете цена за втора класа: ";
		cin >> newTravel.secondClassPrice;

		cout << "\nВъведете брой пътници за първа класа: ";
		cin >> newTravel.passangersFirstClass;

		cout << "\nВъведете брой пътници за втора класа: ";
		cin >> newTravel.passangersSecondClass;

		cout << "\nВъведете ден на тръгване: ";
		cin >> newTravel.startDay;

		cout << "\nВъведете ден на връщане: ";
		cin >> newTravel.endDay;

		if (newTravel.startDay > newTravel.endDay) {
			cout << "\nДенят на тръгване не може да бъде след деня на връщане!" << endl;
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
				cout << "Данните са записани успешно!\n"
				<< "Довиждане!";
				break;
			default:
				cout << "Невалиден избор! Моля изберете отново: ";
				break;
		}
	} while (choice != 0);


	return 0;
}
