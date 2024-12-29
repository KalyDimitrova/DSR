#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <iomanip>

using namespace std;

const int columnNumWidth = 6;
const int columnDestWidth = 11;
const int columnShipWidth = 12;
const int columnCaptainWidth = 16;
const int columnStatusWidth = 21;
const int columnStartWidth = 7;
const int columnEndWidth = 5;
const int TABLE = columnNumWidth + columnDestWidth + columnShipWidth + columnCaptainWidth + columnStatusWidth + columnStartWidth + columnEndWidth + 19;

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

void menu() {
	setlocale(LC_ALL, "");

	cout << "\t\tМЕНЮ:\n"
		<< "0. Изход от програмата\n"
		<< "1. Добавяне на пътуване\n"
		<< "2. Извеждане на всички записани пътувания\n"
		<< "3. Търсене на пътувания за определен интервал от време\n"
		<< "4. Търсене на пътувания до определена дестинация\n"
		<< "5. Сортиране на пътуванията по дестинация\n"
		<< "6. Записване на данните във външен файл\n"
		<< "7. Четене на данни от външен файл\n"
		<< "8. Разширени опции\n"
		<< "Вашият избор: ";
}

void moreMenuOptions() {
	cout << "1. Завършили пътувания до дестинация\n"
		<< "2. Пътувания на капитан за период\n"
		<< "3. Промяна на пътуване\n"
		<< "Вашият избор: ";
}

bool isNumberUnique(int number, int travelCount, Travel travels[MAX_TRAVELS]) {
	for (int i = 0; i < travelCount; i++) {
		if (travels[i].number == number) {
			return false;
		}
	}
	return true;
}

bool isShipCaptainAvailable(int travelCount, Travel travels[MAX_TRAVELS], const string& shipName, const string& captainName, int startDay, int endDay, int currentTravelIndex = -1) {
	for (int i = 0; i < travelCount; i++) {
		if (i == currentTravelIndex) continue;

		bool datesOverlap = !(endDay < travels[i].startDay || startDay > travels[i].endDay);

		if (datesOverlap && (travels[i].shipName == shipName || travels[i].captainName == captainName)) {
			return false;
		}
	}
	return true;
}

int addTravel(int& travelCount, int currentDay, Travel travels[MAX_TRAVELS]) {
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

		do {
			cout << "Въведете номер на пътуването: ";
			cin >> newTravel.number;

			if (!isNumberUnique(newTravel.number, travelCount, travels)) {
				cout << "Този номер вече съществува. Моля въведете уникален номер.\n";
			}
		} while (!isNumberUnique(newTravel.number, travelCount, travels));

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

			if (!isShipCaptainAvailable(travelCount, travels, newTravel.shipName, newTravel.captainName,
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
			newTravel.status = "В очакване\n";
		}
		else if (currentDay > newTravel.endDay) {
			newTravel.status = "Отминало\n";
		}
		else {
			newTravel.status = "В процес на изпълнение\n";
		}

		travels[travelCount] = newTravel;
		travelCount++;
	}
	return 0;
}


void printAllTravels(int travelCount, Travel travels[MAX_TRAVELS]) {
	if (travelCount == 0) {
		cout << "Няма въведени пътувания.\n";
		return;
	}

	cout << setfill('-') << setw(TABLE) << "-" << setfill(' ') << endl;

	cout << setw(columnNumWidth + 5) << right << "Номер" << " | "
		<< setw(columnDestWidth + 10) << left << "Дестинация" << " | "
		<< setw(columnShipWidth + 5) << left << "Кораб" << " | "
		<< setw(columnCaptainWidth + 7) << left << "Капитан" << " | "
		<< setw(columnStatusWidth + 7) << left << "Статус" << " | "
		<< setw(columnStartWidth + 5) << left << "Начало" << " | "
		<< setw(columnEndWidth + 3) << left << "Край" << " |" << endl;

	cout << setfill('-') << setw(TABLE) << "-" << setfill(' ') << endl;

	for (int i = 0; i < travelCount; i++) {
		cout << setw(columnNumWidth) << right << travels[i].number << " | "
			<< setw(columnDestWidth + (travels[i].destination.length() / 2)) << left << travels[i].destination << " | "
			<< setw(columnShipWidth + (travels[i].shipName.length() / 2)) << left << travels[i].shipName << " | "
			<< setw(columnCaptainWidth + (travels[i].captainName.length() / 2)) << left << travels[i].captainName << " | "
			<< setw(columnStatusWidth + (travels[i].status.length() / 2)) << left << travels[i].status << " | "
			<< setw(columnStartWidth - 1) << right << travels[i].startDay << " | "
			<< setw(columnEndWidth - 1) << left
			<< travels[i].endDay << " |" << endl;

	}

	cout << setfill('-') << setw(TABLE) << "-" << setfill(' ') << endl;
}

void searchTravelSpecificPeriod(int travelCount, int currentDay, Travel travels[MAX_TRAVELS]){
	int minDay, maxDay;
	do {
		cout << "Въведете начален ден: ";
		cin >> minDay;
		cout << "Въведете краен ден: ";
		cin >> maxDay;

		if (minDay > maxDay) {
			cout << "Денят на тръгване не може да бъде след деня на връщане!" << endl
				<< "Въведете валидни данни.\n";
		}
	} while (minDay > maxDay);

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

void searchDestinationTravel(int travelCount, int currentDay, Travel travels[MAX_TRAVELS]) {
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

void sortTravelsByDestination(int travelCount, int currentDay, Travel travels[MAX_TRAVELS]) {
	for (int i = 0; i < travelCount - 1; i++) {
		for (int j = 0; j < travelCount - i - 1; j++) {
			if (travels[j].destination > travels[j + 1].destination) {
				Travel temp = travels[j];
				travels[j] = travels[j + 1];
				travels[j + 1] = temp;
			}
		}
	}
	cout << "Пътуванията са сортитани по дестинация!\n" << endl;
}

void giveInfoToExternalFile(int& travelCount, int currentDay, Travel travels[MAX_TRAVELS]) {
	ofstream fileOutput("travels.txt");

	if (!fileOutput.is_open()) {
		cout << "Error: Could not open file for writing!" << endl;
		return;
	}

	fileOutput << travelCount << endl;

	for (int i = 0; i < travelCount; i++) {
		fileOutput << travels[i].number << endl
			<< travels[i].destination << endl
			<< travels[i].shipName << endl
			<< travels[i].captainName << endl
			<< travels[i].startDay << endl
			<< travels[i].endDay << endl
			<< travels[i].firstClassPrice << endl
			<< travels[i].secondClassPrice << endl
			<< travels[i].passangersFirstClass << endl
			<< travels[i].passangersSecondClass << endl
			<< travels[i].status << endl;
	}

	fileOutput.close();
}

void getInfoFromExternalFile(int& travelCount, int currentDay, Travel travels[MAX_TRAVELS]) {
	ifstream fileInput("travels.txt");

	if (!fileInput.is_open()) {
		cout << "Error: Could not open file for reading!" << endl;
		return;
	}

	fileInput >> travelCount;
	fileInput.ignore();

	for (int i = 0; i < travelCount; i++) {
		Travel newTravel;

		fileInput >> newTravel.number;
		fileInput.ignore();

		::getline(fileInput, newTravel.destination);
		::getline(fileInput, newTravel.shipName);
		::getline(fileInput, newTravel.captainName);

		fileInput >> newTravel.startDay;
		fileInput >> newTravel.endDay;
		fileInput >> newTravel.firstClassPrice;
		fileInput >> newTravel.secondClassPrice;
		fileInput >> newTravel.passangersFirstClass;
		fileInput >> newTravel.passangersSecondClass;
		fileInput.ignore();
		::getline(fileInput, newTravel.status);

		travels[i] = newTravel;
	}

	fileInput.close();
}

void travelStatus(int travelCount, int currentDay, Travel travels[MAX_TRAVELS]) {
	for (int i = 0; i < travelCount; i++) {
		if (currentDay < travels[i].startDay) {
			travels[i].status = "В очакване ";
		}
		else if (currentDay > travels[i].endDay) {
			travels[i].status = "Отминало  ";
		}
		else {
			travels[i].status = "В процес на изпълнение";
		}
	}
}

void showFinishedTravelsByDestination(int travelCount, int currentDay, Travel travels[MAX_TRAVELS]) {
	string searchDestination;
	cout << "Въведете дестинация: ";
	cin >> searchDestination;

	// the array is stored in heap
	Travel *finishedTravels = new Travel[MAX_TRAVELS];
	int finishedTravelCount = 0;

	for (int i = 0; i < travelCount; i++) {
		if (travels[i].destination == searchDestination &&
			travels[i].status == "Отминало") {
			finishedTravels[finishedTravelCount++] = travels[i];
		}
	}

	if (finishedTravelCount == 0) {
		cout << "Няма завършили пътувания до " << searchDestination << endl;

		// deleting array from heap
		delete[] finishedTravels;
		return;
	}

	for (int i = 0; i < finishedTravelCount - 1; i++) {
		for (int j = 0; j < finishedTravelCount - i - 1; j++) {
			if (finishedTravels[j].startDay > finishedTravels[j + 1].startDay) {
				Travel temp = finishedTravels[j];
				finishedTravels[j] = finishedTravels[j + 1];
				finishedTravels[j + 1] = temp;
			}
		}
	}

	cout << "\nЗавършили пътувания до " << searchDestination << ":\n";
	for (int i = 0; i < finishedTravelCount; i++) {
		cout << "Пътуване " << finishedTravels[i].number
			<< " - от ден " << finishedTravels[i].startDay
			<< " до ден " << finishedTravels[i].endDay
			<< " с капитан " << finishedTravels[i].captainName << endl;
	}

	// deleting array from heap
	delete[] finishedTravels;
}

void showCaptainTravelsByPeriod(int travelCount, int currentDay, Travel travels[MAX_TRAVELS]) {
	string captainName;
	int startDay, endDay;

	cout << "Въведете име на капитан: ";
	cin >> captainName;
	cout << "Въведете начален ден: ";
	cin >> startDay;
	cout << "Въведете краен ден: ";
	cin >> endDay;

	//the array is stored in heap
	Travel *captainTravels = new Travel[MAX_TRAVELS];
	int captainTravelCount = 0;

	for (int i = 0; i < travelCount; i++) {
		if (travels[i].captainName == captainName &&
			travels[i].startDay >= startDay &&
			travels[i].endDay <= endDay) {
			captainTravels[captainTravelCount++] = travels[i];
		}
	}

	if (captainTravelCount == 0) {
		cout << "Няма намерени пътувания за капитан " << captainName
			<< " в периода " << startDay << "-" << endDay << endl;

		// deleting array from heap
		delete[] captainTravels;
		return;
	}

	for (int i = 0; i < captainTravelCount - 1; i++) {
		for (int j = 0; j < captainTravelCount - i - 1; j++) {
			if (captainTravels[j].destination < captainTravels[j + 1].destination) {
				Travel temp = captainTravels[j];
				captainTravels[j] = captainTravels[j + 1];
				captainTravels[j + 1] = temp;
			}
		}
	}

	cout << "\nПътувания на капитан " << captainName
		<< " в периода " << startDay << "-" << endDay << ":\n";
	for (int i = 0; i < captainTravelCount; i++) {
		cout << "Пътуване " << captainTravels[i].number
			<< " до " << captainTravels[i].destination
			<< " - от ден " << captainTravels[i].startDay
			<< " до ден " << captainTravels[i].endDay << endl;
	}

	// deleting array from heap
	delete[] captainTravels;
}

void modifyTravel(int travelCount, int currentDay, Travel travels[MAX_TRAVELS]) {
	int travelNumber;
	cout << "Въведете номер на пътуването за промяна: ";
	cin >> travelNumber;

	int travelIndex = -1;
	for (int i = 0; i < travelCount; i++) {
		if (travels[i].number == travelNumber) {
			travelIndex = i;
			break;
		}
	}

	if (travelIndex == -1) {
		cout << "Пътуване с този номер не е намерено.\n";
		return;
	}

	if (travels[travelIndex].status != "В очакване") {
		cout << "Пътуването не може да бъде променено - "
			<< (travels[travelIndex].status == "Отминало" ? "вече е отминало" : "е в процес на изпълнение")
			<< endl;
		return;
	}

	if (travels[travelIndex].startDay - currentDay <= 3) {
		cout << "Пътуването не може да бъде променено - остават по-малко от 3 дни до началото.\n";
		return;
	}

	cout << "\nИзберете какво искате да промените:\n"
		<< "0. Отказ\n"
		<< "1. Капитан\n"
		<< "2. Брой пътници първа класа\n"
		<< "3. Брой пътници втора класа\n"
		<< "4. Начална дата\n"
		<< "5. Крайна дата\n"
		<< "6. Цена първа класа\n"
		<< "7. Цена втора класа\n";

	int choice;
	cin >> choice;

	string confirm;
	cout << "Сигурни ли сте, че искате да направите тази промяна? (да/не): ";
	cin >> confirm;
	if (confirm != "да") {
		cout << "Промяната е отказана.\n";
		return;
	}

	switch (choice) {
		case 0:
			cout << "Промяната е отказана.\n";
			break;
		case 1: {
			string newCaptain;
			cout << "Въведете нов капитан: ";
			cin >> newCaptain;

			cout << "Сигурни ли сте, че искате да смените капитана от '"
				<< travels[travelIndex].captainName << "' на '" << newCaptain << "'? (да/не): ";
			cin >> confirm;
			if (confirm != "да") {
				cout << "Промяната е отказана.\n";
				break;
			}

			if (isShipCaptainAvailable(travelCount, travels, travels[travelIndex].shipName, newCaptain,
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
			int newPassengers;
			cout << "Въведете нов брой пътници първа класа: ";
			cin >> newPassengers;

			cout << "Сигурни ли сте, че искате да промените броя пътници от "
				<< travels[travelIndex].passangersFirstClass << " на " << newPassengers << "? (да/не): ";
			cin >> confirm;
			if (confirm != "да") {
				cout << "Промяната е отказана.\n";
				break;
			}

			travels[travelIndex].passangersFirstClass = newPassengers;
			cout << "Броят пътници е променен успешно.\n";
			break;
		}
		case 3: {
			int newPassengers;
			cout << "Въведете нов брой пътници втора класа: ";
			cin >> newPassengers;

			cout << "Сигурни ли сте, че искате да промените броя пътници от "
				<< travels[travelIndex].passangersSecondClass << " на " << newPassengers << "? (да/не): ";
			cin >> confirm;
			if (confirm != "да") {
				cout << "Промяната е отказана.\n";
				break;
			}

			travels[travelIndex].passangersSecondClass = newPassengers;
			cout << "Броят пътници е променен успешно.\n";
			break;
		}
		case 4: {
			int newStartDay;
			cout << "Въведете нова начална дата: ";
			cin >> newStartDay;

			cout << "Сигурни ли сте, че искате да промените началната дата от "
				<< travels[travelIndex].startDay << " на " << newStartDay << "? (да/не): ";
			cin >> confirm;
			if (confirm != "да") {
				cout << "Промяната е отказана.\n";
				break;
			}

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

			cout << "Сигурни ли сте, че искате да промените крайната дата от "
				<< travels[travelIndex].endDay << " на " << newEndDay << "? (да/не): ";
			cin >> confirm;
			if (confirm != "да") {
				cout << "Промяната е отказана.\n";
				break;
			}

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
			double newPrice;
			cout << "Въведете нова цена за първа класа: ";
			cin >> newPrice;

			cout << "Сигурни ли сте, че искате да промените цената от "
				<< travels[travelIndex].firstClassPrice << " на " << newPrice << "? (да/не): ";
			cin >> confirm;
			if (confirm != "да") {
				cout << "Промяната е отказана.\n";
				break;
			}

			travels[travelIndex].firstClassPrice = newPrice;
			cout << "Цената е променена успешно.\n";
			break;
		}
		case 7: {
			double newPrice;
			cout << "Въведете нова цена за втора класа: ";
			cin >> newPrice;

			cout << "Сигурни ли сте, че искате да промените цената от "
				<< travels[travelIndex].secondClassPrice << " на " << newPrice << "? (да/не): ";
			cin >> confirm;
			if (confirm != "да") {
				cout << "Промяната е отказана.\n";
				break;
			}

			travels[travelIndex].secondClassPrice = newPrice;
			cout << "Цената е променена успешно.\n";
			break;
		}
		default:
			cout << "Невалиден избор.\n";
			break;
		}
}

int main() {
	int travelCount = 0;
	int currentDay;
	// stored array in heap instead of stack
	Travel *travels = new Travel[MAX_TRAVELS];

	cout << "Въведете текущ ден от месеца (1-31): ";
	cin >> currentDay;

	getInfoFromExternalFile(travelCount, currentDay, travels);
	travelStatus(travelCount, currentDay, travels);

	int choice;

	do {
		menu();
		cin >> choice;
		
		switch (choice){
			case 0:
				giveInfoToExternalFile(travelCount, currentDay, travels);
				cout << "Довиждане!" << endl;
				break;
			case 1:
				addTravel(travelCount, currentDay, travels);
				break;
			case 2:
				printAllTravels(travelCount, travels);
				break;
			case 3:
				searchTravelSpecificPeriod(travelCount, currentDay, travels);
				break;
			case 4:
				searchDestinationTravel(travelCount, currentDay, travels);
				break;
			case 5:
				sortTravelsByDestination(travelCount, currentDay, travels);
				break;
			case 6:
				giveInfoToExternalFile(travelCount, currentDay, travels);
				cout << "Данните са записани успешно!\n";
				break;
			case 7:
				getInfoFromExternalFile(travelCount, currentDay, travels);
				break;
			case 8:
				int choice2;

				moreMenuOptions();

				cin >> choice2;
				switch (choice2) {
					case 1:
						showFinishedTravelsByDestination(travelCount, currentDay, travels);
						break;
					case 2:
						showCaptainTravelsByPeriod(travelCount, currentDay, travels);
						break;
					case 3:
						modifyTravel(travelCount, currentDay, travels);
						break;
				}
				break;
			default:
				cout << "Невалиден избор! Моля изберете отново: \n";
				break;
		}
	} while (choice != 0);

	// deleting array from heap
	delete[] travels;
	return 0;
}
