﻿#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

struct Travel {
	int number = 0;
	string destination;
	string shipName;
	string captainName;
	int startDay = 0;
	int endDay = 0;
	double firstClassPrice = 0.0;
	double secondClassPrice = 0.0;
	int passangersFirstClass = 0;
	int passangersSecondClass = 0;
	string status;
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
		<< "7. Четене на данни от външен файл\n"
		<< "8. Завършили пътувания до дестинация\n"
		<< "9. Пътувания на капитан за период\n"
		<< "10. Промяна на пътуване\n";
}

bool isShipCaptainAvailable(const string& shipName, const string& captainName, int startDay, int endDay, int currentTravelIndex = -1) {
	for (int i = 0; i < travelCount; i++) {
		if (i == currentTravelIndex) continue;

		bool datesOverlap = !(endDay < travels[i].startDay || startDay > travels[i].endDay);

		if (datesOverlap && (travels[i].shipName == shipName || travels[i].captainName == captainName)) {
			return false;
		}
	}
	return true;
}

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

		bool validTravelData = false;
		do {
			cout << "Въведете име на кораб: ";
			cin >> newTravel.shipName;

			cout << "Въведете име на капитан: ";
			cin >> newTravel.captainName;

			cout << "Въведете ден на тръгване: ";
			cin >> newTravel.startDay;

			cout << "Въведете ден на връщане: ";
			cin >> newTravel.endDay;

			if (newTravel.startDay > newTravel.endDay) {
				cout << "Денят на тръгване не може да бъде след деня на връщане!" << endl
					<< "Въведете валидни данни.\n";
				continue;
			}

			if (!isShipCaptainAvailable(newTravel.shipName, newTravel.captainName,
				newTravel.startDay, newTravel.endDay)) {
				cout << "Корабът или капитанът са заети в този период!\n"
					<< "Въведете други данни.\n";
				continue;
			}

			validTravelData = true;

		} while (!validTravelData);

		cout << "Въведете цена за първа класа: ";
		cin >> newTravel.firstClassPrice;

		cout << "Въведете цена за втора класа: ";
		cin >> newTravel.secondClassPrice;

		cout << "Въведете брой пътници за първа класа: ";
		cin >> newTravel.passangersFirstClass;

		cout << "Въведете брой пътници за втора класа: ";
		cin >> newTravel.passangersSecondClass;

		if (currentDay < newTravel.startDay) {
			newTravel.status = "В очакване";
		}
		else if (currentDay > newTravel.endDay) {
			newTravel.status = "Отминало";
		}
		else {
			newTravel.status = "В процес на изпълнение";
		}

		travels[travelCount] = newTravel;
		travelCount++;
	}
	return 0;
}

void printAllTravels() {
	if (travelCount == 0) {
		cout << "Няма въведени пътувания.";
		return;
	}

	cout << setfill('-') << setw(100) << "-" << setfill(' ') << endl;
	cout << setw(8) << "Номер" << " | "
		<< setw(12) << "Дестинация" << " | "
		<< setw(12) << "Кораб" << " | "
		<< setw(12) << "Капитан" << " | "
		<< setw(10) << "Статус" << " | "
		<< setw(12) << "Дати" << endl;
	cout << setfill('-') << setw(100) << "-" << setfill(' ') << endl;

	for (int i = 0; i < travelCount; i++) {
		cout << setw(8) << travels[i].number << " | "
			<< setw(12) << travels[i].destination << " | "
			<< setw(12) << travels[i].shipName << " | "
			<< setw(12) << travels[i].captainName << " | "
			<< setw(10) << travels[i].status << " | "
			<< setw(2) << travels[i].startDay << "-"
			<< setw(2) << travels[i].endDay << endl;
	}
	cout << setfill('-') << setw(100) << "-" << setfill(' ') << endl;
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

//TODO: fill all these functions accordingly
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
	if (travelCount == 0) {
		cout << "Няма въведени пътувания за проверка." << endl;
		return;
	}

	for (int i = 0; i < travelCount; i++) {
		if (currentDay < travels[i].startDay) {
			travels[i].status = "В очакване";
		}
		else if (currentDay > travels[i].endDay) {
			travels[i].status = "Отминало";
		}
		else {
			travels[i].status = "В процес на изпълнение";
		}
	}
}

void modifyTravel() {
	int travelNumber;
	cout << "Въведете номер на пътуването за промяна: ";
	cin >> travelNumber;

	// Намиране на пътуването
	int travelIndex = -1;
	for (int i = 0; i < travelCount; i++) {
		if (travels[i].number == travelNumber) {
			travelIndex = i;
			break;
		}
	}

	// Проверка дали пътуването съществува
	if (travelIndex == -1) {
		cout << "Пътуване с този номер не е намерено.\n";
		return;
	}

	// Проверка на статуса
	if (travels[travelIndex].status != "В очакване") {
		cout << "Пътуването не може да бъде променено - "
			<< (travels[travelIndex].status == "Отминало" ? "вече е отминало" : "е в процес на изпълнение")
			<< endl;
		return;
	}

	// Проверка за 3-дневния срок
	if (travels[travelIndex].startDay - currentDay <= 3) {
		cout << "Пътуването не може да бъде променено - остават по-малко от 3 дни до началото.\n";
		return;
	}

	cout << "\nИзберете какво искате да промените:\n"
		<< "1. Капитан\n"
		<< "2. Брой пътници първа класа\n"
		<< "3. Брой пътници втора класа\n"
		<< "4. Начална дата\n"
		<< "5. Крайна дата\n"
		<< "6. Цена първа класа\n"
		<< "7. Цена втора класа\n"
		<< "0. Отказ\n";

	int choice;
	cin >> choice;

	switch (choice) {
	case 1: {
		string newCaptain;
		cout << "Въведете нов капитан: ";
		cin >> newCaptain;

		if (isShipCaptainAvailable(travels[travelIndex].shipName, newCaptain,
			travels[travelIndex].startDay, travels[travelIndex].endDay,
			travelIndex)) {
			travels[travelIndex].captainName = newCaptain;
			cout << "Капитанът е променен успешно.\n";
		}
		else {
			cout << "Капитанът е зает в този период.\n";
		}
		break;
	}
	case 2: {
		cout << "Въведете нов брой пътници първа класа: ";
		cin >> travels[travelIndex].passangersFirstClass;
		cout << "Броят пътници е променен успешно.\n";
		break;
	}
	case 3: {
		cout << "Въведете нов брой пътници втора класа: ";
		cin >> travels[travelIndex].passangersSecondClass;
		cout << "Броят пътници е променен успешно.\n";
		break;
	}
	case 4: {
		int newStartDay;
		cout << "Въведете нова начална дата: ";
		cin >> newStartDay;

		if (newStartDay >= travels[travelIndex].endDay) {
			cout << "Началната дата не може да бъде след или равна на крайната дата.\n";
		}
		else if (currentDay >= newStartDay) {
			cout << "Началната дата не може да бъде преди или равна на текущата дата.\n";
		}
		else {
			travels[travelIndex].startDay = newStartDay;
			cout << "Началната дата е променена успешно.\n";
		}
		break;
	}
	case 5: {
		int newEndDay;
		cout << "Въведете нова крайна дата: ";
		cin >> newEndDay;

		if (newEndDay <= travels[travelIndex].startDay) {
			cout << "Крайната дата не може да бъде преди или равна на началната дата.\n";
		}
		else {
			travels[travelIndex].endDay = newEndDay;
			cout << "Крайната дата е променена успешно.\n";
		}
		break;
	}
	case 6: {
		cout << "Въведете нова цена за първа класа: ";
		cin >> travels[travelIndex].firstClassPrice;
		cout << "Цената е променена успешно.\n";
		break;
	}
	case 7: {
		cout << "Въведете нова цена за втора класа: ";
		cin >> travels[travelIndex].secondClassPrice;
		cout << "Цената е променена успешно.\n";
		break;
	}
	case 0:
		cout << "Промяната е отказана.\n";
		break;
	default:
		cout << "Невалиден избор.\n";
		break;
	}
}

int main() {
	cout << "Въведете текущ ден от месеца (1-31): ";
	cin >> currentDay;

	travelStatus();
	getInfroFromExternalFile();

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
