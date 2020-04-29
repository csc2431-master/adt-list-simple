/*
 * Title:		Fixed Size Array List
 * Purpose:		Implementation the ADT List using an underlying fixed size array.
 * 				The array will be allocated at construction with the specified
 * 				capacity.
 * 				This file contains the implementation of the class' methods
 * Author:		Carlos Arias
 * Date:		April 29, 2020
 */
#include "object.h"
#include "list.h"
#include "fsarray.h"

#include <string>
#include <iostream>
#include <sstream>
using std::string;
using std::istream;
using std::ostream;
using std::stringstream;

/**
 * Constructor with capacity
 * Note: This constructor should be made explicit to avoid auto-conversions
 * Given a capacity the constructor allocates an array to Object*
 * this array will later hold pointers to the actual elements
 * that are being inserted into the list. The constructor also initializes
 * the elements of the array to nullptr
 * @param capacity the number of elements that the list is able to hold
 */
FSArray::FSArray(size_t capacity) : _capacity(capacity){
	_data = new Object*[_capacity];
	for (size_t i = 0; i < _capacity; i++) {
		_data[i] = nullptr;
	}
}
/**
 * Copy Constructor
 * Creates a deep copy of the list. It allocates the same capacity of
 * elements for the copy and then clones each of the elements in the
 * original list and inserts them into the copy, this insertion is
 * done directly into the array.
 * @param list the list to be copied
 */
FSArray::FSArray(const FSArray& list) : _capacity(list._capacity){
	// Is there a bug here? --> Solved by setting _size to be protected
	_size = list._size;
	_data = new Object*[_capacity];
	for (size_t i = 0; i < _size; i++) { // Issa correction to the _capacity
		_data[i] = list.Get(i)->Clone();
	}
	for (size_t i = _size; i < _capacity; i++){
		_data[i] = nullptr;
	}
}
/**
 * Destructor
 * It frees the dynamic memory allocated for the list, it does so in
 * two steps:
 * 1. Traverses the list and releases the memory of each element. This in
 *    turn will call the destructor of each of the elements.
 * 2. Once the elements have been freed, then the array memory is released.
 */
FSArray::~FSArray(){
	// Step 1
	for (size_t i = 0; i < _size; i++) {
		delete _data[i];
	}
	// Step 2
	delete[] _data;
}
/**
 * Copy assignment operator
 * Enables the deep copy assignment using the operator = overload. This
 * method is kept private to avoid usage from clients of the class.
 * This method also relies on the Clone method to create copies of the
 * elements.
 * Note: Should the parameter be const List& ?
 * @param rhs the object to be copied into this
 * @return this to enable cascade assignments
 */
const FSArray& FSArray::operator=(const FSArray& rhs){
	if (&rhs == this){
		return *this;
	}
	if (_capacity != rhs._capacity){
		Clear();
		delete[] _data;
		_capacity = rhs._capacity;
		_data = new Object*[_capacity];
		for (size_t i = 0; i < _capacity; i++) {
			_data[i] = nullptr;
		}
	}
	for (size_t i = 0; i < rhs.Size(); i++) {
		_data[i] = rhs.Get(i)->Clone();
	}
	return *this;
}
/**
 * Inserts an element into a given position.
 * This operation has the following steps:
 * 1. Check if the position is valid
 * 2. Check if there is enough space
 * 3. If the position is not the last, it needs to push the elements
 * 4. Insert the element in the given position
 * 5. Increase the size
 * @param element what the client wants to insert into the list
 * @param position the position where the element is to be inserted
 * @return true if it was possible to insert, false otherwise. It will not be able
 * to insert if the position is invalid or if the list is full.
 */
bool FSArray::Insert(Object* element, size_t position){
	// Check if the position is valid
	if (position > _size)
		return false;
	// Check if there is enough space
	if (_capacity == _size)
		return false;

	if (position < _size){ // We need to shift
		// WARNING WILL ROBINSON : Lost in Space Reference
		// Be careful with size_t when subtracting
		for (size_t i = _size; i > position; i--){
			_data[i] = _data[i - 1];
		}
	}
	_data[position] = element;
	_size++;
	return true;
}
/**
 * Searches for the position of an element in the list.
 * The method performs a linear search on the array for the given element.
 * If the element is found it returns the position, if it is not found it
 * returns -1. It is important to note that for this operation to succeed it
 * is necessary to override the method Equals of all the types inserted into
 * the list.
 * @param element the object that the client is searching for.
 * @return the position of the element if found, -1 otherwise.
 */
int FSArray::IndexOf(Object* element)const{
	for (size_t i = 0; i < _size; i++) {
		if (_data[i]->Equals(*element)){
			return i;
		}
	}
	return -1;
}
/**
 * Removes the element at position, when the position is valid. It returns
 * the pointer to the removed element. This method does not release any
 * dynamically allocated object. It is left to the client to release the
 * memory of the removed element. After removing the element, the rest of
 * the elements in the list will be pushed to cover the empty space, unless
 * the removed element is the last, in which case is just set to nullptr.
 * @param position the position of the element to be removed.
 * @return the pointer to the object in that position if the position was valid,
 * nullptr otherwise
 */
Object* FSArray::Remove(size_t position){
	if (position >= _size){
		return nullptr;
	}
	Object* retVal = _data[position];
	for (size_t i = position; i < _size - 1; i++) {
		_data[i] = _data[i + 1];
	}
	_data[_size - 1] = nullptr;
	_size--;
	return retVal;
}
/**
 * Element Access
 * Returns the element at a given position. Note that it is not a copy of the
 * element.
 * @param position the position of the element to retrieve.
 * @return a pointer to the element if the position is valid, nullptr otherwise
 */
Object* FSArray::Get(size_t position)const{
	if (position >= _size)
		return nullptr;
	else
		return _data[position];
}
/**
 * Creates a string representation of the list. This representation
 * will be the string representation of each of the elements, surrounding
 * the whole list with curly braces and separating the elements by comma.
 * Example: {2, 6, 8}
 * @return a string representation of the list
 */
string FSArray::ToString()const{
	stringstream retVal;
	retVal << "{";
	for (size_t i = 0; i < _size - 1; i++) {
		retVal << _data[i]->ToString() << ", ";
	}
	retVal << _data[_size - 1]->ToString() << "}";
	return retVal.str();
}
/**
 * Very similar to the destructor, this method releases all the elements
 * of the list, but it does not release the array to hold elements. It also
 * sets the size to zero. This method makes the list become empty.
 */
void FSArray::Clear(){
	for (size_t i = 0; i < _size; i++) {
		delete _data[i];
		_data[i] = nullptr;
	}
	_size = 0;
}
/**
 * Capacity accessor
 * @return the number of elements the list is able to hold
 */
size_t FSArray::Capacity() const {
	return _capacity;
}