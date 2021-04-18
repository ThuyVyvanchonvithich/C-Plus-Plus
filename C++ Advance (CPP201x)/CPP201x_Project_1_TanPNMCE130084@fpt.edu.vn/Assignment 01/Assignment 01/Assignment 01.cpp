#include <iostream>
#include "General.h"
#include "Display.h"
#include"Setting.h"
#include "Sound.h"
#include "CommonInfo.h"
#include <fstream>
#include<regex>

//declare object
Display *display = new Display();
Sound *sound = new Sound();
General *general = new General();
Setting *setting = new Setting();

//declare array contain object
Setting arr_settings[100];
Sound arr_sounds[100];
General arr_generals[100];
Display arr_displays[100];

//declare variables and string regex
string languageTmp, timezoneTmp;
int displayCount = 1, soundCount = 1, generalCount = 1, settingCount = 0;
regex isDigit("[0-9]+");

///Forward declare
bool isPersonalKeyExisted(string personalKey);
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


void menu();

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int main(int argc, char** argv) {

	menu();

	return 0;
}

bool isPersonalKeyExisted(string personalKey) {

	if (settingCount == 0) {
		return false;
	}

	for (int i = 0; i < settingCount; i++) {
		if (personalKey == arr_settings[i].getPersonalKey()) {
			return true;
		}
	}

	return false;
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
			cout << "Please enter a number from 0 to 3!" << endl;
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
	string personalkey;
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
* The function input data for Sound
*/
void NhapThongTinCaiDat_Sound()
{

	// declare local variables
	string personalKey;
	string continues = "n";
	soundCount = 0;	//set index = 0
	bool error = false;

	//Over and over again constantly until user choice No (do not want to add new Sound)
	do {

		system("cls");
		//Input personal key to check it exist or not
		do {
			error = false;
			cout << "Personal key (Digit): ";
			cin >> personalKey;

			//Check key is numberic
			if (!regex_match(personalKey, isDigit))
			{
				system("cls");
				cout << "PERSONAL KEY must be a digit! \n" << endl;
				cin.ignore(256, '\n');
				error = true;
			}
			//Check key is 8 digitals
			if (personalKey.length() != 8)
			{
				system("cls");
				cout << "PERSONAL KEY must have 8 digitals! \n" << endl;
				cin.ignore(256, '\n');
				error = true;
			}
		} while (error == true);

		soundCount++;		//increase count index

		system("cls");
		cout << " --- Input Sound setting --- " << endl;
		cout << "Car index: " << displayCount << endl;

		//if personal key is not exist
		if (!isPersonalKeyExisted(personalKey)) {
			Setting st = setting->nhapThongTin(personalKey, false);
			arr_settings[settingCount] = st;
			arr_sounds[settingCount] = sound->nhapThongTin(st);
			arr_displays[settingCount] = display->insertEmptyDisplay(st);
			arr_generals[settingCount] = general->nhapThongTin(st, "(GMT+07:00) /  Bangkok, Hanoi, Jakarta", "Vietnamese");
			settingCount++;
		}
		else {		//if personal key is exist

			for (int i = 0; i < settingCount; i++)
			{
				if (personalKey == arr_settings[i].getPersonalKey()) {
					Setting st = setting->nhapThongTin(personalKey, true);
					arr_settings[i] = st;	//update Setting
					arr_sounds[i] = sound->nhapThongTin(st);	//update Sound
					break;
				}
			}
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
* The function input data for General
*/
void NhapThongTinCaiDat_General()
{
	//Declare variable
	string personalKey;
	generalCount = 0;
	string continues = "n";
	bool error = false;

	//Over and over again constantly until user choice No (do not want to add new General)
	do {

		system("cls");
		//Input personal key to check it exist or not
		do {
			error = false;
			cout << "Personal key (Digit): ";
			cin >> personalKey;

			//Check key is numberic
			if (!regex_match(personalKey, isDigit))
			{
				system("cls");
				cout << "PERSONAL KEY must be a digit! \n" << endl;
				cin.ignore(256, '\n');
				error = true;
			}

			//Check key is 8 digitals
			if (personalKey.length() != 8)
			{
				system("cls");
				cout << "PERSONAL KEY must be have 8 digitals! \n" << endl;
				cin.ignore(256, '\n');
				error = true;
			}
		} while (error == true);
		//system("cls");
		

		generalCount++;		//inrease index count

		system("cls");
		cout << " --- Input General setting --- " << endl;
		cout << "Car index: " << generalCount << endl;

		//if personal key is not exist
		if (!isPersonalKeyExisted(personalKey)) {

			//input data setting
			Setting st = setting->nhapThongTin(personalKey, false);
			//settings.push_back(st);
			cout << "This is car, data will be appended to your list" << endl;
			arr_settings[settingCount] = st;

			//choose language
			cout << "Language: " << endl;
			downloadLanguage();

			//choose timezone
			cout << "TimeZone: " << endl;
			downloadTimeZone();

			//add new general
			arr_generals[settingCount] = general->nhapThongTin(st, timezoneTmp, languageTmp);
			arr_sounds[settingCount] = sound->insertEmptySound(st);
			arr_displays[settingCount] = display->insertEmptyDisplay(st);
			settingCount++;
		}
		else	//if personal key is exist
		{

			for (int i = 0; i < settingCount; i++)
			{
				if (personalKey == arr_settings[i].getPersonalKey()) {
					Setting st = setting->nhapThongTin(personalKey, true);
					arr_settings[i] = st;

					//update data of General
					//choose language
					cout << "Language: " << endl;
					downloadLanguage();
					arr_generals[i].set_language(languageTmp);	//update language

					//choose timezone
					cout << "TimeZone: " << endl;
					downloadTimeZone();
					arr_generals[i].set_timeZone(timezoneTmp);	//update timezone
					break;
				}
			}
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
	} while (continues == "y");
}

/*
* The function input data for General
*/
void NhapThongTinCaiDat_Display()
{

	//declare local variables
	string personalKey;
	displayCount = 0;
	string continues = "n";
	bool error = false;

	//Over and over again constantly until user choice No (do not want to add new Display)
	do {

		system("cls");
		//Input personal key to check it exist or not
		do {
			error = false;
			cout << "Personal key (Digit): ";
			cin >> personalKey;

			//Check key is numberic
			if (!regex_match(personalKey, isDigit))
			{
				system("cls");
				cout << "PERSONAL KEY must be a digit! \n" << endl;
				error = true;
				cin.ignore(256, '\n');
			}

			//Check key is 8 digitals
			if (personalKey.length() != 8)
			{
				system("cls");
				cout << "PERSONAL KEY must have 8 digitals! \n" << endl;
				error = true;
				cin.ignore(256, '\n');
			}
		} while (error == true);
		
		displayCount++;

		system("cls");
		cout << " --- Input Display setting --- " << endl;
		cout << "Car index: " << displayCount << endl;

		//if personal key is not exist
		if (!isPersonalKeyExisted(personalKey)) {

			Setting st = setting->nhapThongTin(personalKey, false);
			//settings.push_back(st);
			cout << "This is car, data will be appended to your list" << endl;
			arr_settings[settingCount] = st;

			//add new Display
			arr_displays[settingCount] = display->nhapThongTin(st);
			arr_generals[settingCount] = general->nhapThongTin(st, "(GMT+07:00) /  Bangkok, Hanoi, Jakarta", "Vietnamese");	//add empty General object to vector
			arr_sounds[settingCount] = sound->insertEmptySound(st);	//add empty Sound object to vector
			settingCount++;
		}
		else {		//if personal key is exist

			for (int i = 0; i < settingCount; i++)
			{
				if (personalKey == arr_settings[i].getPersonalKey()) {
					Setting st = setting->nhapThongTin(personalKey, true);
					arr_settings[i] = st;	//update Setting
					arr_displays[i] = display->nhapThongTin(st);	//update Display
					break;
				}
			}
		}

		//Ask user want to input new sound or not
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
	} while (continues == "y");
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
			system("cls");
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
	// Declares variables and regex
	regex isDigit("[0-9]+");
	string user_choice = ""; 
	int arr[1000];
	bool error = false;
	ifstream fileIn;

	fileIn.open("timezones.txt");	//open and read data from timezones.txt
	// Check file open
	// If file not exist then show error message
	if (!fileIn.is_open())
	{
		cout << "Fail open file timezone";
		system("pause");
	}
	else	//if file exist then read file
	{
		cout << "----- SELECT TIMEZONE DATA -----" << endl;
		unsigned int lineNo = 0;
		int selection;
		// Create vector to hole file data
		vector<string> str_timezones;
		string str;

		// Read data from file to show on screen
		while (getline(fileIn, str)) {
			lineNo++;
			cout << setw(8) << lineNo << ":" << str << "\n";
			str_timezones.push_back(str);
		}

		do {
			error = false;
			cout << "YOUR SELECTION: ";
			cin >> user_choice;
			// Check input number
			if (!regex_match(user_choice, isDigit))
			{
				cout << "Select must be a integer number from 1 to 32" << endl;
				cin.ignore(256, '\n');
				error = true;
			}
			// Check input is from 1 to 32 or not
			if (stoi(user_choice) > 32 || stoi(user_choice) == 0)
			{
				cout << "Select must be a integer number from 1 to 32" << endl;
				cin.ignore(256, '\n');
				error = true;
			}
		} while (error == true);
		
		selection = stoi(user_choice);
		cout << str_timezones.at(selection - 1) << endl;

		//get and set timezone
		timezoneTmp = str_timezones.at(selection - 1);
		general->set_timeZone(str_timezones.at(selection - 1));
	}
	fileIn.close();	//close file after worked with file
	system("pause");
	system("cls");
}

/*
* The function work with file data language and set language
*/
void downloadLanguage() {
	// Declares variables and regex
	regex isDigit("[0-9]+");
	string user_choice = "";
	int selection;
	int position;
	bool error = false;
	ifstream fileIn;

	fileIn.open("languages.txt");	//open and read data from language.txt
	// Check file open
	// If file not exist then show error message
	if (!fileIn.is_open())
	{
		cout << "Fail open file language";
		system("pause");
	}
	else	//if file exist then read file
	{
		cout << "----- SELECT LANGUAGE DATA -----" << endl;
		unsigned int lineNo = 0;
		// Create vector to hole file data
		vector<string> language;
		string str;

		// Read and get line of data from file to show on screen
		while (getline(fileIn, str)) {
			lineNo++;
			cout << setw(8) << lineNo << ": " << str << "\n";
			language.push_back(str);
		}
		
		do {
			error = false;
			cout << "YOUR SELECTION: ";
			cin >> user_choice;
			// Check input number
			if (!regex_match(user_choice, isDigit))
			{
				cout << "Select must be a integer number from 1 to 32" << endl;
				cin.ignore(256, '\n');
				error = true;
			}

			//check input is from 1 to 30 or not
			if (stoi(user_choice) > 30 || stoi(user_choice) == 0)
			{
				cout << "Select must be a integer number from 1 to 32" << endl;
				cin.ignore(256, '\n');
				error = true;
			}
		} while (error == true);

		
		selection = stoi(user_choice);
		cout << language.at(selection - 1) << endl;

		//get and set language
		languageTmp = language.at(selection - 1);
		general->set_language(language.at(selection - 1));
	}

	fileIn.close();	//close file after worked with file
	system("pause");
	system("cls");
}

/*
* The function to print data of Sound
*/
void XuatThongTinCaiDat_Sound() {
	cout << setw(20) << left << "Owner name" << setw(25) << left << "Email" << setw(15) << left << "Key number" << setw(15) << left << "ODO number" << setw(20) << left << "Remind Service (km)" << setw(10) << left << "Media" << setw(10) << left << "Call" << setw(10) << left << "Navi" << setw(10) << left << "Notify" << endl;
	//sound->xuatThongTin(sounds);

	for (int i = 0; i < settingCount; i++) {
		cout << setw(20) << left << arr_settings[i].getCarName()
			<< setw(25) << left << arr_settings[i].getEmail()
			<< setw(15) << left << arr_settings[i].getPersonalKey()
			<< setw(15) << left << arr_settings[i].getODO()
			<< setw(20) << left << arr_settings[i].getServiceRemind()
			<< setw(10) << left << arr_sounds[i].get_media_level()
			<< setw(10) << left << arr_sounds[i].get_call_level()
			<< setw(10) << left << arr_sounds[i].get_navi_level()
			<< setw(10) << left << arr_sounds[i].get_notification_level()
			<< endl;
	}
}

/*
* The function to print data of General
*/
void XuatThongTinCaiDat_General() {
	cout << setw(20) << left << "Owner name" << setw(20) << left << "Email" << setw(15) << left << "Key number" << setw(15) << left << "ODO number" << setw(20) << left << "Remind Service (km)" << setw(50) << left << "TimeZone" << setw(50) << left << "Language" << endl;
	//general->xuatThongTin(generals);

	for (int i = 0; i < settingCount; i++) {

		cout << setw(20) << left << arr_settings[i].getCarName()
			<< setw(20) << left << arr_settings[i].getEmail()
			<< setw(15) << left << arr_settings[i].getPersonalKey()
			<< setw(15) << left << arr_settings[i].getODO()
			<< setw(20) << left << arr_settings[i].getServiceRemind()
			<< setw(50) << left << arr_generals[i].get_timeZone()
			<< setw(50) << left << arr_generals[i].get_language() << endl;
	}
}

/*
* The function to print data of Display
*/
void XuatThongTinCaiDat_Display() {
	cout << setw(20) << left << "Owner name" 
		<< setw(25) << left << "Email" 
		<< setw(15) << left << "Key number"
		<< setw(15) << left << "ODO number" 
		<< setw(20) << left << "Remind Service (km)" 
		<< setw(15) << left << "Light level"
		<< setw(20) << left << "Screen light level" 
		<< setw(15) << left << "Taplo level" << endl;

	//display->xuatThongTin(displays);	//call method xuatThongTin
	for (int i = 0; i < settingCount; i++) {

		cout << setw(20) << left << arr_settings[i].getCarName()
			<< setw(25) << left << arr_settings[i].getEmail()
			<< setw(15) << left << arr_settings[i].getPersonalKey()
			<< setw(15) << left << arr_settings[i].getODO()
			<< setw(20) << left << arr_settings[i].getServiceRemind()
			<< setw(15) << left << arr_displays[i].get_light_level()
			<< setw(20) << left << arr_displays[i].get_screen_light_level()
			<< setw(15) << left << arr_displays[i].get_taplo_light_level() << endl;
	}
}

/*
* The function to print all data
*/
void XuatThongTatCaTinCaiDat() {
	cout << "--- All setting ---" << endl;

	//Traversal each data in settings
	for (int i = 0; i < settingCount; i++) {

		cout << setw(10) << left << settingCount << setw(20) << left << "Owner name" << setw(25) << left << "Email" << setw(20) << left << "Key number" << setw(20) << left << "ODO number" << setw(20) << left << "Remind Service (km)" << endl;
		
		//print data of Setting
		cout << setw(10) << left << "" 
			<< setw(20) << left << arr_settings[i].getCarName()
			<< setw(25) << left << arr_settings[i].getEmail()
			<< setw(20) << left << arr_settings[i].getPersonalKey()
			<< setw(20) << left << arr_settings[i].getODO()
			<< setw(20) << left << arr_settings[i].getServiceRemind() << endl;

		//Print data of Display
		for (int dpl_count = 0; dpl_count < settingCount; dpl_count++) {
			if (arr_settings[i].getPersonalKey() == arr_displays[dpl_count].getPersonalKey()) {
				cout << setw(20) << left << "Display:" << setw(15) << "Light level" << setw(20) << "Screen Light level" << setw(15) << "Taplo Light" << endl;
				
				cout << setw(20) << left << "" 
					<< setw(15) << arr_displays[dpl_count].get_light_level()
					<< setw(20) << arr_displays[dpl_count].get_screen_light_level()
					<< setw(15) << arr_displays[dpl_count].get_taplo_light_level() << endl;
				break;
			}
		}

		//Print data of Sound
		for (int s_count = 0; s_count < settingCount; s_count++) {
			if (arr_settings[i].getPersonalKey() == arr_sounds[s_count].getPersonalKey()) {
				cout << setw(20) << left << "Sound:" << setw(10) << left << "Media" << setw(10) << left << "Call" << setw(15) << left << "Navigation" << setw(10) << left << "Notify" << endl;
				
				cout << setw(20) << left << "" 
					<< setw(10) << arr_sounds[s_count].get_media_level()
					<< setw(10) << arr_sounds[s_count].get_call_level()
					<< setw(15) << arr_sounds[s_count].get_navi_level()
					<< setw(10) << arr_sounds[s_count].get_notification_level() << endl;
				break;
			}
		}

		//Print data of General
		for (int g_count = 0; g_count < settingCount; g_count++) {
			if (arr_settings[i].getPersonalKey() == arr_generals[g_count].getPersonalKey()) {
				cout << setw(20) << "General:" << setw(50) << "Timezone" << setw(50) << "Language" << endl;
				cout << setw(20) << left << "" 
					<< setw(50) << arr_generals[g_count].get_timeZone()
					<< setw(50) << arr_generals[g_count].get_language() << endl;
				break;
			}
		}
	}
}