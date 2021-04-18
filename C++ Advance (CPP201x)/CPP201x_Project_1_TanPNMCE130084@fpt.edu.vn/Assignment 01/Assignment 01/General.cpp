#include "General.h"
#include "CommonInfo.h"

// Constructor
General::General(string language, string timeZone)
{
	// Your code
	set_timeZone(timeZone);
	set_language(language);

}

// Constructor
General::General(string personalKey, string timeZone, string language)
{
	// Your code
	personal_key = personalKey;
	set_timeZone(timeZone);
	set_language(language);

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

// Constructor without parameter
General::General() {}


// Destructor
General::~General() {}

// Constructor with parameter
General General::nhapThongTin(Setting setting, string timeZone, string language) {
	// Your code
	return General(setting.getCarName(), setting.getPersonalKey(), setting.getEmail(), setting.getODO(), setting.getServiceRemind(), timeZone, language);
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