#include "Display.h"

// Constructor without parameter
Display::Display() {
	this->light_level = 0;
	this->screen_light_level = 0;
	this->taplo_light_level = 0;
}

// Constructor with parameter
Display::Display(int light_lv, int screen_light_lv, int taplo_light_lv, string carName, string personalKey,
	string email_, int odo_, int serviceRemind) {

	this->car_name = carName;
	this->personal_key = personalKey;
	this->email = email_;
	this->odo = odo_;
	this->service_remind = serviceRemind;
	this->light_level = light_lv;
	this->screen_light_level = screen_light_lv;
	this->taplo_light_level = taplo_light_lv;
}

// Destructor
Display::~Display() {}

/*
* The function to input data of Display
*/
Display Display::nhapThongTin(Setting setting) {

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

	return Display(this->light_level, this->screen_light_level, this->taplo_light_level,
		setting.getCarName(), setting.getPersonalKey(), setting.getEmail(), setting.getODO(), setting.getServiceRemind());
}

/*
* The function to update data of Display
*/
void Display::updateDisplay(int light_lv, int screen_light_lv, int taplo_light_lv) {
	
	this->light_level = light_lv;
	this->screen_light_level = screen_light_lv;
	this->taplo_light_level = taplo_light_lv;
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