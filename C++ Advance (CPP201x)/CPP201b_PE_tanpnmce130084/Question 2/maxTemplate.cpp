template <typename T>
T myMax(T one, T two) {
	T bigger;
	if (one > two) bigger = one;
	else bigger = two;
	return bigger;
}