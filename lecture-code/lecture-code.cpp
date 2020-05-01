#include "../object.h"
#include "../integer.h"
#include "../person.h"

#include <iostream>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

int main(int argc, char* argv[]){
	if (argc != 2){
		cerr << "Not enough parameters, give me the array size!" << endl;
		cerr << "Usage: " << endl;
		cerr << argv[0] << " size" << endl;
		return 1;
	}
	Object** myObjects = nullptr;
	size_t size = atoi(argv[1]);
	myObjects = new Object*[size];

	myObjects[0] = new Person("Jake",2);
	myObjects[1] = new Integer(3);
	myObjects[2] = new Integer(7);
	myObjects[3] = new Person("Blanca", 44);

	for (int i = 0; i < size; ++i) {
		cout << myObjects[i]->ToString() << endl;
	}

	for (int i = 0; i < size; ++i) {
		delete myObjects[i];
	}
	delete[] myObjects;

	return 0;
}
