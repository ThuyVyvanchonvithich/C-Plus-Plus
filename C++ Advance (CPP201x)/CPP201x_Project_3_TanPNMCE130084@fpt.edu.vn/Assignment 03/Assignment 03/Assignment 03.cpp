#include <iostream>
#include "General.h"
#include "Display.h"
#include "Sound.h"
#include "CommonInfo.h"	
#include <fstream>
#include <regex>

// Ban can tao ra 3 list luu tru du lieu cho Display, Sound, General voi class Template List
//declare List contain object
vector<Display*> listDisplay;
vector<Sound*> listSound;
vector<General*> listGeneral;
vector<Setting*> listSetting;

//declare object
Display *display = new Display();
Sound *sound = new Sound();
General *general = new General();
Setting *setting = new Setting();

//declare global variables
int displayCount, soundCount, generalCount = 0;
int settingCount = 0;
int position = 0;	// The variables to store index of exist element 

//declare vector to store Timezone and Language
vector<CommonInfo> timezoneList;
vector<CommonInfo> languageList;

/// Forward declaration
void NhapThongTinCaiDat();
void XuatThongTinCaiDat();

void XuatThongTinCaiDat_Sound();
void XuatThongTinCaiDat_General();
void XuatThongTinCaiDat_Display();
void XuatThongTatCaTinCaiDat();

void NhapThongTinCaiDat_Sound();
void NhapThongTinCaiDat_General();
void NhapThongTinCaiDat_Display();

void downloadTimeZone();
void downloadLanguage();

void writeDataToFile();
void readDataFromFile();
void handleDataInFile(string data);
bool isKeyExisted(string key);

string getStringTimezone(string timezone);

// Sort data
bool comparatorDisplay(Display* display1, Display* display2);
bool comparatorSound(Sound* display1, Sound* display2);
bool comparatorGeneral(General* display1, General* display2);
bool comparatorTimezone(CommonInfo c1, CommonInfo c2);
bool comparatorLanguage(CommonInfo c1, CommonInfo c2);

void menu();

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int main(int argc, char** argv) {

	downloadLanguage();
	downloadTimeZone();
	readDataFromFile();
	menu();

	return 0;
}

/*
* The function to run menu
*/
void menu() {
	int selection;
	bool error = false;
	regex isNumber("^[0-3]");
	string user_choice;

	do {
		error = false;
		system("cls");
		cout << "----- SELECT MENU -----" << endl;
		cout << "1. Input setting information" << endl;
		cout << "2. Print setting information" << endl;
		cout << "3. Exit" << endl;
		cout << "Your selection: ";
		cin >> user_choice;
		if (!regex_match(user_choice, isNumber))
		{
			cout << "Please enter a number from 1 to 3!" << endl;
			system("pause");
			cin.ignore(256, '\n');
			error = true;
		}
	} while (error == true);

	selection = stoi(user_choice);
	system("cls");
	switch (selection)
	{
	case 1:
		NhapThongTinCaiDat();
		break;
	case 2:
		XuatThongTinCaiDat();
		break;
	case 3:
		writeDataToFile();
		cout << "THANKS FOR USE MY PROGRAM!!!" << endl;
		exit(0);

	}
}

/*
* The function to handle menu input setting information
*/
void NhapThongTinCaiDat() {
	//declare local variables and string regex
	int selection;
	bool error = false;
	regex isDigit("^[0-3]");
	string user_choice;

	//Over and over again constantly until user choice Exit
	do {

		do {
			error = false;
			system("cls");

			//display menu
			cout << " --- SELECT MENU --- " << endl;
			cout << " 1. Display setting" << endl;
			cout << " 2. Sound setting" << endl;
			cout << " 3. General setting" << endl;
			cout << " 0. Exit" << endl;
			cout << " Your selection: ";
			cin >> user_choice;

			//catch the case user input is not a number and from 0 to 3
			if (!regex_match(user_choice, isDigit))
			{
				cout << "Please enter a number from 0 to 3!" << endl;
				system("pause");
				cin.ignore(256, '\n');
				error = true;
			}
		} while (error == true);

		selection = stoi(user_choice);	//cast string to int
		system("cls");

		//Handle the cases user choose
		switch (selection) {

		case 1:		//case 1 input thong tin Display
			cout << " --- Ban nhap thong tin Display --- " << endl;
			NhapThongTinCaiDat_Display();
			break;

		case 2:		//case 2 input thong tin Sound
			cout << " --- Ban nhap thong tin Sound --- " << endl;
			NhapThongTinCaiDat_Sound();
			break;

		case 3:		//case 3 input thong tin General
			cout << " --- Ban nhap thong tin General --- " << endl;
			NhapThongTinCaiDat_General();
			system("cls");
			break;

		case 0:		//case 0 Exit
			menu();
			break;
		}
	} while (selection != 0);
}

/*
* The function to input data of Sound
*/
void NhapThongTinCaiDat_Sound()
{
	string continues = "n";

	//Over and over again constantly until user choice No (do not want to add new Sound)
	do {

		system("cls");
		cout << "--- Input Sound setting ---" << endl;
		cout << "Index car: " << soundCount + 1 << "\n";

		//Require user input setting data
		Setting st = setting->nhapThongTin();

		// The case user input personal key is exist
		if (isKeyExisted(st.getPersonalKey()))
		{
			//Update data of Setting list
			listSetting.at(position)->updateSetting(st);
			cout << "-> This car already existed, data will be overriten\n";
			//Require user input data for Sound and update data of Sound list
			listSound.at(position)->nhapThongTin(st);
			listDisplay.at(position)->updateDisplay(st);
			listGeneral.at(position)->updateGeneral(st);
		}
		else {	// The case user input personal key is not exist

			cout << "-> This is car, data will be appended to you list\n";
			//Add new Setting
			Setting* set = new Setting();
			set->updateSetting(st);
			listSetting.push_back(set);

			//Add new Sound
			Sound* s = new Sound(st);
			s->nhapThongTin(st);	//require user input data of Sound
			listSound.push_back(s);

			//Add empty Display and General
			listDisplay.push_back(new Display(st));
			listGeneral.push_back(new General(st));
			soundCount++;
		}

		//Ask user want to input new sound or not
		//Do again if user input data is invalid (input difference Yes/ No)
		do {
			cout << "Will you input for Car " << soundCount + 1 << " ? (y/n): ";
			cin >> continues;

			//if user-entered is invalid then send warnign message
			if (continues != "N" && continues != "n" && continues != "Y" && continues != "y")
			{
				cout << "\nPlease just enter \'Y\' or \'y\' to say \"Yes\" or \'N\' or \'n\' to say \"No\"\n" << endl;
			}
		} while (continues != "N" && continues != "n" && continues != "Y" && continues != "y");

		//if user choose No then break 
		if (continues == "N" || continues == "n") {
			system("cls");
			break;
		}
		cout << "\n" << endl;
		cout << endl;

	} while (continues == "y" || continues == "Y");
}

/*
* The function to input data of General
*/
void NhapThongTinCaiDat_General()
{
	string continues = "n";

	//Over and over again constantly until user choice No (do not want to add new General)
	do {

		system("cls");
		cout << "--- Input General setting ---" << endl;
		cout << "Index car: " << generalCount + 1 << "\n";

		//Require user input setting data
		Setting st = setting->nhapThongTin();

		// The case user input personal key is exist
		if (isKeyExisted(st.getPersonalKey()))
		{
			//Update data of Setting list
			listSetting.at(position)->updateSetting(st);
			cout << "-> This car already existed, data will be overriten\n";
			//Require user input data for General and update data of General list
			listGeneral.at(position)->nhapThongTin(st);
			listDisplay.at(position)->updateDisplay(st);
			listSound.at(position)->updateSound(st);
		}
		else {	// The case user input personal key is not exist

			cout << "-> This is car, data will be appended to you list\n";
			//Add new Setting
			Setting* set = new Setting();
			set->updateSetting(st);
			listSetting.push_back(set);

			//Add new Sound
			General* g = new General(st);
			g->nhapThongTin(st);	//require user input data of General
			listGeneral.push_back(g);

			//Add empty Display and Sound
			listDisplay.push_back(new Display(st));
			listSound.push_back(new Sound(st));
			generalCount++;
		}

		//Ask user want to input new sound or not
		//Do again if user input data is invalid (input difference Yes/ No)
		do {
			cout << "Will you input for Car " << generalCount + 1 << " ? (y/n): ";
			cin >> continues;

			//if user-entered is invalid then send warnign message
			if (continues != "N" && continues != "n" && continues != "Y" && continues != "y")
			{
				cout << "\nPlease just enter \'Y\' or \'y\' to say \"Yes\" or \'N\' or \'n\' to say \"No\"\n" << endl;
			}
		} while (continues != "N" && continues != "n" && continues != "Y" && continues != "y");

		//if user choose No then break 
		if (continues == "N" || continues == "n") {
			system("cls");
			break;
		}
		cout << "\n" << endl;
		cout << endl;

	} while (continues == "y" || continues == "Y");
}

/*
* The function to input data of Display
*/
void NhapThongTinCaiDat_Display()
{
	string continues = "n";

	//Over and over again constantly until user choice No (do not want to add new Display)
	do {

		system("cls");
		cout << "--- Input Sound setting ---" << endl;
		cout << "Index car: " << displayCount + 1 << "\n";

		//Require user input setting data
		Setting st = setting->nhapThongTin();

		// The case user input personal key is exist
		if (isKeyExisted(st.getPersonalKey()))
		{
			//Update data of Setting list
			listSetting.at(position)->updateSetting(st);
			cout << "-> This car already existed, data will be overriten\n";
			//Require user input data for Display and update data of Display list
			listDisplay.at(position)->nhapThongTin(st);
			listSound.at(position)->updateSound(st);
			listGeneral.at(position)->updateGeneral(st);
		}
		else {	// The case user input personal key is not exist

			cout << "-> This is car, data will be appended to you list\n";
			//Add new Setting
			Setting* set = new Setting();
			set->updateSetting(st);
			listSetting.push_back(set);

			//Add new Display
			Display* dpl = new Display(st);
			dpl->nhapThongTin(st);	//require user input data of Display
			listDisplay.push_back(dpl);

			//Add empty Sound and General
			listSound.push_back(new Sound(st));
			listGeneral.push_back(new General(st));
			displayCount++;
		}

		//Ask user want to input new sound or not
		//Do again if user input data is invalid (input difference Yes/ No)
		do {
			cout << "Will you input for Car " << displayCount + 1 << " ? (y/n): ";
			cin >> continues;

			//if user-entered is invalid then send warnign message
			if (continues != "N" && continues != "n" && continues != "Y" && continues != "y")
			{
				cout << "\nPlease just enter \'Y\' or \'y\' to say \"Yes\" or \'N\' or \'n\' to say \"No\"\n" << endl;
			}
		} while (continues != "N" && continues != "n" && continues != "Y" && continues != "y");

		//if user choose No then break 
		if (continues == "N" || continues == "n") {
			system("cls");
			break;
		}
		cout << "\n" << endl;
		cout << endl;

	} while (continues == "y" || continues == "Y");
}

/*
* The function to handle menu print setting information
*/
void XuatThongTinCaiDat() {
	//declare local variables and string regex
	int selection;
	regex isDigit("^[1-5]");
	bool error = false;

	//Over and over again constantly until user choice Exit
	do {
		string user_choice;

		do {
			error = false;
			system("cls");

			user_choice = "";
			//display menu
			cout << " --- SELECT MENU --- " << endl;
			cout << " 1. Print display setting information" << endl;
			cout << " 2. Print sound setting information" << endl;
			cout << " 3. Print general setting information" << endl;
			cout << " 4. Print all setting information" << endl;
			cout << " 5. Exit" << endl;
			cout << " Your selection: ";
			cin >> user_choice;

			//catch the case user input is not a number and from 0 to 5
			if (!regex_match(user_choice, isDigit))
			{
				cout << "Please enter a number from 0 to 5!" << endl;
				system("pause");
				error = true;
			}
		} while (error == true);

		selection = stoi(user_choice);		//cast string to int
		system("cls");
		
		//Handle the cases user choose
		switch (selection) {

		case 1:		//case 1: print data of Display
			XuatThongTinCaiDat_Display();
			system("pause");
			system("cls");
			break;

		case 2:		//case 2: print data of Sound
			XuatThongTinCaiDat_Sound();
			system("pause");
			system("cls");
			break;

		case 3:		//case 3: print data of General
			XuatThongTinCaiDat_General();
			system("pause");
			system("cls");
			break;

		case 4:		//case 4: print all data
			XuatThongTatCaTinCaiDat();
			system("pause");
			system("cls");
			break;

		case 5:		//case 5: Back main menu
			menu();
			break;
		}
	} while (selection != 5);
}

const vector<string> explode(const string& s, const char& c)
{
	string buff{ "" };
	vector<string> v;

	for (auto n : s)
	{
		if (n != c)
			buff += n;
		else if (n == c && buff != "")
		{
			v.push_back(buff);
			buff = "";
		}
	}
	if (buff != "")
		v.push_back(buff);

	return v;
}

/*
* The function work with file data timezone and set timezone
*/
void downloadTimeZone() {
	//declare variables
	ifstream file_in;
	file_in.open("timezones.txt");
	CommonInfo commonInfo;
	string data;
	vector<string> data_vector;

	//read until end of file
	while (!file_in.eof()) {
		while (getline(file_in, data)) {
			// cut data
			data_vector = explode(data, '/');

			if (data_vector.size() == 2)
			{
				// set data of Timezone to common info vector
				commonInfo.setNumber(data_vector[0]);
				commonInfo.setName(data_vector[1]);
				timezoneList.push_back(commonInfo);
			}
		}
	}
	// close file after worked
	file_in.close();

	// Sort list Timezone
	sort(timezoneList.begin(), timezoneList.end(), comparatorTimezone);
}

/*
* The function work with file data language and set language
*/
void downloadLanguage() {

	//declare variables
	ifstream file_in;
	file_in.open("languages.txt");
	CommonInfo commonInfo;
	string data;
	vector<string> data_vector;

	//read until end of file
	while (!file_in.eof()) {
		while (getline(file_in, data)) {
			// cut data
			data_vector = explode(data, '/');

			if (data_vector.size() == 2)
			{
				// set data of Language to common info vector
				commonInfo.setNumber(data_vector[0]);
				commonInfo.setName(data_vector[1]);
				languageList.push_back(commonInfo);
			}
		}
	}
	// close file after worked
	file_in.close();

	//Sort list Language
	sort(languageList.begin(), languageList.end(), comparatorLanguage);
}

/*
* The function to print data of Sound
*/
void XuatThongTinCaiDat_Sound() {

	//Initialize vector Sound temp
	vector<Sound*> v_sound_tmp(listSound);
	//Sort Sound to show
	sort(v_sound_tmp.begin(), v_sound_tmp.end(), comparatorSound);

	cout << setw(20) << left << "Owner name" << setw(25) << left << "Email" << setw(15) << left << "Key number" << setw(15) << left << "ODO number" << setw(20) << left << "Remind Service (km)" << setw(10) << left << "Media" << setw(10) << left << "Call" << setw(10) << left << "Navi" << setw(10) << left << "Notify" << endl;

	for (int i = 0; i < listSetting.size(); i++) {
		cout << setw(20) << left << v_sound_tmp.at(i)->getCarName()
			<< setw(25) << left << v_sound_tmp.at(i)->getEmail()
			<< setw(15) << left << v_sound_tmp.at(i)->getPersonalKey()
			<< setw(15) << left << v_sound_tmp.at(i)->getODO()
			<< setw(20) << left << v_sound_tmp.at(i)->getServiceRemind()
			<< setw(10) << left << v_sound_tmp.at(i)->get_media_level()
			<< setw(10) << left << v_sound_tmp.at(i)->get_call_level()
			<< setw(10) << left << v_sound_tmp.at(i)->get_navi_level()
			<< setw(10) << left << v_sound_tmp.at(i)->get_notification_level()
			<< endl;
	}
}

/*
* The function to print data of General
*/
void XuatThongTinCaiDat_General() {

	string timezoneStr = "";
	//Initialize vector General temp
	vector<General*> v_general_tmp(listGeneral);
	//Sort General to show
	sort(v_general_tmp.begin(), v_general_tmp.end(), comparatorGeneral);

	cout << setw(20) << left << "Owner name" << setw(20) << left << "Email" << setw(15) << left << "Key number" << setw(15) << left << "ODO number" << setw(20) << left << "Remind Service (km)" << setw(50) << left << "TimeZone" << setw(50) << left << "Language" << endl;

	for (int i = 0; i < listSetting.size(); i++) {

		timezoneStr = getStringTimezone(v_general_tmp.at(i)->get_timeZone());

		cout << setw(20) << left << v_general_tmp.at(i)->getCarName()
			<< setw(20) << left << v_general_tmp.at(i)->getEmail()
			<< setw(15) << left << v_general_tmp.at(i)->getPersonalKey()
			<< setw(15) << left << v_general_tmp.at(i)->getODO()
			<< setw(20) << left << v_general_tmp.at(i)->getServiceRemind()
			<< setw(49) << left << timezoneStr
			<< setw(50) << left << v_general_tmp.at(i)->get_language() << endl;
	}
}

/*
* The function to print data of Display
*/
void XuatThongTinCaiDat_Display() {

	//Initialize vector Display temp
	vector<Display*> v_display_tmp(listDisplay);
	//Sort Display to show
	sort(v_display_tmp.begin(), v_display_tmp.end(), comparatorDisplay);

	cout << setw(20) << left << "Owner name"
		<< setw(25) << left << "Email"
		<< setw(15) << left << "Key number"
		<< setw(15) << left << "ODO number"
		<< setw(20) << left << "Remind Service (km)"
		<< setw(15) << left << "Light level"
		<< setw(20) << left << "Screen light level"
		<< setw(15) << left << "Taplo level" << endl;

	for (int i = 0; i < listSetting.size(); i++) {

		cout << setw(20) << left << v_display_tmp.at(i)->getCarName()
			<< setw(25) << left << v_display_tmp.at(i)->getEmail()
			<< setw(15) << left << v_display_tmp.at(i)->getPersonalKey()
			<< setw(15) << left << v_display_tmp.at(i)->getODO()
			<< setw(20) << left << v_display_tmp.at(i)->getServiceRemind()
			<< setw(15) << left << v_display_tmp.at(i)->get_light_level()
			<< setw(20) << left << v_display_tmp.at(i)->get_screen_light_level()
			<< setw(15) << left << v_display_tmp.at(i)->get_taplo_light_level() << endl;
	}
}

/*
* The function to print all data
*/
void XuatThongTatCaTinCaiDat() {

	string timezoneStr = "";

	//Initialize vector Sound temp
	vector<Sound*> v_sound_tmp(listSound);
	sort(v_sound_tmp.begin(), v_sound_tmp.end(), comparatorSound);

	//Initialize vector Display temp
	vector<Display*> v_display_tmp = listDisplay;
	sort(v_display_tmp.begin(), v_display_tmp.end(), comparatorDisplay);

	//Initialize vector General temp
	vector<General*> v_general_tmp(listGeneral);
	sort(v_general_tmp.begin(), v_general_tmp.end(), comparatorGeneral);

	cout << "--- All setting ---" << endl;

	//Traversal each data in settings
	for (int i = 0; i < listSetting.size(); i++) {

		//get Timezone
		timezoneStr = getStringTimezone(v_general_tmp.at(i)->get_timeZone());

		cout << setw(10) << left << i + 1 << setw(20) << left << "Owner name" << setw(25) << left << "Email" << setw(20) << left << "Key number" << setw(20) << left << "ODO number" << setw(20) << left << "Remind Service (km)" << endl;

		//print data of Setting
		cout << setw(10) << left << ""
			<< setw(20) << left << v_display_tmp.at(i)->getCarName()
			<< setw(25) << left << v_display_tmp.at(i)->getEmail()
			<< setw(20) << left << v_display_tmp.at(i)->getPersonalKey()
			<< setw(20) << left << v_display_tmp.at(i)->getODO()
			<< setw(20) << left << v_display_tmp.at(i)->getServiceRemind() << endl;

		//Print data of Display
		cout << setw(20) << left << "Display:" << setw(15) << "Light level" << setw(20) << "Screen Light level" << setw(15) << "Taplo Light" << endl;

		cout << setw(20) << left << ""
			<< setw(15) << v_display_tmp.at(i)->get_light_level()
			<< setw(20) << v_display_tmp.at(i)->get_screen_light_level()
			<< setw(15) << v_display_tmp.at(i)->get_taplo_light_level() << endl;

		//Print data of Sound
		cout << setw(20) << left << "Sound:" << setw(10) << left << "Media" << setw(10) << left << "Call" << setw(15) << left << "Navigation" << setw(10) << left << "Notify" << endl;

		cout << setw(20) << left << ""
			<< setw(10) << v_sound_tmp.at(i)->get_media_level()
			<< setw(10) << v_sound_tmp.at(i)->get_call_level()
			<< setw(15) << v_sound_tmp.at(i)->get_navi_level()
			<< setw(10) << v_sound_tmp.at(i)->get_notification_level() << endl;

		//Print data of General
		cout << setw(20) << "General:" << setw(50) << "Timezone" << setw(50) << "Language" << endl;
		cout << setw(20) << left << ""
			<< setw(49) << timezoneStr
			<< setw(50) << v_general_tmp.at(i)->get_language() << endl;
		cout << endl;
	}
}

/*
* The function to write data to file
*/
void writeDataToFile() {

	//declare file stream variables
	ofstream file_out;

	// get all value in setting array
	string formatString;

	// Handle open file and write data into file
	try
	{
		// open txt file
		file_out.open("Settings.txt");

		// Write data of Setting, Display, Sound and General to file
		for (int i = 0; i < listSetting.size(); i++)
		{
			// Concatenate Setting data to a string
			formatString = "Setting:" + listSetting.at(i)->formatTypeSetting() + "/";

			// Concatenate Display data to a string
			formatString += "Display:" + listDisplay.at(i)->formatTypeDisplay() + "/";

			// Concatenate Sound data to a string
			formatString += "Sound:" + listSound.at(i)->formatTypeSound() + "/";

			// Concatenate General data to a string 
			formatString += "General:" + listGeneral.at(i)->formatTypeGeneral() + "/";

			// Write data to file
			file_out << formatString + "\n";
		}

		// close file after worked
		file_out.close();
	}
	catch (...)		// Throw message when occur error during write file
	{
		cout << "Exception occur when save file!";
	}
}

// Get data from file setting.txt
void readDataFromFile() {

	//declare file stream variables
	ifstream file_in;
	string data;

	// Handle read data from file and add data to List
	try
	{
		// Open file setting.txt
		file_in.open("Settings.txt");

		// Check if file is open
		if (file_in.is_open())
		{
			// read each line in text file
			while (!file_in.eof())
			{
				// Get a line in file
				getline(file_in, data);
				// Use data have just get from file to handle add data to list
				handleDataInFile(data);
			}
		}
	}
	catch (...)		// Throw message when occur error during read file
	{
		cerr << "Exception occur when open file!" << endl;
	}
}

/*
* The function to handle separate string data file, check and add data from file to List
*/
void handleDataInFile(string line) {

	int currentSettingCount = 0;

	// Continue separate string in dataInLine and store in vector
	vector<string> data_in_line = explode(line, '/');
	// Declare temparory value for Setting data
	string car_name, email, personal_key, odo, service_remind;

	// Loop each data cluster in data_in_line
	for (int i = 0; i < data_in_line.size(); i++)
	{
		// Separate string in data_in_line and store in vector sub_data
		vector<string> sub_data = explode(data_in_line[i], ':');

		// The case is Setting
		if (sub_data[0] == "Setting")
		{
			vector<string> dataDetail = explode(sub_data[1], ',');

			// Assign data to temp variables
			car_name = dataDetail[0];
			email = dataDetail[1];
			personal_key = dataDetail[2];
			odo = dataDetail[3];
			service_remind = dataDetail[4];

			// Add data to list Setting
			Setting* st = new Setting(car_name, personal_key, email, stoi(odo), stoi(service_remind));
			listSetting.push_back(st);

			//get index after add new data to list Setting
			currentSettingCount = listSetting.size() - 1;

			// Add new empty Sound, Display and General to List
			listSound.push_back(new Sound());
			listDisplay.push_back(new Display());
			listGeneral.push_back(new General());

		}
		else if (sub_data[0] == "Display")	// The case is Display
		{
			vector<string> dataDetail = explode(sub_data[1], ',');

			// Get Setting
			Setting st = Setting(car_name, personal_key, email, stoi(odo), stoi(service_remind));

			// Update data to Display list
			// The order of the parameters passed: light level-[0], screen level-[1], taplo level-[1]
			listDisplay.at(currentSettingCount)->updateDisplay(st, stoi(dataDetail[0]), stoi(dataDetail[1]), stoi(dataDetail[2]));
			displayCount++;

		}
		else if (sub_data[0] == "Sound")	// The case is Sound
		{
			vector<string> dataDetail = explode(sub_data[1], ',');

			// Get Setting
			Setting st = Setting(car_name, personal_key, email, stoi(odo), stoi(service_remind));

			// Update data to Sound list
			listSound.at(currentSettingCount)->updateSound(st, stoi(dataDetail[0]), stoi(dataDetail[1]), stoi(dataDetail[2]), stoi(dataDetail[3]));
			soundCount++;

		}
		else if (sub_data[0] == "General")	// The case is General
		{
			vector<string> dataDetail = explode(sub_data[1], ';');

			// Get Setting
			Setting st = Setting(car_name, personal_key, email, stoi(odo), stoi(service_remind));

			// Update data to General list
			listGeneral.at(currentSettingCount)->updateGeneral(st, dataDetail[0], dataDetail[1]);
			generalCount++;
		}
	}
}

/*
* The function to check key user-entered is exist or not
*/
bool isKeyExisted(string key) {

	//set default value for position
	position = 0;

	// Loop list Setting to check key user-enterd is exist or not
	for (int i = 0; i < listSetting.size(); i++)
	{
		//if key is exist
		if (listSetting.at(i)->getPersonalKey() == key)
		{
			position = i;	// set value of position by i
			return true;
		}
	}

	//if key is not exist
	return false;
}

/*
* The function to find and get string timezone 
*/
string getStringTimezone(string timezone) {

	//Loop each item in timezone list to find and get timezone data match with passed parameter
	for (CommonInfo &item : timezoneList) {
		
		// If match, return a string = UTC / Area
		if (item.getName() == timezone) {
			return item.getNumber() + "/" + item.getName();
		}
	}

	// If is not match, return not Found
	return "Not Found!";
}

/*
* The function to sort list Display by personalKey
*/
bool comparatorDisplay(Display* display1, Display* display2) {
	return ((*display1).getPersonalKey() < (*display2).getPersonalKey());
}

/*
* The function to sort list Sound by personalKey
*/
bool comparatorSound(Sound* sound1, Sound* sound2) {
	return ((*sound1).getPersonalKey() < (*sound2).getPersonalKey());
}

/*
* The function to sort list General by personalKey
*/
bool comparatorGeneral(General* general1, General* general2) {
	return ((*general1).getPersonalKey() < (*general2).getPersonalKey());
}

/*
* The function to sort list Timezone by UTC
*/
bool comparatorTimezone(CommonInfo c1, CommonInfo c2) {
	return (c1.getNumber() < c2.getNumber());
}

/*
* The function to sort list Language by alphabet
*/
bool comparatorLanguage(CommonInfo c1, CommonInfo c2) {
	return (c1.getName() < c2.getName());
}