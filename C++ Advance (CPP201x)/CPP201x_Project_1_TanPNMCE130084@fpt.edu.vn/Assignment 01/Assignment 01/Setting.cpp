#include "Setting.h"

Setting::Setting(){}

Setting::Setting(string carName, string personalKey, string email, int odo, int remind)
{
	setCarName(carName);
	setPersonalKey(personalKey);
	setEmail(email);
	setODO(odo);
	setServiceRemind(remind);
}

Setting::~Setting() {}

#pragma region MyRegion

string Setting::getCarName() {
	string name = car_name;
	return name;
}

void Setting::setCarName(string carName) {
	this->car_name = carName;
}
string Setting::getPersonalKey() {
	string s = personal_key;
	return s;
}
void Setting::setPersonalKey(string pk) {
	this->personal_key = pk;
}

string Setting::getEmail()
{
	return email;
}

// Set email function
void Setting::setEmail(string email) {
	this->email = email;
}

int Setting::getODO() {
	return odo;
}
void Setting::setODO(int ODO) {
	this->odo = ODO;
}
int Setting::getServiceRemind() {
	return service_remind;
}
void Setting::setServiceRemind(int serviceRemind) {
	this->service_remind = serviceRemind;
}
#pragma endregion

Setting Setting::nhapThongTin(string personalKey, bool keyExisted) {
	string user_input;
	bool error = false;

	//Regular expression
	regex isNumber("[0-9]+$");
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
	
	cout << "Key number: " << personalKey << endl;

	//input ODO
	do {
		error = false;
		cout << "ODO number: ";
		cin >> user_input;
		if (!regex_match(user_input, isNumber))
		{
			cout << "ODO number must be integer" << endl;
			error = true;
		}
	} while (error == true);
	this->odo = stoi(user_input);
	cin.ignore(256, '\n');

	//input Remind Service
	do {
		cout << "Remind service (km): ";
		cin >> user_input;
		if (!regex_match(user_input, isNumber))
		{
			cout << "SERVICE REMIND must be integer" << endl;
			error = true;
		}
	} while (error == true);
	this->service_remind = stoi(user_input);
	cin.ignore(256, '\n');

	//check personal key is existed or not
	if (keyExisted == true) {
		cout << "This car already existed, data will be overriten" << endl;
	}
	else
	{
		cout << "This is car, data will be appended to your list" << endl;
	}

	return Setting(car_name, personalKey, email, odo, service_remind);
}