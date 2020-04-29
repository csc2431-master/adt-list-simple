/*
 * Title:		Single Linked List implementation of the ADT List
 * Purpose:		A subclass of ADT List that implements each of the methods
 * 				of the ADT list using an underlying single linked list to
 * 				hold the elements.
 * Author:		Carlos Arias
 * Date:		April 29, 2020
 */
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "object.h"
#include "list.h"

#include <string>
using std::string;
/**
 * This class uses an underlying single link list as
 * the data structure to implement the ADT List. The struct
 * Node is the type of each of the "links" in the "chain"
 * that is formed when elements are added to the list.
 *                 -------
 * _head -------> |       |
 *                |   * -------> Some Object
 *                |-------|
 *                |   *   |
 *                |   |   |
 *                 -- | --
 *                    |
 *                    V  (Points to the next element in the list)
 */
class LinkedList : public List{
	/* Struct to represent the node of the list,
	 * it has two members, a pointer to object to enable
	 * pointing to anything that derives from Object,
	 * a pointer to the next node
	 */
	struct Node{
		Object* data;
		Node* next;
	};
	// Pointer to the first element of the list
	Node* _head;
	LinkedList(const LinkedList&);
	const LinkedList& operator=(const LinkedList&);
public:
	LinkedList();
	virtual ~LinkedList();

	virtual bool Insert(Object* element, size_t position);
	virtual int IndexOf(Object* element)const;
	virtual Object* Remove(size_t position);
	virtual Object* Get(size_t position)const;
	virtual string ToString()const;
	virtual void Clear();
};


#endif /* end of include guard: LINKEDLIST_H */
