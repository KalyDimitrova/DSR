#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

struct Travel {
	int number;
	string destination;
	string shipName;
	string captainName;
	double firstClassPrice;
	double secondClassPrice;
	int passangersFirstClass;
	int passangersSecondClass;
	int startDay;
	int endDay;
};

const int MAX_TRAVELS = 100;
int travelCount = 0;
int currentDay = 1;
Travel travels[MAX_TRAVELS];
// vector<Travel> travels;

void menu() {
	setlocale(LC_ALL, "");

	//TODO: fill all the choices
	cout << "МЕНЮ:\n"
		<< "1. Добавяне на пътуване\n"
		<< "2. Извеждане на всички записани пътувания\n"
		<< "3. Търсене на пътувания за определен интервал от време\n"
		<< "4. Търсене на пътувания до определена дестинация\n"
		<< "5. Сортиране на пътуванията по дестинация\n"
		<< "6. Записване на данните във външен файл\n"
		<< "7. Четене на данни от външен файл\n"
		<< "0. Изход от програмата\n";
}

int addTravel() {

	// must create functions to check if the captain/ship is already booked !!!

	if (travelCount == MAX_TRAVELS) {
		cout << "Максималният брой на пътувания е достигнат!\n";
		return 0;
	}

	int n;
	do {
		cout << "Въведете брой на пътувания, които искате да добавите: ";
		cin >> n;

		if (travelCount + n > MAX_TRAVELS) {
			cout << "Максималният брой на пътувания е достигнат!\n"
				<< "Въведете валиден брой пътувания!\n";
		}

	} while (travelCount + n > MAX_TRAVELS);


	for (int i = 0; i < n; i++) {
		Travel newTravel = {};

		cout << "Пътуване: " << i + 1 << endl;
		cout << "Въведете номер на пътуването: ";
		cin >> newTravel.number;

		cin.ignore();
		cout << "Въведете дестинация: ";
		cin >> newTravel.destination;

		cout << "Въведете име на кораб: ";
		cin >> newTravel.shipName;

		cout << "Въведете име на капитан: ";
		cin >> newTravel.captainName;

		cin.ignore();
		cout << "Въведете цена за първа класа: ";
		cin >> newTravel.firstClassPrice;

		cout << "Въведете цена за втора класа: ";
		cin >> newTravel.secondClassPrice;

		cout << "Въведете брой пътници за първа класа: ";
		cin >> newTravel.passangersFirstClass;

		cout << "Въведете брой пътници за втора класа: ";
		cin >> newTravel.passangersSecondClass;

		do {
			cout << "Въведете ден на тръгване: ";
			cin >> newTravel.startDay;

			cout << "Въведете ден на връщане: ";
			cin >> newTravel.endDay;

			if (newTravel.startDay > newTravel.endDay) {
				cout << "Денят на тръгване не може да бъде след деня на връщане!" << endl
					<< "Въведете валидни данни:\n";
			}
		} while (newTravel.startDay > newTravel.endDay);	

		travels[travelCount] = newTravel;
		travelCount++;
		return 0;
	}
}

// do the table !!!
void printAllTravels() {
	// must output all travles in a table !!!

	if (travelCount == 0) {
		cout << "Няма въведени пътувания.";
	}
}

void searchTravelSpecificPeriod(){
	// neshto si tam
	int minDay, maxDay;
	cout << "Въведете начален ден: ";
	cin >> minDay;
	cout << "Въведете краен ден: ";
	cin >> maxDay;

	bool isFound = false;
	for (int i = 0; i < travelCount; i++) {
		if (travels[i].startDay >= minDay && travels[i].endDay <= maxDay) {
			isFound = true;

			cout << "Намерени пътувания:\n"
				<< "Пътуване " << travels[i].number 
				<< " до " << travels[i].destination
				<< " на " << travels[i].startDay << " ден." << endl;
		}
	}

	if (!isFound) {
		cout << "Няма намерени пътувания за този период.\n";
	}
}

void searchDestinationTravel() {
	char destinationInput[50];
	cin.ignore();
	
	cout << "Въведете дестинация: ";
	cin.getline(destinationInput, sizeof(destinationInput));

	bool isFound = false;
	for (int i = 0; i < travelCount; i++) {
		// using strcmp (string compare) to see if the input destination has a match
		if (travels[i].destination == destinationInput) {
			isFound = true;

			cout << "Намерени пътувания:\n"
				<< "Пътуване " << travels[i].number
				<< " до " << travels[i].destination
				<< " на " << travels[i].startDay << " ден." << endl;
		}
	}


	if (!isFound) {
		cout << "Няма намерени пътувания до тази дестинация.\n";
	}
}

//TODO: fill all these functions accordingly
void sortTravelsByDestination() {
	// neshto
}

void giveInfoToExternalFile() {
	// neshto
}

void getInfroFromExternalFile() {
	// neshto
}

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
				<< "Довиждане!" << endl;
				break;
			default:
				cout << "Невалиден избор! Моля изберете отново: \n";
				break;
		}
	} while (choice != 0);


	return 0;
}
