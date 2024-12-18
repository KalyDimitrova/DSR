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
int currentDay;
Travel travels[MAX_TRAVELS];

void menu() {
	setlocale(LC_ALL, "");

	cout << "\t\t\tМЕНЮ:\n"
		<< "0. Изход от програмата\n"
		<< "1. Добавяне на пътуване\n"
		<< "2. Извеждане на всички записани пътувания\n"
		<< "3. Търсене на пътувания за определен интервал от време\n"
		<< "4. Търсене на пътувания до определена дестинация\n"
		<< "5. Сортиране на пътуванията по дестинация\n"
		<< "6. Записване на данните във външен файл\n"
		<< "7. Четене на данни от външен файл\n";
}

// must create functions to check if the captain/ship is already booked !!!
int addTravel() {
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

		cout << "Въведете дестинация: ";
		cin >> newTravel.destination;

		cout << "Въведете име на кораб: ";
		cin >> newTravel.shipName;

		cout << "Въведете име на капитан: ";
		cin >> newTravel.captainName;

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
	}
	return 0;
}

// do the table !!!
void printAllTravels() {
	if (travelCount == 0) {
		cout << "Няма въведени пътувания.";
	}
}

void searchTravelSpecificPeriod(){
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
	for (int i = 0; i < travelCount - 1; i++) {
		for (int j = 0; j < travelCount - i - 1; j++) {
			if (travels[j].destination > travels[j + 1].destination) {
				Travel temp = travels[j];
				travels[j] = travels[j + 1];
				travels[j + 1] = temp;
			}
		}
	}
	cout << "Пътуванията са сортирани по дестинация.\n";
}

void giveInfoToExternalFile() {
	// neshto
}

void getInfroFromExternalFile() {
	fstream fileInput("travels.txt", ios::in);

	// think how to input all the data
	/*  Пътуване 1:
		Номер на пътуване : 634263
		Дестинация : Варна
		Име на кораб : Черната Перла
		Име на капитан : Джак Спароу
		Цена за първа класа : 120
		Цена за втора класа : 80
		Брой пътници в първа класа : 20
		Брой пътници във втора класа : 130
		Ден на тръгване : 13
		Ден на връщане : 25  */
}

void travelStatus() {
	// neshto
}

int main() {
	cout << "Въведете текущ ден от месеца (1-31): ";
	cin >> currentDay;

	travelStatus();

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
				cout << "Данните са записани успешно!\n";
				break;
			case 7:
				getInfroFromExternalFile();
				break;
			case 0:
				cout << "Довиждане!" << endl;
				break;
			default:
				cout << "Невалиден избор! Моля изберете отново: \n";
				break;
		}
	} while (choice != 0);


	return 0;
}
