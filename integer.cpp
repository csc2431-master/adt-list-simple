/*
 * Title:		Integer wrapper Class methods definition
 * Purpose:		A subclass of object to wrap up an integer
 * Author:		Carlos Arias
 * Date:		April 29, 2020
 */
#include "integer.h"

#include <string>
#include <sstream>
using std::string;
using std::stringstream;

/**
 * Constructor
 * Initializes the object with the value. This is basically a wrapper class
 * to wrap an integer and enable it to be inserted into a list of Objects.
 * This constructor is not explicit, therefore can serve as a conversion
 * constructor too!
 * @param value the initial value of the integer value being wrapped
 */
Integer::Integer(int value): _value(value){

}
/**
 * Creates a string representation of the integer.
 * @return the integer converted to string
 */
string Integer::ToString()const{
	stringstream retVal;
	retVal << _value;
	return retVal.str();
}
/**
 * Checks if rhs integer value is equal to this integer value. The method
 * will follow this protocol:
 * 1. Check if the two objects are actually the same
 * 2. Check if rhs is actually an integer, if not, they can't be the same
 * 3. After the above tests, cast and check the integer values
 * @param rhs the object to compare this to
 * @return true if the integer values are the same
 */
bool Integer::Equals(const Object& rhs)const{
	if (this == &rhs){
		return true;
	}
	// What happens if we take away the consts?
	const Integer* rhsPtr = dynamic_cast<const Integer*>(&rhs);
	if (rhsPtr == nullptr){
		return false;
	}
	return _value == rhsPtr->_value;

}
/**
 * Value accessor
 * @return the underlying integer value
 */
int Integer::GetValue()const{
	return _value;
}
/**
 * Value mutator
 * @param value the value to set the underlying integer
 */
void Integer::SetValue(int value){
	_value = value;
}
/**
 * Creates a deep copy of an integer
 * @return a newly allocated copy of this
 */
Object* Integer::Clone()const{
	return new Integer(_value);
}