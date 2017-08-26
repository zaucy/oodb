struct Subobject1 {
	[[using oodb: readwrite]]
	int someInt;
};

class ClassB {
public:
	[[using oodb: readonly]]
	int yo;

};

class ClassA {
public:

	[[using oodb: readwrite]]
	int something;

	// In mongodb this would translate into a sub document.
	[[using oodb: readwrite]]
	Subobject1 testSubobject;

	// In mongodb this wouldn't even be stored in the same object. ClassB would
	// be retreived from its own collection using this classes ID as ClassB's ID.
	[[using oodb: readwrite]]
	ClassB& otherObject;

	// You cannot have a reference refering to your own class or a derived class
	// as an oodb property.

	// NOT ALLOWED
	//[[using oodb: readwrite]]
	//ClassA& selfObject;


};

// C++ using generated code from the above.
int main() {

	ClassA a;

	a.testSubobject.someInt = 42;
	a.otherobject.yo = 1;
	a.something = 16;

	// This is not necessary. In the C++ environment a flush occurs on
	// destruction.
	ClassA::flush(a);

	return 0;
}