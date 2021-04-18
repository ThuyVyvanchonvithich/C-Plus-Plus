#include "Display.h"

// Constructor without parameter
Display::Display() {
	
	this->light_level = 0;
	this->screen_light_level = 0;
	this->taplo_light_level = 0;
}

// Constructor with parameter
Display::Display(Setting setting) {
	this->car_name = setting.getCarName();
	this->personal_key = setting.getPersonalKey();
	this->email = setting.getEmail();
	this->odo = setting.getODO();
	this->service_remind = setting.getServiceRemind();
	this->light_level = 0;
	this->screen_light_level = 0;
	this->taplo_light_level = 0;
}

// Destructor
Display::~Display() {}

/*
* The function to input data of Display
*/
void Display::nhapThongTin(Setting setting) {

	//declare variables temp
	string light_lv, screen_light_lv, taplo_light_lv;
	bool error = false;
	//declare string regex
	regex isDigit("[0-9]+");


#pragma region Input light level

	do {
		error = false;
		cout << "Light level: ";
		cin >> light_lv;
		//check input data
		if (!regex_match(light_lv, isDigit)) {	//if is not a digit
			cerr << "Light level must be a digit!";
			error = true;
		}
		else if (stoi(light_lv) < 0) {	//if is not a positive number
			cerr << "Light level must be a positive number!";
			error = true;
		}
	} while (error == true);
	this->light_level = stoi(light_lv);
#pragma endregion

#pragma region Input screen light level
	do {
		error = false;
		cout << "Screen light level: ";
		cin >> screen_light_lv;
		//check input data
		if (!regex_match(screen_light_lv, isDigit)) {	//if is not a digit
			cerr << "Screen light level must be a digit!";
			error = true;
		}
		else if (stoi(screen_light_lv) < 0) {	//if is not a positive number
			cerr << "Screen light level must be a positive number!";
			error = true;
		}
	} while (error == true);
	this->screen_light_level = stoi(screen_light_lv);
#pragma endregion

#pragma region Input Taplo light level

	do {
		error = false;
		cout << "Taplo light level: ";
		cin >> taplo_light_lv;
		//check input data
		if (!regex_match(taplo_light_lv, isDigit)) {	//if is not a digit
			cerr << "Taplo light level must be a digit!";
			error = true;
		}
		else if (stoi(taplo_light_lv) < 0) {	//if is not a positive number
			cerr << "Taplo light level must be a positive number!";
			error = true;
		}
	} while (error == true);
	this->taplo_light_level = stoi(taplo_light_lv);
#pragma endregion

	//update data Setting in Display
	updateDisplay(setting);
}

void Display::xuatThongTin() {
	cout << setw(20) << left << getCarName()
		<< setw(25) << left << getEmail()
		<< setw(15) << left << getPersonalKey()
		<< setw(15) << left << getODO()
		<< setw(20) << left << getServiceRemind()
		<< setw(15) << left << this->light_level
		<< setw(20) << left << this->screen_light_level
		<< setw(15) << left << this->taplo_light_level << endl;
}

/*
* The function to update full data of Display
*/
void Display::updateDisplay(Setting setting, int light_lv, int screen_light_lv, int taplo_light_lv) {
	
	setCarName(setting.getCarName());
	setEmail(setting.getEmail());
	setPersonalKey(setting.getPersonalKey());
	setODO(setting.getODO());
	setServiceRemind(setting.getServiceRemind());
	this->light_level = light_lv;
	this->screen_light_level = screen_light_lv;
	this->taplo_light_level = taplo_light_lv;
}

/*
* The function to update setting data of Display
*/
void Display::updateDisplay(Setting setting) {

	setCarName(setting.getCarName());
	setEmail(setting.getEmail());
	setPersonalKey(setting.getPersonalKey());
	setODO(setting.getODO());
	setServiceRemind(setting.getServiceRemind());
}

/*
* The function to format type of Display data to write to file
*/
string Display::formatTypeDisplay() {
	return to_string(get_light_level()) + "," + to_string(get_screen_light_level()) + "," + to_string(get_taplo_light_level());
}

#pragma region Getter and Setter of Display

int Display::get_light_level() {
	return this->light_level;
}

int Display::get_screen_light_level() {
	return this->screen_light_level;
}

int Display::get_taplo_light_level() {
	return this->taplo_light_level;
}

void Display::set_light_level(int data) {
	this->light_level = data;
}

void Display::set_screen_light_level(int data) {
	this->screen_light_level = data;
}

void Display::set_taplo_light_level(int data) {
	this->taplo_light_level = data;
}
#pragma endregion