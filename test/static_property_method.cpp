#include <iostream>

class SomeClass {
public:

	[[using oodb: readwrite]]
	int someInt;
};
