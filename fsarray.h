/*
 * Title:		Fixed Size Array List
 * Purpose:		Implementation the ADT List using an underlying fixed size array.
 * 				The array will be allocated at construction with the specified
 * 				capacity.
 * Author:		Carlos Arias
 * Date:		April 29, 2020
 */

#ifndef FSARRAY_H
#define FSARRAY_H

#include "object.h"
#include "list.h"

#include <string>
#include <iostream>
using std::string;
using std::istream;
using std::ostream;
/**
 * This class uses an array to pointers to Object. This way it is
 * possible to add pointer references to the list to any object
 * that is an instance of a derived class from Object.
 * Copy constructor and Copy assignment operator are implemented but
 * kept private to prevent clients to create copies from the list.
 * The reason is mostly academic.
 */

class FSArray : public List{
	Object** _data;
	size_t _capacity;
	FSArray(const FSArray&);
	const FSArray& operator=(const FSArray&);
public:
	FSArray(size_t capacity);
	virtual ~FSArray();
	virtual bool Insert(Object* element, size_t position);
	virtual int IndexOf(Object* element)const;
	virtual Object* Remove(size_t position);
	virtual Object* Get(size_t position)const;
	virtual string ToString()const;
	virtual void Clear();
	size_t Capacity()const;
};


#endif
