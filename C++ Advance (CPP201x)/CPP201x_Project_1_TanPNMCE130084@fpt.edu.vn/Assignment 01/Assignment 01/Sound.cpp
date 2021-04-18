#include "Sound.h"

// Constructor without parameter
Sound::Sound() : Setting() {}

// Constructor with parameter
Sound::Sound(int media_lv, int call_lv, int navi_lv, int notification_lv, string carName, string personalKey,
	string email_, int odo_, int serviceRemind) : Setting() {

	this->car_name = carName;
	this->personal_key = personalKey;
	this->email = email_;
	this->odo = odo_;
	this->service_remind = serviceRemind;
	this->media_level = media_lv;
	this->call_level = call_lv;
	this->navi_level = navi_lv;
	this->notification_level = notification_lv;
}

Sound::~Sound() {}

/*
* The function to input data of Sound
*/
Sound Sound::nhapThongTin(Setting setting) {
	//declare variables temp
	string media_lv, call_lv, navi_lv, notification_lv;
	bool error = false;
	//declare string regex
	regex numberRegex("[0-9]+");

#pragma region Input media level
	do {
		error = false;
		cout << "Media level: ";
		cin >> media_lv;
		//check input data
		if (!regex_match(media_lv, numberRegex)) {	//if is not a digit
			cerr << "Media level must be a digit!";
			error = true;
		}
		else if (stoi(media_lv) < 0) {	//if is not a positive number
			cerr << "Media level must be a positive number!";
			error = true;
		}
	} while (error == true);
	this->media_level = stoi(media_lv);
#pragma endregion

#pragma region Input call level
	do {
		error = false;
		cout << "Call level: ";
		cin >> call_lv;
		//check input data
		if (!regex_match(call_lv, numberRegex)) {	//if is not a digit
			cerr << "Call level must be a digit!";
			error = true;
		}
		else if (stoi(call_lv) < 0) {	//if is not a positive number
			cerr << "Call level must be a positive number!";
			error = true;
		}
	} while (error == true);
	this->call_level = stoi(call_lv);
#pragma endregion

#pragma region Input navigator level

	do {
		error = false;
		cout << "Navigator level: ";
		cin >> navi_lv;
		//check input data
		if (!regex_match(navi_lv, numberRegex)) {	//if is not a digit
			cerr << "Navigator level must be a digit!";
			error = true;
		}
		else if (stoi(navi_lv) < 0) {	//if is not a positive number
			cerr << "Navigator level must be a positive number!";
			error = true;
		}
	} while (error == true);
	this->navi_level = stoi(navi_lv);
#pragma endregion

#pragma region Input notification level

	do {
		error = false;
		cout << "Notification level: ";
		cin >> notification_lv;
		//check input data
		if (!regex_match(notification_lv, numberRegex)) {	//if is not a digit
			cerr << "Notification level must be a digit!";
			error = true;
		}
		else if (stoi(notification_lv) < 0) {	//if is not a positive number
			cerr << "Notification level must be a positive number!";
			error = true;
		}
	} while (error == true);
	this->notification_level = stoi(notification_lv);
#pragma endregion

	return Sound(this->media_level, this->call_level, this->navi_level, this->notification_level,
		setting.getCarName(), setting.getPersonalKey(), setting.getEmail(), setting.getODO(), setting.getServiceRemind());
}

/*
* The function to insert empty Sound
*/
Sound Sound::insertEmptySound(Setting setting) {
	return Sound(0, 0, 0, 0, setting.getCarName(), setting.getPersonalKey(), setting.getEmail(), setting.getODO(), setting.getServiceRemind());
}

#pragma region Getter and Setter of Sound

int Sound::get_media_level() {
	return this->media_level;
}

int Sound::get_call_level() {
	return this->call_level;
}

int Sound::get_navi_level() {
	return this->navi_level;
}

int Sound::get_notification_level() {
	return this->notification_level;
}

void Sound::set_media_level(int data) {
	this->media_level = data;
}

void Sound::set_call_level(int data) {
	this->call_level = data;
}

void Sound::set_navi_level(int data) {
	this->navi_level = data;
}

void Sound::set_notification_level(int data) {
	this->notification_level = data;
}
#pragma endregion