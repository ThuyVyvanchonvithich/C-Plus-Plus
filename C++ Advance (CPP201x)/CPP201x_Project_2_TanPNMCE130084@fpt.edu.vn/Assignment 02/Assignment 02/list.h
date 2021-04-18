#ifndef LIST_H_
#define LIST_H_
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include "Setting.h"
#include "Display.h"
#include "Sound.h"
#include "General.h"

template<class T>
class List {
private:
	T elements_[100];
	int index = 0;
public:
	List();
	virtual ~List();
	void add(T const&);
	T get(int pos);
	int size();
};

#endif /* LIST_H_ */
