/*
 * Title:		Single Linked List implementation of the ADT List
 * Purpose:		A subclass of ADT List that implements each of the methods
 * 				of the ADT list using an underlying single linked list to
 * 				hold the elements.
 * Author:		Carlos Arias
 * Date:		April 29, 2020
 */
#include "object.h"
#include "linkedlist.h"

#include <string>
#include <sstream>
using std::string;
using std::stringstream;
/**
 * Default constructor
 * Just sets the head to nullptr
 */
LinkedList::LinkedList() : _head(nullptr){
}
/**
 * Copy Constructor
 * Creates a deep copy of the list. It creates a clone each of the
 * elements in the original list and inserts them into the copy,
 * this insertion is done using the Insert method.
 * The time complexity of this method could be improved by inserting
 * directly instead of using Insert.
 * @param list the list to be copied
 */
LinkedList::LinkedList(const LinkedList& list): _head(nullptr){
	for (Node* tmp = list._head; tmp != nullptr; tmp = tmp->next){
		Insert(tmp->data->Clone(), _size);
	}
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
const LinkedList& LinkedList::operator=(const LinkedList& rhs){
	return *this;
}
/**
 * Destructor
 * It frees the dynamic memory allocated for the list, it does so by
 * traversing the list and releasing the memory of each element and
 * then its node.
 */
LinkedList::~LinkedList(){
	Node* tempNode = _head;
	while (_head != nullptr){
		_head = tempNode->next;
		if (tempNode->data)
			delete tempNode->data;
		delete tempNode;
		tempNode = _head;
	}
//	Another way to do it
//	Which one is best?
//	while (_size != 0){
//		Object* tmp = Remove(0);
//		delete tmp;
//	}
}
/**
 * Inserts an element into a given position.
 * This operation has the following steps:
 * 1. Check if the position is valid
 * 2. Creates a new node and links it to the element
 * 3. If the list is empty, the head points to the new node
 * 4. If the list is not empty but want to insert in position zero
 *    it links the list and updates the head
 * 5. If the position is not zero and the list is not empty, it tra-
 *    verses the list up the element that precedes the element to be
 *    inserted. Links the new node to that position
 * @param element what the client wants to insert into the list
 * @param position the position where the element is to be inserted
 * @return true if it was possible to insert, false otherwise. It will not be able
 * to insert if the position is invalid.
 */
bool LinkedList::Insert(Object* element, size_t position){
	if (position > _size){
		return false;
	}
	Node* neo = new Node;
	neo->data = element;
	neo->next = nullptr;
	if (_size == 0){ // The list is empty
		_head = neo;
	}else if (position == 0){
		neo->next = _head;
		_head = neo;
	}else{
		Node* tmp = _head;
		for (size_t i = 0; i < position -1; i++){
			tmp = tmp->next;
		}
		neo->next = tmp->next;
		tmp->next = neo;
	}
	_size++;
	return true;
}
/**
 * Searches for the position of an element in the list.
 * The method performs a linear search, traversing the list, for the given
 * element.
 * If the element is found it returns the position, if it is not found it
 * returns -1. It is important to note that for this operation to succeed it
 * is necessary to override the method Equals of all the types inserted into
 * the list.
 * @param element the object that the client is searching for.
 * @return the position of the element if found, -1 otherwise.
 */
int LinkedList::IndexOf(Object* element)const{
	size_t index = 0;
	for (Node* tmp = _head; tmp != nullptr; tmp = tmp->next){
		if (tmp->data->Equals(*element)){
			return index;
		}
		index++;
	}
	return -1;
}
/**
 * Removes the element at position, when the position is valid. It returns
 * the pointer to the removed element. This method does not release any
 * dynamically allocated object. It is left to the client to release the
 * memory of the removed element. After removing the element, the list needs
 * to be correctly link to avoid losing the reference to the elements after
 * the removed element.
 * @param position the position of the element to be removed.
 * @return the pointer to the object in that position if the position was valid,
 * nullptr otherwise
 */
Object* LinkedList::Remove(size_t position){
	if (position >= _size){
		return nullptr;
	}
	Object* retVal = nullptr;
	Node* tmp = nullptr;
	if (position == 0){ // Want to remove the first element, _head
		retVal = _head->data;
		_head->data = nullptr;
		tmp = _head->next;
		_head->next = nullptr;
		delete _head;
		_head = tmp;
	}else {
		tmp = _head;
		for (size_t i = 0; i < position -1; i++){
			tmp = tmp->next;
		}
		Node* toRemove = tmp->next;
		retVal = toRemove->data;
		tmp->next = toRemove->next;
		toRemove->next = nullptr;
		toRemove->data = nullptr;
		delete toRemove;
	}
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
Object* LinkedList::Get(size_t position)const{
	if (position >= _size){
		return nullptr;
	}
	Node* tmp = _head;
	for (size_t i = 0; i < position; i++) {
		tmp = tmp->next;
	}
	return tmp->data;
}
/**
 * Creates a string representation of the list. This representation
 * will be the string representation of each of the elements, surrounding
 * the whole list with curly braces and separating the elements by comma.
 * Example: {2, 6, 8}
 * -----------------------------------------------------------------------
 * Since all derived classes have the same code, can this be done in the
 * List class?
 * @return a string representation of the list
 */
string LinkedList::ToString()const{
	stringstream retVal;
	retVal << "{";
	Node* tmp;
	for (tmp = _head; tmp->next != nullptr; tmp = tmp->next) {
		retVal << tmp->data->ToString() << ", ";
	}
	retVal << tmp->data->ToString() << "}";
	return retVal.str();
}
/**
 * Very similar to the destructor, this method releases all the elements
 * of the list. It also sets the size to zero, and the head to nullptr.
 * This method makes the list become empty.
 */
void LinkedList::Clear(){
	Node* tempNode = _head;
	while (_head != nullptr){
		_head = tempNode->next;
		if (tempNode->data)
			delete tempNode->data;
		delete tempNode;
		tempNode = _head;
	}
	_head = nullptr;
	_size = 0;

//	Another way to do it
//	Which one is best?
//	while (_size != 0){
//		Object* tmp = Remove(0);
//		delete tmp;
//	}
//	_size = 0;

}
