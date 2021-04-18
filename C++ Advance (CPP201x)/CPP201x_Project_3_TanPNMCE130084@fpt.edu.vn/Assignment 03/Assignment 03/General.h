#ifndef GENERAL_H_
#define GENERAL_H_
#include "Setting.h"
#include <vector>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class General : public Setting {
public:
	General();
	General(Setting setting);
	~General();
	void nhapThongTin(Setting);
	void updateGeneral(Setting setting, string timeZone, string language);
	void updateGeneral(Setting setting);
	string formatTypeGeneral();

	string get_language();
	string get_timeZone();
	void set_timeZone(string data);
	void set_language(string data);
protected:
	string timeZone;
	string language;
};

#endif // GENERAL_H_