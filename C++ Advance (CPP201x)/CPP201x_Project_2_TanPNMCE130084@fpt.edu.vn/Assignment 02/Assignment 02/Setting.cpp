#include "Setting.h"

Setting::Setting() {}

Setting::Setting(string carName, string personalKey, string email, int odo, int remind)
{
	this->car_name = carName;
	this->personal_key = personalKey;
	this->email = email;
	this->odo = odo;
	this->service_remind = remind;
}

Setting::~Setting() {}

#pragma region Getter & Setter

string Setting::getCarName() {
	return this->car_name;
}

void Setting::setCarName(string data) {
	this->car_name = data;
}
string Setting::getPersonalKey() {
	return this->personal_key;
}
void Setting::setPersonalKey(string data) {
	this->personal_key = data;
}

string Setting::getEmail()
{
	return this->email;
}

// Set email function
void Setting::setEmail(string data) {
	this->email = data;
}

int Setting::getODO() {
	return odo;
}
void Setting::setODO(int data) {
	this->odo = data;
}
int Setting::getServiceRemind() {
	return service_remind;
}
void Setting::setServiceRemind(int serviceRemind) {
	this->service_remind = serviceRemind;
}
#pragma endregion

Setting Setting::nhapThongTin() {
	string user_input;
	bool error = false;

	//Regular expression
	regex isDigit("[0-9]+$");
	regex isChar("[a-zA-Z]+");
	regex isMail("\\w{1,}@[a-z]+\\.[\\.a-z]+");

	//input data
	//input owner name
	do {
		error = false;
		cout << "Owner name: ";
		cin >> this->car_name;
		if (!regex_match(car_name, isChar))
		{
			cout << "CAR NAME must be a string without number" << endl;
			error = true;
		}
		cin.ignore(256, '\n');
	} while (error == true);

	//input email
	do {
		error = false;
		cout << "Email: ";
		cin >> this->email;
		if (!regex_match(email, isMail))
		{
			cout << "Email must be a string with \"@example.com\" at end" << endl;
			error = true;
		}
		cin.ignore(256, '\n');
	} while (error == true);

	//cout << "Key number: " << personalKey << endl;
	//input personal key
	do {
		error = false;
		cout << "Key number: ";
		cin >> this->personal_key;
		//Check key is numberic
		if (!regex_match(personal_key, isDigit))
		{
			//system("cls");
			cout << "PERSONAL KEY must be a digit! \n" << endl;
			error = true;
			cin.ignore(256, '\n');
		}

		//Check key is 8 digitals
		if (personal_key.length() != 8)
		{
			system("cls");
			cout << "PERSONAL KEY must have 8 digitals! \n" << endl;
			error = true;
			cin.ignore(256, '\n');
		}
	} while (error == true);

	//input ODO
	do {
		error = false;
		cout << "ODO number: ";
		cin >> user_input;
		if (!regex_match(user_input, isDigit))
		{
			cout << "ODO number must be integer" << endl;
			error = true;
		}
	} while (error == true);
	this->odo = stoi(user_input);
	cin.ignore(256, '\n');

	//input Remind Service
	do {
		error = false;
		cout << "Remind service (km): ";
		cin >> user_input;
		if (!regex_match(user_input, isDigit))
		{
			cout << "SERVICE REMIND must be integer" << endl;
			error = true;
		}
	} while (error == true);
	this->service_remind = stoi(user_input);
	cin.ignore(256, '\n');

	return Setting(car_name, personal_key, email, odo, service_remind);
}

/*
* The function to update data of Setting
*/
void Setting::updateSetting(Setting setting) {

	this->car_name = setting.getCarName();
	this->personal_key = setting.getPersonalKey();
	this->email = setting.getEmail();
	this->odo = setting.getODO();
	this->service_remind = setting.getServiceRemind();
}

/*
* The function format type of Setting data to write to file
*/
string Setting::formatTypeSetting() {
	return getCarName() + "," + getEmail() + "," + getPersonalKey() + "," + std::to_string(getODO()) + "," + std::to_string(getServiceRemind());
}