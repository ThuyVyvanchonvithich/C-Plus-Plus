#include "list.h"

template <class T>
List<T>::List()
{
	List::index = 0;
}

template <typename T>
List<T>::~List()
{
}

template<class T>
void List<T>::add(T const& item)
{
	if (List::index <= 100) {

		List::elements_[index] = item;
		List::index++;
	}
	else {
		cout << "Can not add more because the number of elements in List is maximum (100 elements)!" << endl;
	}
}

template<class T>
T List<T>::get(int pos)
{
	if (List::index <= 100) {
		return List::elements_[pos];
	}
}

template<class T>
int List<T>::size()
{
	return index;
}

template class List<Setting*>;
template class List<Sound*>;
template class List<General*>;
template class List<Display*>;
