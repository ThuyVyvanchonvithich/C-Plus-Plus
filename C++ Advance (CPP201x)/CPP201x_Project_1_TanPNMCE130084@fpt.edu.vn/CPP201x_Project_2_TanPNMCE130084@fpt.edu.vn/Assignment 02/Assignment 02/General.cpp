#include "General.h"
#include "CommonInfo.h"

extern vector<CommonInfo> timezoneList;
extern vector<CommonInfo> languageList;

// Constructor without parameter
General::General()
{
	this->timeZone = "23";	// (GMT+07:00) /  Bangkok, Hanoi, Jakarta
	this->language = "15";	// Vietnamese
}

// Constructor with parameter
General::General(string carName, string personalKey, string e_mail, int myodo, int remind, string timezone, string language) {
	this->car_name = carName;
	this->personal_key = personalKey;
	this->email = e_mail;
	this->odo = myodo;
	this->service_remind = remind;
	this->timeZone = timezone;
	this->language = language;
}

// Destructor
General::~General() {}

// Constructor with parameter
General General::nhapThongTin(Setting setting) {
	//declare string regex
	regex isDigit("[0-9]+");
	bool error = false;

	//Input timezone
	cout << "Please select time zone" << endl;

	// Show list Timezone
	for (int i = 0; i < timezoneList.size(); ++i) {
		string convert_number = to_string(i) + ":";
		cout << left << setw(7) << convert_number << setw(13) << timezoneList[i].getNumber() << timezoneList[i].getName() << endl;
	}
	
	do
	{
		error = false;
		cout << "Please select your timezone: ";
		cin >> timeZone;
		// check if user enter is number
		if (!regex_match(timeZone, isDigit))
		{
			cout << "Timezone must be a number!" << endl;
			error = true;
		}
		else {
			// check if time zone is from 0 to 30
			if (0 > stoi(timeZone) || stoi(timeZone) > 31)
			{
				cout << "Timezone must between 0 and 31!" << endl;
				error = true;
			}
			else {
				break;
			}
		}
	} while (error == true);
	cout << timezoneList[stoi(timeZone)].getName() << endl;
	system("pause");

	//Input language
	system("cls");
	cout << "Please select your language" << endl;
	// Show list Language
	for (int i = 0; i < languageList.size(); ++i) {
		cout << left << setw(4) << i << "  " << languageList[i].getName() << endl;
	}
	
	do
	{
		cout << "Please select: ";
		cin >> language;
		// check if user enter is number
		if (!regex_match(timeZone, isDigit))
		{
			cout << "Language must be a number!" << endl;
			error = true;
		}
		else {
			// check if user enter is from 0 to 29
			if (0 > stoi(language) || stoi(language) > 29)
			{
				cout << "Language must between 0 and 29!" << endl;
				error = true;
			}
			else {
				break;
			}
		}
	} while (error == true);
	cout << languageList[stoi(language)].getName() << endl;
	system("pause");

	return General(setting.getCarName(), setting.getPersonalKey(), setting.getEmail(), setting.getODO(), setting.getServiceRemind(), this->timeZone, this->language);
}

/*
* The function to update data of General
*/
void General::updateGeneral(string timeZone, string language) {
	
	this->timeZone = timeZone;
	this->language = language;
}

/*
* The function to format type of General data to write to file
*/
string General::formatTypeGeneral() {
	return get_timeZone() + "," + get_language();
}

#pragma region Getter and Setter of General
string General::get_language() {
	return this->language;
}

string General::get_timeZone() {
	return this->timeZone;
}

void General::set_timeZone(string data) {
	this->timeZone = data;
}

// Set language function
void General::set_language(string data) {
	this->language = data;
}
#pragma endregion
