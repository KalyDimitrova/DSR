#include <iostream>
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

bool isNumberUnique(int number) {
	for (int i = 0; i < travelCount; i++) {
		if (travels[i].number == number) {
			return false;
		}
	}
	return true;
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

		do {
			cout << "Въведете номер на пътуването: ";
			cin >> newTravel.number;

			if (!isNumberUnique(newTravel.number)) {
				cout << "Този номер вече съществува. Моля въведете уникален номер.\n";
			}
		} while (!isNumberUnique(newTravel.number));

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
	cout << "Пътуванията са сортитани по дестинация!" << endl;
}

//TODO: fill the functions for the files
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

void showFinishedTravelsByDestination() {
	string searchDestination;
	cout << "Въведете дестинация: ";
	cin >> searchDestination;

	Travel finishedTravels[MAX_TRAVELS];
	int finishedTravelCount = 0;

	for (int i = 0; i < travelCount; i++) {
		if (travels[i].destination == searchDestination &&
			travels[i].status == "Отминало") {
			finishedTravels[finishedTravelCount++] = travels[i];
		}
	}

	if (finishedTravelCount == 0) {
		cout << "Няма завършили пътувания до " << searchDestination << endl;
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
}

void showCaptainTravelsByPeriod() {
	string captainName;
	int startDay, endDay;

	cout << "Въведете име на капитан: ";
	cin >> captainName;
	cout << "Въведете начален ден: ";
	cin >> startDay;
	cout << "Въведете краен ден: ";
	cin >> endDay;

	Travel captainTravels[MAX_TRAVELS];
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
}

void modifyTravel() {
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
	cout << "Въведете текущ ден от месеца (1-31): ";
	cin >> currentDay;

	travelStatus();
	getInfroFromExternalFile();

	int choice;

	do {
		menu();
		cin >> choice;
		
		switch (choice){
			case 0:
				giveInfoToExternalFile();
				cout << "Довиждане!" << endl;
				break;
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
			case 8:
				showFinishedTravelsByDestination();
				break;
			case 9:
				showCaptainTravelsByPeriod();
				break;
			case 10:
				modifyTravel();
				break;
			default:
				cout << "Невалиден избор! Моля изберете отново: \n";
				break;
		}
	} while (choice != 0);


	return 0;
}
