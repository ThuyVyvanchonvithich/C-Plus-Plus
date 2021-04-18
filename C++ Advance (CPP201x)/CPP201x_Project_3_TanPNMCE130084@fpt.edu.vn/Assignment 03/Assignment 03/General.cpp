#include "General.h"
#include "CommonInfo.h"

extern vector<CommonInfo> timezoneList;
extern vector<CommonInfo> languageList;

// Constructor without parameter
General::General()
{
	this->timeZone = "  Bangkok, Hanoi, Jakarta";	// (GMT+07:00) /  Bangkok, Hanoi, Jakarta
	this->language = "Vietnamese";	// Vietnamese
}

// Constructor with parameter
General::General(Setting setting)
{
	this->car_name = setting.getCarName();
	this->personal_key = setting.getPersonalKey();
	this->email = setting.getEmail();
	this->odo = setting.getODO();
	this->service_remind = setting.getServiceRemind();
	this->timeZone = "  Bangkok, Hanoi, Jakarta";	// (GMT+07:00) /  Bangkok, Hanoi, Jakarta
	this->language = "Vietnamese";	// Vietnamese
}

// Destructor
General::~General() {}

/*
* The function to input data of General
*/
void General::nhapThongTin(Setting setting) {
	//declare string regex
	regex isDigit("[0-9]+");
	string user_choice_timezone = "";
	string user_choice_language = "";
	bool error = false;

	// Input timezone
	cout << "Please select a timezone" << endl;

	// Show list Timezone
	for (int i = 0; i < timezoneList.size(); ++i) {
		string convert_number = to_string(i) + ":";
		cout << left << setw(7) << convert_number << setw(13) << timezoneList[i].getNumber() << timezoneList[i].getName() << endl;
	}
	
	do
	{
		error = false;
		cout << "Please select: ";
		cin >> user_choice_timezone;
		// check if user enter is number
		if (!regex_match(user_choice_timezone, isDigit))
		{
			cout << "Timezone must be a number!" << endl;
			error = true;
		}
		else {
			// check if time zone is from 0 to 30
			if (0 > stoi(user_choice_timezone) || stoi(user_choice_timezone) > 31)
			{
				cout << "Timezone must between 0 and 31!" << endl;
				error = true;
			}
			else {
				break;
			}
		}
	} while (error == true);
	this->timeZone = timezoneList[stoi(user_choice_timezone)].getName();
	cout << this->timeZone << endl;
	system("pause");

	//Input language
	system("cls");
	cout << "Please select a language" << endl;
	// Show list Language
	for (int i = 0; i < languageList.size(); ++i) {
		cout << left << setw(4) << i << "  " << languageList[i].getName() << endl;
	}
	
	do
	{
		cout << "Please select: ";
		cin >> user_choice_language;
		// check if user enter is number
		if (!regex_match(user_choice_language, isDigit))
		{
			cout << "Language must be a number!" << endl;
			error = true;
		}
		else {
			// check if user enter is from 0 to 29
			if (0 > stoi(user_choice_language) || stoi(user_choice_language) > 29)
			{
				cout << "Language must between 0 and 29!" << endl;
				error = true;
			}
			else {
				break;
			}
		}
	} while (error == true);
	this->language = languageList[stoi(user_choice_language)].getName();
	cout << this->language << endl;
	system("pause");

	//update data Setting in General
	updateGeneral(setting);
}

/*
* The function to update full data of General
*/
void General::updateGeneral(Setting setting, string timeZone, string language) {

	setCarName(setting.getCarName());
	setEmail(setting.getEmail());
	setPersonalKey(setting.getPersonalKey());
	setODO(setting.getODO());
	setServiceRemind(setting.getServiceRemind());
	this->timeZone = timeZone;
	this->language = language;
}

/*
* The function to update setting data of General
*/
void General::updateGeneral(Setting setting) {
	
	setCarName(setting.getCarName());
	setEmail(setting.getEmail());
	setPersonalKey(setting.getPersonalKey());
	setODO(setting.getODO());
	setServiceRemind(setting.getServiceRemind());
}

/*
* The function to format type of General data to write to file
*/
string General::formatTypeGeneral() {
	return get_timeZone() + ";" + get_language();
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
