#include "Setting.h"
#include <vector>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class General : public Setting {
public:
	General(string language, string timeZone);
	General(string personalKey, string timeZone, string language);
	General(string carName, string personalKey, string email, int odo, int remind, string language, string timeZone);
	General();
	~General();
	General nhapThongTin(Setting, string, string);
	string get_language();
	string get_timeZone();
	void set_timeZone(string data);
	void set_language(string data);
protected:

	string timeZone;
	string language;
};