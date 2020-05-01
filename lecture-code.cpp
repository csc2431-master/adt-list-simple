#include "object.h"
#include "integer.h"
#include "person.h"

#include <iostream>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

int main(int argc, char* argv[]){
	const size_t SIZE = 4;
	Object* myObjects[SIZE]; // What is the type of myObjects

	myObjects[0] = new Person("Jake",2);
	myObjects[1] = new Integer(3);
	myObjects[2] = new Integer(7);
	myObjects[3] = new Person("Blanca", 44);

	for (int i = 0; i < SIZE; ++i) {
		cout << myObjects[i]->ToString() << endl;
	}


	return 0;
}
